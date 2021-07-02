#ifndef QTODO_SIGNUPWIDGET_HPP
#define QTODO_SIGNUPWIDGET_HPP

#include "abstractform.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SignupWidget;
}
QT_END_NAMESPACE

class SignupWidget : public AbstractForm
{
Q_OBJECT

public:
    explicit SignupWidget(QWidget *parent = nullptr);
    ~SignupWidget() override;

private slots:
    void validateInputs() override;

private:
    Ui::SignupWidget *ui;

signals:
    void dataValidated(QMap<QString, QVariant> map);
};

#endif //QTODO_SIGNUPWIDGET_HPP
