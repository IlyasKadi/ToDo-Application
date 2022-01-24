#include "taskdescription.h"
#include "ui_taskdescription.h"
#include "task.h"
#include "todoapp.h"
#include <QSqlQueryModel>
#include <QMessageBox>
#include <iostream>


//Constructor
TaskDescription::TaskDescription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskDescription)
{
    ui->setupUi(this);

    setCurrentDate();

}

//Destructor
TaskDescription::~TaskDescription()
{
    delete ui;

}

//Setting today's date as default date
void TaskDescription::setCurrentDate()
{
    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
}


//function applied once the Dialog is accepted
void TaskDescription::on_buttonBox_accepted()
{

    const QString format = "ddd MMM d yyyy";

    //Retrieving user_data
    QDate currdate = QDate::currentDate();
    QDate duedate = ui->dateEdit->date();
    QString textdudate = duedate.toString(format);
    QString tag = ui->comboBox->currentText();
    bool isfinished = ui->checkBox->isChecked();
    QString description = ui->lineEdit->text();


    //Filling up tasks_List from user_data ..

    if(isfinished)
        FT_list.append(description+": Finished  Due: " + textdudate + " " + tag);


    else if(duedate==currdate)
        TT_list.append(description+": Task for Today Due: " + textdudate + " " + tag);


    else if(duedate>currdate && !isfinished)
        TBD_list.append(description+": Pending  Due: " + textdudate + " " + tag);

    //settinging up data base and insert new entry from user_data retrieved
    setdatabase( description, isfinished,  textdudate,  tag);


}

void TaskDescription::setdatabase(QString description, bool finished, QString date, QString tag)
{

    // Setting up new file for the DB
    db =QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("/home/ilyas/Desktop/test_2.sqlite");
    db.open();

    QSqlQuery query(db);

    // Creating the table that will hold all the tasks
    QString create {"CREATE TABLE IF NOT EXISTS task (description VARCHAR(80), finished bool, date date, tag VARCHAR(10))"};
    if(!query.exec(create))
        QMessageBox::critical(this,"info","could not create table");

    //Insert into the Task table values inserted in [setdatabase(des,isF,Date,tag)]
    QString insert {"INSERT INTO task values ('%1','%2','%3','%4')"};
    if(!query.exec(insert.arg(description).arg(finished).arg(date).arg(tag)))
        QMessageBox::critical(this,"info","insert not create table");


}



