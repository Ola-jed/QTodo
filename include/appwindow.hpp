#ifndef QTODO_APPWINDOW_HPP
#define QTODO_APPWINDOW_HPP

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
    QAction *signUp;
    QAction *signIn;
    QAction *tasks;
    QAction *logout;
    QAction *exit;
    void buildLayout();
    void buildToolbar();
    void buildActions();
    void makeConnections();

private slots:
    void onQuit();
    void onSignup();
    void onSignin();
    void onLogout();

public:
    explicit AppWindow(QWidget* parent = nullptr);
};
#endif //QTODO_APPWINDOW_HPP
