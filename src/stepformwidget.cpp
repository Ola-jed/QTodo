#include "stepformwidget.hpp"
#include "../include/ui_StepFormWidget.h"

StepFormWidget::StepFormWidget(QWidget *parent) :
    AbstractForm(parent), ui(new Ui::StepFormWidget)
{
    ui->setupUi(this);
    connect(ui->cancel,&QPushButton::clicked,this,&StepFormWidget::clearAll);
    connect(ui->submit,&QPushButton::clicked,this,&StepFormWidget::validateInputs);
}

StepFormWidget::~StepFormWidget()
{
    delete ui;
}

/// Clear all inputs
void StepFormWidget::clearAll()
{
    ui->titleEdit->clear();
}

/// Validate fields
void StepFormWidget::validateInputs()
{
    if(ui->titleEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Title","The title field is required");
        return;
    }
    emit dataValidated(QMap<QString,QVariant>{
        {"title",ui->titleEdit->text()},
        {"priority",ui->prioritySpinBox->value()}
    });
}