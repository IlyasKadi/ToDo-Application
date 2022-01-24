#ifndef TASKMANAGER_H
#define TASKMANAGER_H

#include <QMainWindow>
#include "taskedit.h"
#include <QStringListModel>
#include <QStandardItemModel>


QT_BEGIN_NAMESPACE
namespace Ui { class TaskManager; }
QT_END_NAMESPACE

class TaskManager : public QMainWindow
{
    Q_OBJECT

public:
    QStandardItemModel *tttaskmodel = nullptr;
    QStandardItemModel *Ftaskmodel = nullptr;
    QStandardItemModel *TBDmodel= nullptr;


    void deleteslot();
    void makeconnections();
    void loaddatabase();
    TaskManager(QWidget *parent = nullptr);
    ~TaskManager();

private slots:
    void select_item_today();

    void select_item_finished();

    void select_item_tbd();
    void on_action_Quit_triggered();
    void on_action_New_triggered();

    void on_action_Today_s_Tasks_triggered();

    void on_action_Pending_Tasks_triggered();

    void on_action_Finished_Tasks_triggered();

    void on_action_Delete_triggered();

    void on_actionAll_Tasks_triggered();

private:
    Ui::TaskManager *ui;
};
#endif // TASKMANAGER_H
