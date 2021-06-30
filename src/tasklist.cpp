#include "tasklist.hpp"
#include "../include/ui_TaskList.h"

TaskList::TaskList(QWidget *parent) :
        QWidget(parent), ui(new Ui::TaskList)
{
    ui->setupUi(this);
    //ui->listWidget->addItem(QListWidgetItem(new TaskFormWidget));
}

TaskList::~TaskList()
{
    delete ui;
}

/// Add a new task to the list
/// \param taskToInsert
void TaskList::insertTask(const Task &taskToInsert)
{

}

/// Add a list of task and build the task widget with all the tasks
/// \param tasksToInsert
void TaskList::insertTaskList(const QList<Task> &tasksToInsert)
{

}
