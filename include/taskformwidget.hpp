#ifndef QTODO_TASKFORMWIDGET_HPP
#define QTODO_TASKFORMWIDGET_HPP

#include "abstractform.hpp"
#include "task.hpp"

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
    explicit TaskFormWidget(QWidget *parent = nullptr,const Task &initialTask = Task{});
    ~TaskFormWidget() override;

private slots:
    void validateInputs() override;

private:
    Ui::TaskFormWidget *ui;

signals:
    void dataValidated(QMap<QString, QVariant> map);
};

#endif //QTODO_TASKFORMWIDGET_HPP
