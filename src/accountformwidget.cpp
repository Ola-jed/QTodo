#include "accountformwidget.hpp"
#include "../include/ui_AccountFormWidget.h"

AccountFormWidget::AccountFormWidget(const QMap<QString,QVariant> &userData,QWidget *parent) :
        AbstractForm(parent), ui(new Ui::AccountFormWidget)
{
    ui->setupUi(this);
    const auto data = userData["data"].toMap();
    ui->nameEdit->setText(data["name"].toString());
    ui->emailEdit->setText(data["email"].toString());
    connect(ui->updateButton, &QPushButton::clicked, this, &AccountFormWidget::validateInputs);
    connect(ui->deleteButton, &QPushButton::clicked, this, &AccountFormWidget::checkInputForDeletion);
}

AccountFormWidget::~AccountFormWidget()
{
    delete ui;
}

/// Validate inputs of widget
void AccountFormWidget::validateInputs()
{
    if (ui->nameEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Name", "The name field is required");
        return;
    }
    if (ui->emailEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Email", "The email field is required");
        return;
    }
    if (!QRegularExpression{R"([^@ \t\r\n]+@[^@ \t\r\n]+\.[^@ \t\r\n]+)"}
            .match(ui->emailEdit->text())
            .hasMatch())
    {
        QMessageBox::warning(this, "Email", "Invalid email");
        return;
    }
    if (ui->passwordEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Password", "The password field is required");
        return;
    }
    emit dataValidated(QMap<QString, QVariant>{
            {"name",         ui->nameEdit->text()},
            {"email",        ui->emailEdit->text()},
            {"password",     ui->passwordEdit->text()},
            {"new_password", ui->newPasswordEdit->text()}
    });
}

/// Check the password input for the deletion
void AccountFormWidget::checkInputForDeletion()
{
    if (ui->passwordEdit->text().trimmed().isEmpty())
    {
        QMessageBox::warning(this, "Password", "The password field is required");
        return;
    }
    emit deletionRequested(ui->passwordEdit->text());
}
