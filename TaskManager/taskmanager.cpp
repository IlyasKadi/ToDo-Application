#include "taskmanager.h"
#include "ui_taskmanager.h"
#include "ui_taskedit.h"
#include "taskedit.h"
#include <QStandardItemModel>
#include <QStandardItem>
#include <QAbstractListModel>
#include <QDate>
#include <QMessageBox>
#include <QListView>



TaskManager::TaskManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::TaskManager)
{
    ui->setupUi(this);
    tttaskmodel = new QStandardItemModel;
    Ftaskmodel = new QStandardItemModel;
    TBDmodel= new QStandardItemModel;

    loaddatabase();
     makeconnections();


}

void TaskManager:: makeconnections()
{
    connect(ui->to_be_done, &QAbstractItemView::doubleClicked , this,  &TaskManager::select_item_tbd);
    connect(ui->finished, &QAbstractItemView::doubleClicked, this,  &TaskManager::select_item_finished);
    connect(ui->todays_task, &QAbstractItemView::doubleClicked, this,  &TaskManager::select_item_today);
    connect(ui->todays_task, &QAbstractItemView::clicked , this,  &TaskManager::deleteslot);
    connect(ui->finished, &QAbstractItemView::clicked , this,  &TaskManager::deleteslot);
    connect(ui->to_be_done, &QAbstractItemView::clicked , this,  &TaskManager::deleteslot);

}

TaskManager::~TaskManager()
{
    delete ui;
    delete TBDmodel;
    delete Ftaskmodel;
    delete tttaskmodel;

}


void TaskManager::on_action_Quit_triggered()
{

}
void TaskManager::on_action_New_triggered()
{

    TaskEdit newtask;
    newtask.exec();
    for(auto e :newtask.TBD_list)
    {

        QString path{"/home/ilyas/Downloads/icons8-and-64.png"};
        QIcon icon(path);
        ui->to_be_done->setModel(TBDmodel);
        TBDmodel->appendRow(new QStandardItem(QIcon(icon),e));


    }
    for(auto e :newtask.TT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-48.png"};
        QIcon icon(path);
        ui->todays_task->setModel(tttaskmodel);
        tttaskmodel->appendRow(new QStandardItem(QIcon(icon),e));


    }
    for(auto e :newtask.FT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-terminée-48.png"};
        QIcon icon(path);
        ui->finished->setModel(Ftaskmodel);
        Ftaskmodel->appendRow(new QStandardItem(QIcon(icon),e));


    }


}


void TaskManager::on_action_Today_s_Tasks_triggered()
{
    ui->finished->hide();
     ui->to_be_done->hide();
     ui->todays_task->show();
}


void TaskManager::on_action_Pending_Tasks_triggered()
{
    ui->to_be_done->show();
    ui->todays_task->hide();
    ui->finished->hide();
}


void TaskManager::on_action_Finished_Tasks_triggered()
{
    ui->todays_task->hide();
    ui->to_be_done->hide();
    ui->finished->show();

}
void TaskManager::on_actionAll_Tasks_triggered()
{
    ui->todays_task->show();
    ui->to_be_done->show();
    ui->finished->show();
}


void TaskManager::loaddatabase()
{

    TaskEdit newtask;

    newtask.db =QSqlDatabase::addDatabase("QSQLITE");
    newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
    newtask.db.open();

    const QString format = "ddd MMM d yyyy";
    QDate currdate = QDate::currentDate();
    QString todadate = currdate.toString(format);

    //Query for Today's Ts
    QString sttquery ="SELECT * from task where finished =0 and date ='%1'";
    QSqlQuery tt_query(sttquery.arg(todadate),newtask.db);

    //Query for Pendind_Ts
    QString stbd_query("SELECT * from task where finished =0 and date !='%1' ");
    QSqlQuery tbd_query(stbd_query.arg(todadate),newtask.db);

    //Query for Finished_Ts
    QSqlQuery F_query("SELECT * from task where finished =1",newtask.db);

   //Load data from DB to each task_List
    while(F_query.next())
        newtask.FT_list.append(""+F_query.value(0).toString()+": Finished  Due: " + F_query.value(2).toString() + " " +F_query.value(3).toString());

    while(tbd_query.next())
        newtask.TBD_list.append(""+tbd_query.value(0).toString()+": Pending  Due: " + tbd_query.value(2).toString() + " " +tbd_query.value(3).toString());

    while(tt_query.next())
        newtask.TT_list.append(""+tt_query.value(0).toString()+": Task for Today Due: "+ tt_query.value(2).toString() + " " +tt_query.value(3).toString());



    for(auto e :newtask.TT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-48.png"};
        QIcon icon(path);
        ui->todays_task->setModel(tttaskmodel);
        tttaskmodel->appendRow(new QStandardItem(QIcon(icon),e));

    }
    for(auto e :newtask.FT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-terminée-48.png"};
        QIcon icon(path);
        Ftaskmodel->appendRow(new QStandardItem(QIcon(icon),e));
        ui->finished->setModel(Ftaskmodel);
    }

    for(auto e :newtask.TBD_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-and-64.png"};
        QIcon icon(path);
        ui->to_be_done->setModel(TBDmodel);
        TBDmodel->appendRow(new QStandardItem(QIcon(icon),e));

    }



}


