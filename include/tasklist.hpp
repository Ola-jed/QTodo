#ifndef QTODO_TASKLIST_HPP
#define QTODO_TASKLIST_HPP

#include <QWidget>
#include <QLayoutItem>
#include "taskformwidget.hpp"
#include "taskwidget.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TaskList;
}
QT_END_NAMESPACE

class TaskList : public QWidget
{
Q_OBJECT

public:
    explicit TaskList(QWidget *parent = nullptr);
    ~TaskList() override;

public slots:
    void clear();
    void insertTask(const Task &taskToInsert);
    void insertTaskList(const QList<Task> &tasksToInsert);

private:
    Ui::TaskList *ui;

signals:
    void taskCreationRequested();
    void taskSearchRequested(const QString &search);
    void taskEditRequested(const Task &taskToDelete);
    void taskMarkingAsFinishedRequested(const QString &slug,bool status);
    void taskDeleteRequested(const Task &taskToDelete);
};

#endif //QTODO_TASKLIST_HPP
