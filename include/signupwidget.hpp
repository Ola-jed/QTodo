#ifndef QTODO_SIGNUPWIDGET_HPP
#define QTODO_SIGNUPWIDGET_HPP

#include <QDebug>
#include <QWidget>
#include <QRegularExpression>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SignupWidget;
}
QT_END_NAMESPACE

class SignupWidget : public QWidget
{
Q_OBJECT

public:
    explicit SignupWidget(QWidget *parent = nullptr);
    ~SignupWidget() override;

private:
    Ui::SignupWidget *ui;

private slots:
    bool validateInputs();
    void clearAll();

signals:
    void dataValidated(QMap<QString, QString> map);
};

#endif //QTODO_SIGNUPWIDGET_HPP
