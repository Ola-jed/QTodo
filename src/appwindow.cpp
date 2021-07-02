#include "appwindow.hpp"

AppWindow::AppWindow(QWidget *parent): QMainWindow(parent),taskList(new TaskList())
{
    buildActions();
    buildToolbar();
    buildLayout();
    makeConnections();
    initStatusBar();
}

/// Build the app layout (center on screen) icon
void AppWindow::buildLayout()
{
    setWindowIcon(QIcon(":assets/icon.png"));
    resize(900,550);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,size(),QGuiApplication::primaryScreen()->availableGeometry()));
    setCentralWidget(new HomeWidget);
    initStatusBar();
}

/// Init the status bar
/// Display a message depending on the fact that user is authenticated or not
void AppWindow::initStatusBar()
{
    auto stBar = statusBar();
    stBar->showMessage(appUser.name.isEmpty()
        ? "Not authenticated"
        : "Authenticated as " + appUser.name
    );
}

/// Build the window toolbar
void AppWindow::buildToolbar()
{
    auto toolbar = addToolBar("Toolbar");
    toolbar->addAction(signUp);
    toolbar->addAction(signIn);
    toolbar->addSeparator();
    toolbar->addAction(tasks);
    toolbar->addSeparator();
    toolbar->addAction(logout);
    toolbar->addAction(exit);
}

/// Build all our actions
void AppWindow::buildActions()
{
    signUp = new QAction(QIcon(":assets/signup.png"),"Sign up",this);
    signIn = new QAction(QIcon(":assets/signin.png"),"Sign in",this);
    tasks = new QAction(QIcon(":assets/task.png"),"Tasks",this);
    logout = new QAction(QIcon(":assets/logout.png"),"Logout",this);
    exit = new QAction(QIcon(":assets/exit.png"),"Exit",this);
}

/// Make all the connections for the toolbar actions
void AppWindow::makeConnections()
{
    connect(exit,&QAction::triggered,this,&AppWindow::onQuit);
    connect(signUp,&QAction::triggered,this,&AppWindow::onSignup);
    connect(signIn,&QAction::triggered,this,&AppWindow::onSignin);
    connect(tasks,&QAction::triggered,this,&AppWindow::onTaskLoading);
    connect(logout,&QAction::triggered,this,&AppWindow::onLogout);
    connect(taskList,&TaskList::taskSearchRequested,this,&AppWindow::onTaskSearch);
    connect(taskList,&TaskList::taskCreationRequested,this,&AppWindow::onTaskCreation);
    connect(taskList,&TaskList::taskEditRequested,this,&AppWindow::onTaskEdit);
    connect(taskList,&TaskList::taskDeleteRequested,this,&AppWindow::onTaskDelete);
}

/// Prompt to ask the user a confirmation to quit
void AppWindow::onQuit()
{
    if(QMessageBox::question(this,"Exit","Do you want to exit ?") == QMessageBox::Yes)
    {
        qApp->quit();
    }
}

/// Show the signup form and handle the signup process
void AppWindow::onSignup()
{
    auto signupWidget = new SignupWidget;
    setCentralWidget(signupWidget);
    connect(signupWidget,&SignupWidget::dataValidated,this,&AppWindow::makeSignup);
}

/// Show the signin form for the user and handle the signin process
void AppWindow::onSignin()
{
    auto signinWidget = new SigninWidget;
    setCentralWidget(signinWidget);
    connect(signinWidget,&SigninWidget::dataValidated,this,&AppWindow::makeSignin);
}

/// Signup a new user with the data
/// \param data
void AppWindow::makeSignup(const QMap<QString,QVariant> &data)
{
    connect(&appRequestsHandler, &HttpRequestHandler::signupSucceeded, this, &AppWindow::signupCompleted, Qt::UniqueConnection);
    connect(&appRequestsHandler,&HttpRequestHandler::authFailed,this,&AppWindow::operationFailed,Qt::UniqueConnection);
    appRequestsHandler.trySignup(data);
}

/// Signup process completed successfully
/// \param data
void AppWindow::signupCompleted(const QString &data)
{
    auto const userData = QJsonDocument::fromJson(data.toUtf8());
    auto const userJsonObject = userData.object();
    appRequestsHandler.token = userJsonObject["token"].toString();
    appUser = User::deserialize(QJsonDocument{userJsonObject["user"].toObject()}.toJson());
    QMessageBox::information(this,"Signup","Operation successful");
    initStatusBar();
}


