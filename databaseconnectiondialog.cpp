/*
 wdbview

 Copyright (C) 2013 met.no

 Contact information:
 Norwegian Meteorological Institute
 Box 43 Blindern
 0313 OSLO
 NORWAY
 E-mail: post@met.no

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 MA  02110-1301, USA
*/

#include "databaseconnectiondialog.h"
#include "logging.h"
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
    LOG_FUNCTION

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
