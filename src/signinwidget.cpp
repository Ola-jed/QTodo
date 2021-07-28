#include "signinwidget.hpp"
#include "../include/ui_SigninWidget.h"

SigninWidget::SigninWidget(QWidget *parent) :
    AbstractForm(parent), ui(new Ui::SigninWidget)
{
    ui->setupUi(this);
    connect(ui->cancel,&QPushButton::clicked,[&]{
        ui->emailEdit->clear();
        ui->passwordEdit->clear();
    });
    connect(ui->submit,&QPushButton::clicked,this,&SigninWidget::validateInputs);
}

SigninWidget::~SigninWidget()
{
    delete ui;
}

/// Validation of inputs
void SigninWidget::validateInputs()
{
    if(ui->emailEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this,"Email","The email field is required");
        return;
    }
    if(!QRegularExpression{R"([^@ \t\r\n]+@[^@ \t\r\n]+\.[^@ \t\r\n]+)"}
        .match(ui->emailEdit->text())
        .hasMatch())
    {
        QMessageBox::warning(this,"Email","Invalid email");
        return;
    }
    if(ui->passwordEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this,"Password","The password field is required");
        return;
    }
    emit dataValidated(QMap<QString,QVariant>{
        {"email",ui->emailEdit->text()},
        {"password",ui->passwordEdit->text()}
    });
}