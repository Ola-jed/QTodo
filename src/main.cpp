#include "appwindow.hpp"
#include "homewidget.hpp"
#include "step.hpp"
#include <QFile>
#include <QApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QNetworkAccessManager>

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication a(argc, argv);
    QCoreApplication::setApplicationName("QTodo");
    QCoreApplication::setOrganizationName("QTodo");
    QCoreApplication::setApplicationVersion("1.0");
    /*QNetworkRequest rq{QUrl("http://localhost:8000/api/logout")};
    rq.setHeader(QNetworkRequest::ContentTypeHeader,"application/json");
    QJsonObject obj{};
    obj["name"] = "Ola";
    obj["email"] = "olabijed@gmail.com";
    obj["password1"] = "0000";
    obj["password2"] = "0000";
    obj["device_name"] = "x556uqk";
    auto const token = "1|dbsheYASD77FkKBSBYRXjxdMIYhTtsdDuZMFqtjD";
    auto header = QString("Bearer %1").arg(token);
    rq.setRawHeader(QByteArray("Authorization"), header.toUtf8());
    QJsonDocument doc{obj};
    QNetworkAccessManager manager{};
    auto rslt = manager.post(rq,doc.toJson());
    QObject::connect(rslt, &QNetworkReply::finished, [=]() {
        if(rslt->error() == QNetworkReply::NoError)
        {
            qDebug() << rslt->readAll();
        }
        else // handle error
        {
            qDebug() << rslt->errorString();
            qDebug() << rslt->readAll();
        }
    });*/
    QFile f(":dark/style.qss");
    if (!f.exists())
    {
        printf("Unable to set stylesheet, file not found\n");
    }
    else
    {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    AppWindow e{};
    e.show();
    return QApplication::exec();
}
