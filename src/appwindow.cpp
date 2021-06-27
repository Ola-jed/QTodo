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

/// Show the signup form and handle data
void AppWindow::onSignup()
{
    auto signupWidget = new SignupWidget;
    setCentralWidget(signupWidget);
}

/// Show the signin form for the user
void AppWindow::onSignin()
{
    auto signinWidget = new SigninWidget;
    setCentralWidget(signinWidget);
}

/// Try to logout the connected user
void AppWindow::onLogout()
{

}
