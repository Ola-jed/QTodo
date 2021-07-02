#include "taskformwidget.hpp"
#include "../include/ui_TaskFormWidget.h"

TaskFormWidget::TaskFormWidget(QWidget *parent,const Task &initialTask) :
        AbstractForm(parent), ui(new Ui::TaskFormWidget)
{
    ui->setupUi(this);
    connect(ui->cancel,&QPushButton::clicked,this,&TaskFormWidget::close);
    connect(ui->submit,&QPushButton::clicked,this,&TaskFormWidget::validateInputs);
    // Set placeholders for task update
    if(!initialTask.title.isEmpty())
    {
        ui->titleEdit->setText(initialTask.title);
        ui->descriptionEdit->setPlainText(initialTask.description);
        ui->prioritySpinBox->setValue(initialTask.priority);
        ui->hasStepsCheckBox->setChecked(initialTask.has_steps);
        ui->dateEdit->setDate(QDate::fromString(initialTask.date_limit));
    }
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
        {"date_limit",ui->dateEdit->date().toString("dd/MM/yyyy")}
    });
    close();
}