void TaskManager:: select_item_tbd()
{

ui->action_Delete->setEnabled(1);
    TaskEdit newtask;
    newtask.db =QSqlDatabase::addDatabase("QSQLITE");

    newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
    newtask.db.open();


    const QString format = "ddd MMM d yyyy";

    //Retrieving Task_info from selected items
    QModelIndex ind = ui->to_be_done->currentIndex();
    QString itemText = ind.data(0).toString();

    QString fulldes = itemText;
    QVariant i =fulldes.size();
    int index = fulldes.indexOf(':');

    //Filtering Task_info from selected item(task)
    QString description = fulldes.mid(0,index);
    QString date = fulldes.mid(13+index+3,15);
    QDate Date = QDate::fromString(date,"ddd MMM d yyyy");
    QString tag = fulldes.mid(30+index+2,6);

    //Filling up NewTaskEdit from filtered data before EXEC..
    newtask.ui->lineEdit->setText(description);
    newtask.ui->dateEdit->setDate(Date);
    newtask.ui->comboBox->setCurrentText(tag);
    //(no need to change checkbox : finsished it's already unchecked by DEFLT)


    auto reply = newtask.exec();
    if(reply == TaskEdit::Accepted)
    {
        //Filtering Task_info from selected item(task) after accepting TaskEdit dialog..
        QString afdescription = newtask.ui->lineEdit->text();
        QString afdate = newtask.ui->dateEdit->date().toString(format);
        QString aftag=newtask.ui->comboBox->currentText();
        bool isfinished=newtask.ui->checkBox->isChecked();

        //Delete Query for slected task
        QString sdeleteentry ="DELETE FROM task where description='%1' ";
        QSqlQuery delentry(sdeleteentry.arg(description),newtask.db);
        if(!delentry.exec(sdeleteentry))
        {QMessageBox::critical(this,"info","could not delete entry");}

        //Insert Query for edited task
        QString insert {"INSERT INTO task values ('%1','%2','%3','%4')"};
        QSqlQuery insertentry(newtask.db);

        if(!insertentry.exec(insert.arg(afdescription).arg(isfinished).arg(afdate).arg(aftag)))
        {QMessageBox::critical(this,"info","could not insert entry");}

        //Refreshing ListView
        TBDmodel->clear();
        tttaskmodel->clear();
        Ftaskmodel->clear();
        loaddatabase();

    }





}
void TaskManager:: select_item_finished()
{

    ui->action_Delete->setEnabled(1);
    TaskEdit newtask;
    newtask.db =QSqlDatabase::addDatabase("QSQLITE");

    newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
    newtask.db.open();

    const QString format = "ddd MMM d yyyy";
    QModelIndex ind = ui->finished->currentIndex();
    QString itemText = ind.data(0).toString();

    QString fulldes = itemText;
    int index = fulldes.indexOf(':');

    QString description = fulldes.mid(0,index);
    QString date = fulldes.mid(14+index+3,15);
    QString tag = fulldes.mid(31+index+2,6);
    QDate Date = QDate::fromString(date,"ddd MMM d yyyy");
    QString finished = fulldes.mid(index+1,9);

    newtask.ui->lineEdit->setText(description);
    newtask.ui->dateEdit->setDate(Date);
    newtask.ui->comboBox->setCurrentText(tag);
    newtask.ui->checkBox->setChecked(1);


    auto reply = newtask.exec();
    if(reply == TaskEdit::Accepted)
    {

        QString afdescription = newtask.ui->lineEdit->text();
        QString afdate = newtask.ui->dateEdit->date().toString(format);
        QString aftag=newtask.ui->comboBox->currentText();
        bool isfinished=newtask.ui->checkBox->isChecked();

        QString sdeleteentry ="DELETE FROM task where description='%1' ";
        QSqlQuery delentry(sdeleteentry.arg(description),newtask.db);
        if(!delentry.exec(sdeleteentry))
        {QMessageBox::critical(this,"info","could not delete entry");}

        QString insert {"INSERT INTO task values ('%1','%2','%3','%4')"};
        QSqlQuery insertentry(newtask.db);
        if(!insertentry.exec(insert.arg(afdescription).arg(isfinished).arg(afdate).arg(aftag)))
           { QMessageBox::critical(this,"info","could not insert entry");}

        //Refreshing ListView
        TBDmodel->clear();
        tttaskmodel->clear();
        Ftaskmodel->clear();

        loaddatabase();

    }


}
void TaskManager:: select_item_today()
{

    TaskEdit newtask;
    newtask.db =QSqlDatabase::addDatabase("QSQLITE");

    newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
    newtask.db.open();

    const QString format = "ddd MMM d yyyy";

    QModelIndex ind = ui->todays_task->currentIndex();
    QString itemText = ind.data(0).toString();

    QString fulldes = itemText;
    int index = fulldes.indexOf(':');
    QString description = fulldes.mid(0,index);
    QString date = fulldes.mid(19+index+3,15);
    QString tag = fulldes.mid(36+index+2,6);

    newtask.ui->lineEdit->setText(description);
    newtask.ui->comboBox->setCurrentText(tag);
    //(no need to change checkbox : finsished it's already unchecked by DEFLT)
    //(no need to change date : Today's date is the date set by DEFLT)

    auto reply = newtask.exec();
    if(reply == TaskEdit::Accepted)
    {
        QString afdescription = newtask.ui->lineEdit->text();
        QString afdate = newtask.ui->dateEdit->date().toString(format);
        QString aftag=newtask.ui->comboBox->currentText();
        bool isfinished=newtask.ui->checkBox->isChecked();

        QString sdeleteentry ="DELETE FROM task where description='%1' ";
        QSqlQuery delentry(newtask.db);
        if(!delentry.exec(sdeleteentry.arg(description)))
        {QMessageBox::critical(this,"info","could not delete entry");}


        QString insert {"INSERT INTO task values ('%1','%2','%3','%4')"};
        QSqlQuery insertentry(newtask.db);
        if(!insertentry.exec(insert.arg(afdescription).arg(isfinished).arg(afdate).arg(aftag)))
        {QMessageBox::critical(this,"info","could not insert entry");}

        //Refreshing ListView
        TBDmodel->clear();
        tttaskmodel->clear();
        Ftaskmodel->clear();
        loaddatabase();

    }

}



