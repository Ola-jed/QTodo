#ifndef QTODO_TASKLIST_HPP
#define QTODO_TASKLIST_HPP

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class TaskList;
}
QT_END_NAMESPACE

class TaskList : public QWidget
{
Q_OBJECT

public:
    explicit TaskList(QWidget *parent = nullptr);
    ~TaskList() override;

private:
    Ui::TaskList *ui;
};

#endif //QTODO_TASKLIST_HPP
