#ifndef TODOAPP_H
#define TODOAPP_H

#include <QMainWindow>
#include <QHBoxLayout>
#include "taskdescription.h"
#include <QSqlDatabase>
#include <QSqlQuery>



QT_BEGIN_NAMESPACE
namespace Ui { class ToDoApp; }
QT_END_NAMESPACE

class ToDoApp : public QMainWindow
{
    Q_OBJECT

public:
//      void dropEvent(QDropEvent *event) override;
//  void restoredragdrop();
    void loaddatabase();
     void makeconnections();

    ToDoApp(QWidget *parent = nullptr);
    ~ToDoApp();

private slots:
    void on_action_New_triggered();

    void select_item_today();

    void select_item_finished();

    void select_item_tbd();

    void on_action_Task_Pending_triggered();

    void on_action_Task_finished_triggered();

    void on_actionToday_s_Tasks_triggered();

    void on_actionAll_Tasks_triggered();

private:
    Ui::ToDoApp *ui;
};
#endif // TODOAPP_H
