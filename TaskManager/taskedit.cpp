#include "taskedit.h"
#include "ui_taskedit.h"
#include <QMessageBox>

TaskEdit::TaskEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TaskEdit)
{
    ui->setupUi(this);
    setCurrentDate();
}

TaskEdit::~TaskEdit()
{
    delete ui;
}
void TaskEdit::setCurrentDate()
{

    QDate date = QDate::currentDate();
    ui->dateEdit->setDate(date);
}

void TaskEdit::on_buttonBox_accepted()
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
void TaskEdit::setdatabase(QString description, bool finished, QString date, QString tag)
{
    db =QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("/home/ilyas/Desktop/mvcDB.sqlite");
    db.open();

      QSqlQuery query(db);


    QString create {"CREATE TABLE IF NOT EXISTS task (description VARCHAR(80), finished bool, date date, tag VARCHAR(10))"};
    if(!query.exec(create))
    {
        QMessageBox::critical(this,"info","could not create table");

    }


    QString insert {"INSERT INTO task values ('%1','%2','%3','%4')"};
    if(!query.exec(insert.arg(description).arg(finished).arg(date).arg(tag)))
    {
        QMessageBox::critical(this,"info","insert not create table");
    }


}

