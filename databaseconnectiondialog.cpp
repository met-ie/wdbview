#include "databaseconnectiondialog.h"
#include <QtGui>



DatabaseConnectionDialog::DatabaseConnectionDialog(QWidget *parent) :
    QDialog(parent)
{
    setWindowTitle("Connect to database");


    QLabel * nameLabel = new QLabel("&Name", this);
    nameEdit = new QLineEdit("wdb", this);
    nameLabel->setBuddy(nameEdit);

    QLabel * userLabel = new QLabel("&User", this);
    userEdit = new QLineEdit(this);
    userLabel->setBuddy(userEdit);

    QLabel * hostLabel = new QLabel("&Host", this);
    hostEdit = new QLineEdit(this);
    hostLabel->setBuddy(hostEdit);

    QLabel * portLabel = new QLabel("&Port", this);
    portEdit = new QLineEdit(this);
    portEdit->setValidator(new QIntValidator(1, 65535, this));
    portLabel->setBuddy(portEdit);


    QDialogButtonBox * buttonBox = new QDialogButtonBox(QDialogButtonBox::Open | QDialogButtonBox::Cancel, Qt::Horizontal, this);
    connect(buttonBox, SIGNAL(accepted()), SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), SLOT(reject()));

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(new QLabel("Enter database characteristics", this));

    QGridLayout * layout = new QGridLayout;
    layout->addWidget(nameLabel, 0, 0);
    layout->addWidget(nameEdit, 0, 1);
    layout->addWidget(userLabel, 1, 0);
    layout->addWidget(userEdit, 1, 1);
    layout->addWidget(hostLabel, 2, 0);
    layout->addWidget(hostEdit, 2, 1);
    layout->addWidget(portLabel, 3, 0);
    layout->addWidget(portEdit, 3, 1);

    mainLayout->addLayout(layout);
    mainLayout->addWidget(buttonBox);

}

bool DatabaseConnectionDialog::getDatabase(QSqlDatabase & database)
{
    qDebug() << __func__;

    if ( exec() )
    {
        database.close();
        database = QSqlDatabase::addDatabase("QPSQL");
        if ( nameEdit->text().isEmpty() )
        {
            QMessageBox::critical(this, "Missing database name", "A name for the database must be specified", QMessageBox::Ok);
            return getDatabase(database);
        }
        database.setDatabaseName(nameEdit->text());
        if ( not userEdit->text().isEmpty() )
            database.setUserName(userEdit->text());
        if ( not hostEdit->text().isEmpty() )
            database.setHostName(hostEdit->text());
        if ( not portEdit->text().isEmpty() )
            database.setPort(portEdit->text().toInt());

        if ( ! database.open() )
        {
            QMessageBox::critical(this, "Unable to connect", "Unable to connect to database", QMessageBox::Ok);
            return getDatabase(database);
        }
        return true;
    }
    return false;
}
