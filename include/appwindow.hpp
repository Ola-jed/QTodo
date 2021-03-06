#ifndef QTODO_APPWINDOW_HPP
#define QTODO_APPWINDOW_HPP

#include "tasklist.hpp"
#include "csvloader.hpp"
#include "homewidget.hpp"
#include "signinwidget.hpp"
#include "signupwidget.hpp"
#include "taskformwidget.hpp"
#include "accountformwidget.hpp"
#include "httprequesthandler.hpp"
#include <QGuiApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QFileDialog>
#include <QAction>
#include <QStyle>
#include <QScreen>
#include <QStatusBar>

class AppWindow: public QMainWindow
{
private:
    HttpRequestHandler appRequestsHandler{};
    QAction *signUp;
    QAction *signIn;
    QAction *account;
    QAction *tasks;
    QAction *saveAll;
    QAction *logout;
    QAction *exit;
    TaskList *taskList;
    void buildLayout();
    void buildToolbar();
    void buildActions();
    void makeConnections();
    void showActions();
    void hideActions();
    User appUser;

private slots:
    void onQuit();
    void initStatusBar();
    void onSignup();
    void makeSignup(const QMap<QString,QVariant> &data);
    void signupCompleted(const QString &data);
    void onSignin();
    void makeSignin(const QMap<QString,QVariant> &data);
    void signinCompleted(const QString &data);
    void onLogout();
    void onTaskLoading();
    void insertTasksInList(const QList<Task> &tasksList);
    void logoutCompleted();
    void operationFailed(const QString &data);
    void onTaskSearch(const QString &search);
    void onTaskCreation();
    void onTaskEdit(const Task &taskToEdit);
    void onTaskMarkingAsFinished(const QString &slug,bool status);
    void makeTaskCreation(const QMap<QString,QVariant> &data);
    void makeTaskEdit(const QString &slug,const QMap<QString,QVariant> &data);
    void onTaskDelete(const Task &taskToDelete);
    void onTasksSave();
    void buildAccountScreen();
    void makeAccountUpdate(const QMap<QString,QVariant> &data);

public:
    explicit AppWindow(QWidget* parent = nullptr);
};
#endif //QTODO_APPWINDOW_HPP
