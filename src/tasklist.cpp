#include "tasklist.hpp"
#include "../include/ui_TaskList.h"

TaskList::TaskList(QWidget *parent) :
        QWidget(parent), ui(new Ui::TaskList)
{
    ui->setupUi(this);
    auto wid = new QWidget(this);
    auto lay = new QVBoxLayout(wid);
    ui->scrollArea->setWidget(wid);
    ui->scrollArea->setWidgetResizable(true);
    connect(ui->searchBtn,&QPushButton::clicked,[this]{
        if(!ui->lineEdit->text().isEmpty())
        {
            qDebug() << "Search";
            emit taskSearchRequested(ui->lineEdit->text());
        }
    });
    connect(ui->addBtn,&QPushButton::clicked,[this]{
            qDebug() << "Add";
            emit taskCreationRequested();
    });
}

TaskList::~TaskList()
{
    delete ui;
}

/// Clear all the widgets
/// Iterate and delete all layout items
void TaskList::clear()
{
    QLayoutItem* child;
    while ((child = ui->scrollArea->widget()->layout()->takeAt(0)) != nullptr)
    {
        delete child->widget();
        delete child;
    }
}

/// Add a new task to the list
/// \param taskToInsert
void TaskList::insertTask(const Task &taskToInsert)
{
    auto taskWid = new TaskWidget(taskToInsert, this);
    connect(taskWid,&TaskWidget::deleteRequested,[=,this]{
        emit taskDeleteRequested(taskToInsert);
        qDebug() << "Delete a task";
    });
    ui->scrollArea->widget()->layout()->addWidget(taskWid);
    auto lineB = new QWidget;
    lineB->setFixedHeight(2);
    lineB->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    lineB->setStyleSheet(QString("background-color: #ffffff;"));
    ui->scrollArea->widget()->layout()->addWidget(lineB);
}

/// Add a list of task and build the task widget with all the tasks
/// \param tasksToInsert
void TaskList::insertTaskList(const QList<Task> &tasksToInsert)
{
    for(const auto & aTaskInList : tasksToInsert)
    {
        insertTask(aTaskInList);
    }
}