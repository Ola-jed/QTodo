#include "taskformwidget.hpp"
#include "../include/ui_TaskFormWidget.h"

TaskFormWidget::TaskFormWidget(QWidget *parent) :
        AbstractForm(parent), ui(new Ui::TaskFormWidget)
{
    ui->setupUi(this);
    connect(ui->cancel,&QPushButton::clicked,this,&TaskFormWidget::clearAll);
    connect(ui->submit,&QPushButton::clicked,this,&TaskFormWidget::validateInputs);
}

TaskFormWidget::~TaskFormWidget()
{
    delete ui;
}

/// Validate all the inputs
void TaskFormWidget::validateInputs()
{
    if(ui->titleEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Title","The title field is required");
        return;
    }
    if(ui->descriptionEdit->toPlainText().isEmpty())
    {
        QMessageBox::warning(this,"Description","The description field is required");
        return;
    }
    emit dataValidated(QMap<QString,QVariant>{
        {"title",ui->titleEdit->text()},
        {"description",ui->descriptionEdit->toPlainText()},
        {"has_steps",ui->hasStepsCheckBox->isChecked()},
        {"priority",ui->prioritySpinBox->value()},
        {"date_limit",ui->dateEdit->date().toString("dd/mm/yyyy")}
    });
}

/// Clear all inputs
void TaskFormWidget::clearAll()
{
    ui->titleEdit->clear();
    ui->descriptionEdit->clear();
}