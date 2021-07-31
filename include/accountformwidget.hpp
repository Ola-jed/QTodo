#ifndef QTODO_ACCOUNTFORMWIDGET_HPP
#define QTODO_ACCOUNTFORMWIDGET_HPP

#include "abstractform.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class AccountFormWidget;
}
QT_END_NAMESPACE

class AccountFormWidget : public AbstractForm
{
Q_OBJECT

public:
    explicit AccountFormWidget(const QMap<QString,QVariant> &userData,QWidget *parent = nullptr);
    ~AccountFormWidget() override;

private slots:
    void validateInputs() override;
    void checkInputForDeletion();

private:
    Ui::AccountFormWidget *ui;

signals:
    void dataValidated(const QMap<QString, QVariant> &map);
    void deletionRequested(const QString &password);
};

#endif //QTODO_ACCOUNTFORMWIDGET_HPP
