#ifndef TASKEDIT_H
#define TASKEDIT_H

#include <QDialog>
#include "taskmanager.h"
#include <QSqlDatabase>
#include <QSqlQuery>

namespace Ui {
class TaskEdit;
}

class TaskEdit : public QDialog
{
    Q_OBJECT

public:
      Ui::TaskEdit *ui;
    void setdatabase(QString description, bool finished, QString date, QString tag);
    QSqlDatabase db;
    explicit TaskEdit(QWidget *parent = nullptr);
    ~TaskEdit();

private:

    void setCurrentDate();


public :
    QStringList TT_list ;
    QStringList TBD_list ;
    QStringList FT_list ;
private slots:
    void on_buttonBox_accepted();
};

#endif // TASKEDIT_H
