#include "appwindow.hpp"

AppWindow::AppWindow(QWidget *parent): QMainWindow(parent)
{
    buildActions();
    buildToolbar();
    buildLayout();
    makeConnections();
}

/// Build the app layout (center on screen) icon
void AppWindow::buildLayout()
{
    setWindowIcon(QIcon(":assets/icon.png"));
    resize(600,450);
    setGeometry(QStyle::alignedRect(Qt::LeftToRight,Qt::AlignCenter,size(),QGuiApplication::primaryScreen()->availableGeometry()));
    setCentralWidget(new HomeWidget);
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

// Make all the connections for the toolbar actions
void AppWindow::makeConnections()
{
    connect(exit,&QAction::triggered,this,&AppWindow::onQuit);
    connect(signUp,&QAction::triggered,this,&AppWindow::onSignup);
    connect(signIn,&QAction::triggered,this,&AppWindow::onSignin);
    connect(logout,&QAction::triggered,this,&AppWindow::onLogout);
}

/// Prompt to ask the user a confirmation to quit
void AppWindow::onQuit()
{
    const auto ans = QMessageBox::question(this,"Exit","Do you want to exit ?");
    if(ans == QMessageBox::Yes)
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
    connect(&appRequestsHandler,&HttpRequestHandler::signupSuceeded,[&](const QString &data){
        auto const userData = QJsonDocument::fromJson(data.toUtf8());
        auto const userJsonObject = userData.object();
        appRequestsHandler.token = userJsonObject["token"].toString();
        appUser = User::deserialize(QJsonDocument{userJsonObject["user"].toObject()}.toJson());
        QMessageBox::information(this,"Signup","Operation successful");
    });
    connect(&appRequestsHandler,&HttpRequestHandler::authFailed,[&](const QString &data){
        QMessageBox::information(this,"Signup","Operation failed "+data);
    });
    appRequestsHandler.trySignup(data);
}

/// Signin the user with the data
/// \param data
void AppWindow::makeSignin(const QMap<QString,QVariant> &data)
{
    connect(&appRequestsHandler,&HttpRequestHandler::signinSuceeded,[&](const QString &data){
        auto const userData = QJsonDocument::fromJson(data.toUtf8());
        auto const userJsonObject = userData.object();
        appRequestsHandler.token = userJsonObject["token"].toString();
        appUser = User::deserialize(QJsonDocument{userJsonObject["user"].toObject()}.toJson());
        QMessageBox::information(this,"Signin","Operation successful");
    });
    connect(&appRequestsHandler,&HttpRequestHandler::authFailed,[&](const QString &data){
        QMessageBox::information(this,"Signin","Operation failed "+data);
    });
    appRequestsHandler.trySignin(data);
}

/// Try to logout the connected user
void AppWindow::onLogout()
{
    connect(&appRequestsHandler,&HttpRequestHandler::logoutSuceeded,[&]{
        QMessageBox::information(this,"Logout","Operation successful");
    });
    connect(&appRequestsHandler,&HttpRequestHandler::authFailed,[&](const QString &data){
        QMessageBox::information(this,"Logout","Operation failed "+data);
    });
    appRequestsHandler.tryLogout();
}