/// Signin the user with the data
/// \param data
void AppWindow::makeSignin(const QMap<QString,QVariant> &data)
{
    connect(&appRequestsHandler,&HttpRequestHandler::signinSucceeded,this,&AppWindow::signinCompleted,Qt::UniqueConnection);
    connect(&appRequestsHandler,&HttpRequestHandler::authFailed,this,&AppWindow::operationFailed,Qt::UniqueConnection);
    appRequestsHandler.trySignin(data);
}

/// Signin process completed successfully
/// \param data
void AppWindow::signinCompleted(const QString &data)
{
    auto const userData = QJsonDocument::fromJson(data.toUtf8());
    auto const userJsonObject = userData.object();
    appRequestsHandler.token = userJsonObject["token"].toString();
    appUser = User::deserialize(QJsonDocument{userJsonObject["user"].toObject()}.toJson());
    QMessageBox::information(this,"Signin","Operation successful");
    initStatusBar();
}

/// Try to logout the connected user
void AppWindow::onLogout()
{
    connect(&appRequestsHandler,&HttpRequestHandler::logoutSucceeded,this,&AppWindow::logoutCompleted, Qt::UniqueConnection);
    connect(&appRequestsHandler,&HttpRequestHandler::authFailed, this,&AppWindow::operationFailed,Qt::UniqueConnection);
    appRequestsHandler.tryLogout();
}

/// Logout process completed successfully
/// Make the user unusable
void AppWindow::logoutCompleted()
{
    appUser.name.clear();
    appUser.email.clear();
    QMessageBox::information(this,"Logout","Operation successful");
    initStatusBar();
}

/// Shows a message box when something went wrong
/// \param data
void AppWindow::operationFailed(const QString &data)
{
    QMessageBox::warning(this,"Warning","Operation failed : " + data);
}

/// Load all the tasks
void AppWindow::onTaskLoading()
{
    setCentralWidget(taskList);
    connect(&appRequestsHandler,&HttpRequestHandler::tasksRetrievingSucceeded,this,&AppWindow::insertTasksInList);
    connect(&appRequestsHandler,&HttpRequestHandler::dataRetrievingFailed,[&](){
        qDebug() << "Error retrieving data";
    });
    appRequestsHandler.tryTasksRetrieving();
}

/// Search for tasks
/// \param search
void AppWindow::onTaskSearch(const QString &search)
{
    connect(&appRequestsHandler,&HttpRequestHandler::tasksRetrievingSucceeded,this,&AppWindow::insertTasksInList);
    connect(&appRequestsHandler,&HttpRequestHandler::dataRetrievingFailed,[&](){
        qDebug() << "Error retrieving data";
    });
    appRequestsHandler.tryTaskSearching(search);
}

/// Delete a task
/// \param taskToDelete
void AppWindow::onTaskDelete(const Task &taskToDelete)
{
    connect(&appRequestsHandler,&HttpRequestHandler::taskDeletionSucceeded,this,[=]{
    });
    connect(&appRequestsHandler,&HttpRequestHandler::dataDeletionFailed,[&]{
        qDebug() << "Could not delete task";
    });
    appRequestsHandler.tryTaskDeletion(taskToDelete);
}

/// Show the popup to create a new task
void AppWindow::onTaskCreation()
{
    auto form = new TaskFormWidget(this);
    connect(form,&TaskFormWidget::dataValidated,this,&AppWindow::makeTaskCreation);
    form->setWindowFlags(Qt::Dialog);
    form->show();
}

/// Creation of a new task
/// Insert a new task widget in the task list
/// \param data
void AppWindow::makeTaskCreation(const QMap<QString, QVariant> &data)
{
    connect(&appRequestsHandler,&HttpRequestHandler::taskCreationSucceeded,this,[=]{
        taskList->insertTask(Task::fromMap(data));
    });
    connect(&appRequestsHandler,&HttpRequestHandler::dataCreationFailed,[&]{
        qDebug() << "Task creation failed";
    });
    appRequestsHandler.tryTaskCreation(data);
}

/// Show the form to edit a task
/// TODO : finish implementation
/// \param taskToEdit
void AppWindow::onTaskEdit(const Task &taskToEdit)
{
    auto editForm = new TaskFormWidget(this,taskToEdit);
    connect(editForm,&TaskFormWidget::dataValidated,[]{
       qDebug() << "TODO : update this task";
    });
    editForm->setWindowFlags(Qt::Dialog);
    editForm->show();
}

/// Insert a list of tasks in the task widget
/// \param taskList
void AppWindow::insertTasksInList(const QList<Task> &tasksList)
{
    taskList->clear();
    taskList->insertTaskList(tasksList);
}