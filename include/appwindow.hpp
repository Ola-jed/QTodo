#ifndef QTODO_APPWINDOW_HPP
#define QTODO_APPWINDOW_HPP

#include "httprequesthandler.hpp"
#include "homewidget.hpp"
#include "signupwidget.hpp"
#include "signinwidget.hpp"
#include <QGuiApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QStyle>
#include <QScreen>

class AppWindow: public QMainWindow
{
private:
    HttpRequestHandler appRequestsHandler{};
    QAction *signUp;
    QAction *signIn;
    QAction *tasks;
    QAction *logout;
    QAction *exit;
    void buildLayout();
    void buildToolbar();
    void buildActions();
    void makeConnections();
    User appUser;

private slots:
    void onQuit();
    void onSignup();
    void makeSignup(const QMap<QString,QVariant> &data);
    void onSignin();
    void makeSignin(const QMap<QString,QVariant> &data);
    void onLogout();

public:
    explicit AppWindow(QWidget* parent = nullptr);
};
#endif //QTODO_APPWINDOW_HPP
