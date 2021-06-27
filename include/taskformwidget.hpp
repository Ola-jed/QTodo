#ifndef QTODO_TASKFORMWIDGET_HPP
#define QTODO_TASKFORMWIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TaskFormWidget;
}
QT_END_NAMESPACE

class TaskFormWidget : public QWidget
{
Q_OBJECT

public:
    explicit TaskFormWidget(QWidget *parent = nullptr);
    ~TaskFormWidget() override;

private:
    Ui::TaskFormWidget *ui;

private slots:
    void clearAll();
    bool validateInputs();

signals:
    void dataValidated(QMap<QString,QVariant>);
};

#endif //QTODO_TASKFORMWIDGET_HPP
