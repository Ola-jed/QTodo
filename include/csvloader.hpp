#ifndef QTODO_CSVLOADER_HPP
#define QTODO_CSVLOADER_HPP

#include "task.hpp"
#include <QFile>

namespace CsvLoader
{
    /// Save a task list into a csv file
    /// \param tasks
    /// \param filename
    inline bool saveTaskListToCsv(const QList<Task> &tasks,const QString &filename)
    {
        QFile fileToSave{filename};
        if(fileToSave.open(QFile::WriteOnly|QIODevice::Text))
        {
            QTextStream out{&fileToSave};
            out << "title,priority,date_limit,is_finished\n";
            for(auto const &task : tasks)
            {
                out << task.title << "," << task.priority << "," << task.date_limit << "," << task.is_finished << "\n";
            }
            return true;
        }
        return false;
    }
}
#endif //QTODO_CSVLOADER_HPP
