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
    ui->titleEdit->clear();
    ui->descriptionEdit->clear();
}

/// Validate all the inputs
bool TaskFormWidget::validateInputs()
{
    if(ui->titleEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Title","The title field is required");
        return false;
    }
    if(ui->descriptionEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,"Description","The description field is required");
        return false;
    }
    emit dataValidated(QMap<QString,QVariant>{
        {"title",ui->titleEdit->text()},

        /*
         *     "title":"taest",
    "description":"thi is a test task",
    "has_steps":true,
    "priority":7,
    "date_limit":"04/10/2024"
         */
    });
    return true;
}



