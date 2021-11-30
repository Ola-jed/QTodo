#include "appwindow.hpp"
#include "step.hpp"
#include <QFile>
#include <QSplashScreen>
#include <QApplication>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("QTodo");
    QCoreApplication::setOrganizationName("QTodo");
    QCoreApplication::setApplicationVersion("1.0");
    QPixmap pixmap(":assets/icon.png");
    QSplashScreen splash(pixmap);
    splash.show();
    QApplication::processEvents();
    QFile f{":dark/style.qss"};
    if (!f.exists())
    {
        qWarning() << "Unable to set stylesheet, file not found\n";
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    AppWindow e{};
    e.show();
    splash.finish(&e);
    return QApplication::exec();
}
