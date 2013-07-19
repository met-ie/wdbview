#ifndef DATABASECONNECTIONDIALOG_H
#define DATABASECONNECTIONDIALOG_H

#include <QDialog>
#include <QtSql/QSqlDatabase>


class QSqlDatabase;
class QLineEdit;


class DatabaseConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DatabaseConnectionDialog(QWidget *parent = 0);

    bool getDatabase(QSqlDatabase & out);


private:
    QLineEdit * nameEdit;
    QLineEdit * userEdit;
    QLineEdit * hostEdit;
    QLineEdit * portEdit;
};

#endif // DATABASECONNECTIONDIALOG_H
