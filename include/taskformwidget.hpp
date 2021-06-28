#ifndef QTODO_TASKFORMWIDGET_HPP
#define QTODO_TASKFORMWIDGET_HPP

#include "abstractform.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TaskFormWidget;
}
QT_END_NAMESPACE

class TaskFormWidget : public AbstractForm
{
Q_OBJECT

public:
    explicit TaskFormWidget(QWidget *parent = nullptr);
    ~TaskFormWidget() override;

private slots:
    void clearAll() override;
    void validateInputs() override;

private:
    Ui::TaskFormWidget *ui;

signals:
    void dataValidated(QMap<QString, QVariant> map);
};

#endif //QTODO_TASKFORMWIDGET_HPP
