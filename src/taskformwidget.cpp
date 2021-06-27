#include "taskformwidget.hpp"
#include "../include/ui_TaskFormWidget.h"

TaskFormWidget::TaskFormWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::TaskFormWidget)
{
    ui->setupUi(this);
}

TaskFormWidget::~TaskFormWidget()
{
    delete ui;
}

/// Clear all inputs
void TaskFormWidget::clearAll()
{

}

/// Validate all the inputs
bool TaskFormWidget::validateInputs()
{
    return true;
}



