#ifndef QTODO_STEPFORMWIDGET_HPP
#define QTODO_STEPFORMWIDGET_HPP

#include "abstractform.hpp"

QT_BEGIN_NAMESPACE
namespace Ui
{
    class StepFormWidget;
}
QT_END_NAMESPACE

class StepFormWidget : public AbstractForm
{
Q_OBJECT

public:
    explicit StepFormWidget(QWidget *parent = nullptr);
    ~StepFormWidget() override;

private slots:
    void clearAll() override;
    void validateInputs() override;

private:
    Ui::StepFormWidget *ui;

signals:
    void dataValidated(QMap<QString, QVariant> map);
};

#endif //QTODO_STEPFORMWIDGET_HPP
