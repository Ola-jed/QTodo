#include "taskwidget.hpp"
#include "../include/ui_TaskWidget.h"

TaskWidget::TaskWidget(const Task &task,QWidget *parent) :
    QWidget(parent), ui(new Ui::TaskWidget),internalTask(task)
{
    ui->setupUi(this);
    ui->titleLabel->setText(task.title);
    ui->prioritySlider->setValue(task.priority);
    ui->descriptionLabel->setText(task.description);
    ui->dateLabel->setText(task.date_limit);
    connect(ui->edit,&QPushButton::clicked,[&]{
        emit editRequested(internalTask);
    });
    connect(ui->deleteBtn,&QPushButton::clicked,[&]{
       emit deleteRequested(internalTask);
    });
}

TaskWidget::~TaskWidget()
{
    delete ui;
}
