#include "signupwidget.hpp"
#include "../include/ui_SignupWidget.h"

SignupWidget::SignupWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::SignupWidget)
{
    ui->setupUi(this);
    connect(ui->cancel,&QPushButton::clicked,this,&SignupWidget::clearAll);
    connect(ui->submit,&QPushButton::clicked,this,&SignupWidget::validateInputs);
}

SignupWidget::~SignupWidget()
{
    delete ui;
}

/// Function to validate the form
/// \return bool
bool SignupWidget::validateInputs()
{
    if(ui->nameEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Name","The name field is required");
        return false;
    }
    if(ui->emailEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Email","The email field is required");
        return false;
    }
    if(!QRegularExpression{R"([^@ \t\r\n]+@[^@ \t\r\n]+\.[^@ \t\r\n]+)"}
        .match(ui->emailEdit->text())
        .hasMatch())
    {
        QMessageBox::warning(this,"Email","Invalid email");
        return false;
    }
    if(ui->passwordEdit->text().isEmpty())
    {
        QMessageBox::warning(this,"Password","The password field is required");
        return false;
    }
    if(ui->passwordEdit->text() != ui->confirmPasswordEdit->text())
    {
        QMessageBox::warning(this,"Password","The password and confirm password fields should match");
        return false;
    }
    emit dataValidated(QMap<QString, QString>{
        {"name",ui->nameEdit->text()},
        {"email",ui->emailEdit->text()},
        {"password",ui->passwordEdit->text()}
    });
    return true;
}

/// Clear all inputs to reset the form
void SignupWidget::clearAll()
{
    ui->nameEdit->clear();
    ui->emailEdit->clear();
    ui->passwordEdit->clear();
    ui->confirmPasswordEdit->clear();
}
