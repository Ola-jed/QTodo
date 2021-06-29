#ifndef QTODO_TASKWIDGET_HPP
#define QTODO_TASKWIDGET_HPP

#include <QWidget>
#include "task.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TaskWidget;
}
QT_END_NAMESPACE

class TaskWidget : public QWidget
{
Q_OBJECT

public:
    explicit TaskWidget(const Task &task,QWidget *parent = nullptr);
    ~TaskWidget() override;

private:
    Ui::TaskWidget *ui;
    Task internalTask;

signals:
    void editRequested(const Task &taskToEdit);
    void deleteRequested(const Task &taskToDelete);
};

#endif //QTODO_TASKWIDGET_HPP