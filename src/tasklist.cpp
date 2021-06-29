#include "tasklist.hpp"
#include "ui_TaskList.h"

TaskList::TaskList(QWidget *parent) :
        QWidget(parent), ui(new Ui::TaskList)
{
    ui->setupUi(this);
}

TaskList::~TaskList()
{
    delete ui;
}
