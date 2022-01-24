#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDateTime>
#include "taskdescription.h"




class Task
{
private:
//    QString description;
//     bool finished;
//    QString tag;
//    QDate duedate;


public:
    Task(QString desc,bool fin,QString tag,QDate ddate);

   //Setters

//    void setdescription(QString des)
//    {
//        des=description;
//    }
//    void setfinished(bool fin)
//    {
//        fin=finished;
//    }
//    void settag(QString tag)
//    {
//        tag=tag;
//    }
//    void setdate(QDate ddate)
//    {
//        ddate=duedate;
//    }

////...................


//    //getters

//    QString getdescription()
//    {
//        return description;
//    }
//    bool getfinished()
//    {
//        return finished;
//    }
//    QString gettag()
//    {
//        return tag;
//    }
//    QDate getdate()
//    {
//        return duedate;
//    }

};

#endif // TASK_H
