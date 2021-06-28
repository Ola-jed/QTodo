#ifndef QTODO_ABSTRACTFORM_HPP
#define QTODO_ABSTRACTFORM_HPP

#include <QDebug>
#include <QWidget>
#include <QMessageBox>
#include <QRegularExpression>

class AbstractForm: public QWidget
{
Q_OBJECT
public:
    explicit AbstractForm(QWidget *parent = nullptr)
        : QWidget(parent){}
private slots:
    virtual void validateInputs() = 0;
    virtual void clearAll() = 0;
};


#endif //QTODO_ABSTRACTFORM_HPP
