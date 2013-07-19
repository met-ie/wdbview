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

#include "dataselector.h"
#include "databaseconnectiondialog.h"
#include <QtGui>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <stdexcept>


DataSelector::DataSelector(QWidget *parent) :
    QWidget(parent),
    model_(0),
    connectionDialog_(0)
{
    view_ = new QTableView(this);
    view_->setSortingEnabled(true);
    view_->setSelectionBehavior(QTableView::SelectRows);
    connect(view_, SIGNAL(activated(QModelIndex)), SLOT(entryActivated(QModelIndex)));

    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(view_);

    connectToDatabase();
}

DataSelector::~DataSelector()
{
}

void DataSelector::connectToDatabase()
{
    if ( ! connectionDialog_ )
        connectionDialog_ = new DatabaseConnectionDialog(this);

    if ( connectionDialog_->getDatabase(database_) )
        refresh();
}

void DataSelector::refresh()
{
    delete model_;
    model_ = new QSqlQueryModel(view_);
    model_->setQuery("SELECT wci.begin('wdb'); SELECT value, dataprovidername, placename, referencetime, validtimeto, valueparametername, dataversion FROM wci_int.gridvalue_v", database_);

    view_->setModel(model_);
    view_->hideColumn(0);
    view_->resizeColumnsToContents();
    connect(view_->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(entryActivated(QItemSelection,QItemSelection)));
}

void DataSelector::entryActivated(const QModelIndex & index)
{
    QModelIndex i = index.sibling(index.row(), 0);
    QVariant vdata = model_->data(i);

    QString q = "SELECT wci.begin('wdb'); SELECT grid, numberx, numbery FROM wci.fetch(" + QString::number(vdata.toLongLong()) + ", NULL::wci.grid)";
    QSqlQuery query = database_.exec(q);

    if ( not query.next() )
        return;
    QSqlRecord record = query.record();
    int w = record.value(1).toDouble();
    int h = record.value(2).toDouble();

    qDebug() << vdata.toLongLong() << ":\t" << w << ", " << h;

    QVariant grid = record.value(0);
    QByteArray bdata = grid.toByteArray();
    float * data = (float *) bdata.data();

    if ( ! data )
        qDebug("No data");
    else
        emit selected(w, h, data);
}

void DataSelector::entryActivated(const QItemSelection & selection, const QItemSelection & old)
{
    QModelIndexList modelIndexes = selection.indexes();
    if ( not modelIndexes.empty() )
        entryActivated(modelIndexes.front());
}
