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

#ifndef DATASELECTOR_H
#define DATASELECTOR_H

#include <QWidget>
#include <QtGui>
#include <QtSql/QSqlDatabase>


class QSqlQueryModel;
class DatabaseConnectionDialog;

class DataSelector : public QWidget
{
    Q_OBJECT
public:
    explicit DataSelector(QWidget *parent = 0);
    ~DataSelector();
    
public slots:
    void connectToDatabase();
    void refresh();

signals:
    void selected(int width, int height, float * data);

private slots:
    void entryActivated(const QModelIndex & index);
    void entryActivated(const QItemSelection & selection, const QItemSelection & old);

private:

    QSqlDatabase database_;
    QTableView * view_;
    QSqlQueryModel * model_;
    DatabaseConnectionDialog * connectionDialog_;
};

#endif // DATASELECTOR_H
