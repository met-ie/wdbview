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

#ifndef DATABASECONNECTIONDIALOG_H
#define DATABASECONNECTIONDIALOG_H

#include <QDialog>
#include <QtSql/QSqlDatabase>


class QSqlDatabase;
class QLineEdit;


/**
 * Dialog for specifying a database to connect to
 */
class DatabaseConnectionDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DatabaseConnectionDialog(QWidget *parent = 0);

    /**
     * Display dialog, and unless cancelled, connect to database.
     *
     * @param out This object will be assigned the database connection
     * @returns true on a successful connect, false otherwise.
     */
    bool getDatabase(QSqlDatabase & out);


private:
    QLineEdit * nameEdit;
    QLineEdit * userEdit;
    QLineEdit * hostEdit;
    QLineEdit * portEdit;
};

#endif // DATABASECONNECTIONDIALOG_H