void TaskManager::on_action_Delete_triggered()
{

        //Pending tasks :
    if(ui->to_be_done->currentIndex().isValid())
    {
        TaskEdit newtask;
        newtask.db =QSqlDatabase::addDatabase("QSQLITE");

        newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
        newtask.db.open();

        const QString format = "ddd MMM d yyyy";

        QModelIndex indt = ui->to_be_done->currentIndex();

        QString itemText_t = indt.data(0).toString();

        QString fulldes = itemText_t;
        int index = fulldes.indexOf(':');
        QString description = fulldes.mid(0,index);
        QString date = fulldes.mid(19+index+3,15);
        QString tag = fulldes.mid(36+index+2,6);


            QString sdeleteentry ="DELETE FROM task where description='%1' ";
            QSqlQuery delentry(sdeleteentry.arg(description),newtask.db);
            if(!delentry.exec(sdeleteentry))
            {QMessageBox::critical(this,"info","could not delete entry");}

            TBDmodel->clear();
            tttaskmodel->clear();
            Ftaskmodel->clear();
            loaddatabase();
    }


        //Today's tasks :
    else if(ui->todays_task->currentIndex().isValid())
    {
        TaskEdit newtask;
        newtask.db =QSqlDatabase::addDatabase("QSQLITE");

        newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
        newtask.db.open();

        const QString format = "ddd MMM d yyyy";

        QModelIndex indt = ui->todays_task->currentIndex();

        QString itemText_t = indt.data(0).toString();

        QString fulldes = itemText_t;
        int index = fulldes.indexOf(':');
        QString description = fulldes.mid(0,index);
        QString date = fulldes.mid(19+index+3,15);
        QString tag = fulldes.mid(36+index+2,6);

        newtask.ui->lineEdit->setText(description);


            QString sdeleteentry ="DELETE FROM task where description='%1' ";
            QSqlQuery delentry(sdeleteentry.arg(description),newtask.db);
            if(!delentry.exec(sdeleteentry))
            {QMessageBox::critical(this,"info","could not delete entry");}


            //Refreshing ListView
            TBDmodel->clear();
            tttaskmodel->clear();
            Ftaskmodel->clear();
            loaddatabase();
    }

        //Finished tasks :
    else if(ui->finished->currentIndex().isValid())
    {
        TaskEdit newtask;
        newtask.db =QSqlDatabase::addDatabase("QSQLITE");

        newtask.db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
        newtask.db.open();

        const QString format = "ddd MMM d yyyy";

        QModelIndex indt = ui->finished->currentIndex();

        QString itemText_t = indt.data(0).toString();

        QString fulldes = itemText_t;
        int index = fulldes.indexOf(':');
        QString description = fulldes.mid(0,index);
        QString date = fulldes.mid(19+index+3,15);
        QString tag = fulldes.mid(36+index+2,6);

        newtask.ui->lineEdit->setText(description);


            QString sdeleteentry ="DELETE FROM task where description='%1' ";
            QSqlQuery delentry(sdeleteentry.arg(description),newtask.db);
            if(!delentry.exec(sdeleteentry))
            {QMessageBox::critical(this,"info","could not delete entry");}

            //Refreshing ListView
            TBDmodel->clear();
            tttaskmodel->clear();
            Ftaskmodel->clear();
            loaddatabase();
   }


}

void TaskManager::deleteslot()
{
     ui->action_Delete->setEnabled(1);

}



