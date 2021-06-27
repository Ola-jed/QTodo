#ifndef QTODO_SIGNINWIDGET_HPP
#define QTODO_SIGNINWIDGET_HPP

#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SigninWidget;
}
QT_END_NAMESPACE

class SigninWidget : public QWidget
{
Q_OBJECT

public:
    explicit SigninWidget(QWidget *parent = nullptr);
    ~SigninWidget() override;

private slots:
    bool validateInputs();
    void clearAll();

private:
    Ui::SigninWidget *ui;

signals:
    void dataValidated(QMap<QString, QString> map);
};

#endif //QTODO_SIGNINWIDGET_HPP
