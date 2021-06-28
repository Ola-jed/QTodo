#include "taskwidget.hpp"
#include "../include/ui_TaskWidget.h"

TaskWidget::TaskWidget(Task task,QWidget *parent) :
    QWidget(parent), ui(new Ui::TaskWidget)
{
    ui->setupUi(this);
}

TaskWidget::~TaskWidget()
{
    delete ui;
}
