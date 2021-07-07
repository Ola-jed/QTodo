#include "taskwidget.hpp"
#include "../include/ui_TaskWidget.h"

/// Constructor
/// Building signals
/// \param task
/// \param parent
TaskWidget::TaskWidget(const Task &task,QWidget *parent) :
    QWidget(parent), ui(new Ui::TaskWidget),internalTask(task)
{
    ui->setupUi(this);
    ui->titleLabel->setText(task.title);
    ui->prioritySlider->setValue(task.priority);
    ui->descriptionLabel->setText(task.description);
    ui->dateLabel->setText(task.date_limit);
    ui->finishCheckBox->setChecked(task.is_finished);
    connect(ui->finishCheckBox,&QCheckBox::stateChanged,[&,this](int state){
        emit markingAsFinishedRequested(state == Qt::Checked);
    });
    connect(ui->edit,&QPushButton::clicked,[&]{
        emit editRequested(internalTask);
    });
    connect(ui->deleteBtn,&QPushButton::clicked,[&,this]{
       emit deleteRequested(internalTask);
    });
}

TaskWidget::~TaskWidget()
{
    delete ui;
}