#ifndef QTODO_SIGNINWIDGET_HPP
#define QTODO_SIGNINWIDGET_HPP

#include "abstractform.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class SigninWidget;
}
QT_END_NAMESPACE

class SigninWidget : public AbstractForm
{
Q_OBJECT

public:
    explicit SigninWidget(QWidget *parent = nullptr);
    ~SigninWidget() override;

private slots:
    void validateInputs() override;
    void clearAll() override;

private:
    Ui::SigninWidget *ui;
};

#endif //QTODO_SIGNINWIDGET_HPP
