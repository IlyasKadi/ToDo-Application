#include "todoapp.h"
#include "ui_todoapp.h"
#include "taskdescription.h"
#include "ui_taskdescription.h"
#include <QLayout>
#include <QFileSystemModel>
#include <QSqlQueryModel>
#include <QMessageBox>
#include <iostream>
#include <string>
#include <QDropEvent>






//constructor
ToDoApp::ToDoApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ToDoApp)
{
    ui->setupUi(this);
    makeconnections();
    loaddatabase();
}

//Connections for selected_Item aka selected_Task
void ToDoApp:: makeconnections()
{
    connect(ui->to_be_done, &QListWidget::itemActivated , this,  &ToDoApp::select_item_tbd);
    connect(ui->finished, &QListWidget::itemActivated, this,  &ToDoApp::select_item_finished);
    connect(ui->todays_task, &QListWidget::itemActivated, this,  &ToDoApp::select_item_today);
}

//destructor
ToDoApp::~ToDoApp()
{
    delete ui;
}

//NewTAsk Action
void ToDoApp::on_action_New_triggered()
{
    TaskDescription newtask ;
    newtask.exec();

    //Add Items(tasks) to the ListView from their appropriate table :

    //TBD_list >> to_be_done
    for(auto e :newtask.TBD_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-and-64.png"};
        QIcon icon(path);
        ui->to_be_done->addItem(new QListWidgetItem(icon,e));
    }

    //TT_list >> todays_task
    for(auto e :newtask.TT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-48.png"};
        QIcon icon(path);
        ui->todays_task->addItem(new QListWidgetItem(icon,e));
    }

    //FT_list >> finished
    for(auto e :newtask.FT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-terminée-48.png"};
        QIcon icon(path);
        ui->finished->addItem(new QListWidgetItem(icon,e));
    }


}

//Show Pending_Ts only
void ToDoApp::on_action_Task_Pending_triggered()
{
    ui->to_be_done->show();
    ui->todays_task->hide();
    ui->finished->hide();
}

//Show Finished_TS only
void ToDoApp::on_action_Task_finished_triggered()
{
    ui->todays_task->hide();
    ui->to_be_done->hide();
    ui->finished->show();
}

//Show Today's_Ts only
void ToDoApp::on_actionToday_s_Tasks_triggered()
{
    ui->finished->hide();
    ui->to_be_done->hide();
    ui->todays_task->show();
}

//Show All_Ts
void ToDoApp::on_actionAll_Tasks_triggered()
{
    ui->finished->show();
    ui->to_be_done->show();
    ui->todays_task->show();
}



void ToDoApp::loaddatabase()
{

    TaskDescription newtask;

    newtask.db =QSqlDatabase::addDatabase("QSQLITE");
    newtask.db.setDatabaseName("/home/ilyas/Desktop/test_2.sqlite");
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


    //ADd items(tasks) to the list view from tasks_List :

    //TBD_list >> to_be_done
    for(auto e :newtask.TBD_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-and-64.png"};
        QIcon icon(path);
        ui->to_be_done->addItem(new QListWidgetItem(icon,e));
    }
    //todays_task >> TT_list
    for(auto e :newtask.TT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-48.png"};
        QIcon icon(path);
        ui->todays_task->addItem(new QListWidgetItem(icon,e));
    }

    //FT_list >> finished
    for(auto e :newtask.FT_list)
    {
        QString path{"/home/ilyas/Downloads/icons8-tâche-terminée-48.png"};
        QIcon icon(path);
        ui->finished->addItem(new QListWidgetItem(icon,e));
    }



}

void ToDoApp:: select_item_tbd()
{

    TaskDescription newtask;

    const QString format = "ddd MMM d yyyy";

    //Retrieving Task_info from selected items
    QString fulldes = ui->to_be_done->currentItem()->data(0).toString();

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
    if(reply == TaskDescription::Accepted)
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
        ui->to_be_done->clear();
        ui->todays_task->clear();
        ui->finished->clear();
        loaddatabase();


    }





}
void ToDoApp:: select_item_finished()
{

    TaskDescription newtask;

    const QString format = "ddd MMM d yyyy";
    QString fulldes = ui->finished->currentItem()->data(0).toString();
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
    if(reply == TaskDescription::Accepted)
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


        ui->to_be_done->clear();
        ui->todays_task->clear();
        ui->finished->clear();
        loaddatabase();

    }


}
void ToDoApp:: select_item_today()
{
    TaskDescription newtask;

    const QString format = "ddd MMM d yyyy";
    QString fulldes = ui->todays_task->currentItem()->data(0).toString();
    int index = fulldes.indexOf(':');
    QString description = fulldes.mid(0,index);
    QString date = fulldes.mid(19+index+3,15);
    QString tag = fulldes.mid(36+index+2,6);

    newtask.ui->lineEdit->setText(description);
    newtask.ui->comboBox->setCurrentText(tag);
    //(no need to change checkbox : finsished it's already unchecked by DEFLT)
    //(no need to change date : Today's date is the date set by DEFLT)

    auto reply = newtask.exec();
    if(reply == TaskDescription::Accepted)
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
        {QMessageBox::critical(this,"info","could not insert entry");}


         ui->to_be_done->clear();
         ui->todays_task->clear();
         ui->finished->clear();
         loaddatabase();

    }

}




//void ToDoApp:: restoredragdrop()
//{
//    TaskDescription newtask;
//     QString str="";

//     for(int i = 0; i < ui->finished->count(); i++)
//     {

//         QString str = ui->finished->item(i)->data(0).toString();
//         int index = str.indexOf(':');
//         QString description = str.mid(0,index);
//          QString finished = str.mid(index+1,9);

//          QString date = str.mid(14+index+3,15);
//          QString tag = str.mid(31+index+2,6);
//          if(finished!="Finished")
//          {
//              QString path{"/home/ilyas/Downloads/icons8-and-64.png"};
//              QIcon icon(path);
//              ui->finished->addItem(new QListWidgetItem(icon,description+": Finished  Due: " ));

//              QString insert {"INSERT INTO task values ('%1','%2','%3','%4')"};
//              QSqlQuery insertentry(insert.arg(description),newtask.db);

//              if(!insertentry.exec(insert.arg(description).arg(finished).arg(date).arg(tag)))
//              {
//                  QMessageBox::critical(this,"info","insert not create table");
//              }


//          }


//     }


//    QString fulldes = ui->finished->currentItem()->data(0).toString();
//    int index = fulldes.indexOf(':');





//}
//void ToDoApp:: dropEvent(QDropEvent *event)

//{
//    exit(0);
//    if (event->DragLeave)
//    { exit(0);}


//}


