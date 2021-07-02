#include "signupwidget.hpp"
#include "../include/ui_SignupWidget.h"

SignupWidget::SignupWidget(QWidget *parent) :
        AbstractForm(parent), ui(new Ui::SignupWidget)
{
    ui->setupUi(this);
    connect(ui->cancel,&QPushButton::clicked,[&]{
        ui->nameEdit->clear();
        ui->emailEdit->clear();
        ui->passwordEdit->clear();
        ui->confirmPasswordEdit->clear();
    });
    connect(ui->submit,&QPushButton::clicked,this,&SignupWidget::validateInputs);
}

SignupWidget::~SignupWidget()
{
    delete ui;
}

/// Function to validate the form
void SignupWidget::validateInputs()
{
    if(ui->nameEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Name","The name field is required");
        return;
    }
    if(ui->emailEdit->text().isEmpty())
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
    if(ui->passwordEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Password","The password field is required");
        return;
    }
    if(ui->passwordEdit->text() != ui->confirmPasswordEdit->text())
    {
        QMessageBox::warning(this,"Password","The password and confirm password fields should match");
        return;
    }
    emit dataValidated(QMap<QString, QVariant>{
        {"name",ui->nameEdit->text()},
        {"email",ui->emailEdit->text()},
        {"password1",ui->passwordEdit->text()},
        {"password2",ui->confirmPasswordEdit->text()},
    });
}