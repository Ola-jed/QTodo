#ifndef QTODO_HOMEWIDGET_HPP
#define QTODO_HOMEWIDGET_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class HomeWidget;
}
QT_END_NAMESPACE

class HomeWidget : public QWidget
{
Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget() override;

private:
    Ui::HomeWidget *ui;
};

#endif //QTODO_HOMEWIDGET_HPP
