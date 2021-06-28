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
    explicit TaskWidget(Task task,QWidget *parent = nullptr);
    ~TaskWidget() override;

private:
    Ui::TaskWidget *ui;
};

#endif //QTODO_TASKWIDGET_HPP
