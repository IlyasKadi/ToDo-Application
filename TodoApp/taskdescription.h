#ifndef TASKDESCRIPTION_H
#define TASKDESCRIPTION_H

#include <QDialog>
#include "task.h"
#include <QListWidgetItem>
#include <QSqlDatabase>
#include <QSqlQuery>


namespace Ui {
class TaskDescription;
}

class TaskDescription : public QDialog
{
    Q_OBJECT

public:

     void setdatabase(QString description, bool finished, QString date, QString tag);
     QSqlDatabase db;
     QStringList TT_list ;
     QStringList TBD_list ;
     QStringList FT_list ;
     TaskDescription(QWidget *parent = nullptr);
    ~TaskDescription();
    Ui::TaskDescription *ui;

private slots:
    void on_buttonBox_accepted();

private:
    QString ok;
    void setCurrentDate();

};

#endif // TASKDESCRIPTION_H
