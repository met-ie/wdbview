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
#include "griddata.h"
#include <QtGui>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>


DataSelector::DataSelector(QWidget *parent) :
    QWidget(parent),
    model_(0),
    connectionDialog_(0)
{
    gridData_ = new GridData(this);
    view_ = new QTreeView(this);
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

namespace
{
struct ModelFetcher
{
    ModelFetcher(QStandardItemModel & parent) :
        parent(parent)
    {}
    QStandardItem * operator () (int index)
    {
        return parent.item(index);
    }
    QStandardItemModel & parent;
};

struct ChildFetcher
{
    ChildFetcher(QStandardItem & parent) :
        parent(parent)
    {}
    QStandardItem * operator () (int index)
    {
        return parent.child(index);
    }
    QStandardItem & parent;
};

template<typename Fetcher>
QStandardItem * getEntry(const QVariant & entry, Fetcher fetcher)
{
    QString entryValue = entry.toString();
    if ( entryValue.isEmpty() )
        entryValue = "<no value>";
    QStandardItem * ret = 0;
    for ( int i = 0; ; ++ i )
    {
        QStandardItem * item = fetcher(i);
        if ( ! item )
            break;
        if ( item->text() == entryValue )
        {
            ret = item;
            break;
        }
    }
    if ( ! ret )
    {
        ret = new QStandardItem(entryValue);
        fetcher.parent.appendRow(ret);
    }
    return ret;
}

bool hasManyDataVersions(const QSqlQuery & /*query*/)
{
    return false;
}
}

void DataSelector::refresh()
{
    delete model_;

    QString queryStatement = "SELECT wci.begin('wdb'); ";
    queryStatement += "SELECT dataprovidername, placename, referencetime, valueparametername, dataversion, validtimeto, value ";
    queryStatement += "FROM wci.read(NULL,NULL, NULL,NULL, NULL,NULL, NULL,NULL::wci.returngid) ";
    queryStatement += "ORDER BY 1, 2, 3, 4, 5, 6";

    QSqlQuery query(queryStatement, database_);

    model_ = new QStandardItemModel(this);
    model_->setHorizontalHeaderLabels(QStringList("Data"));
    while ( query.next() )
    {
        QStandardItem * item;
        item = getEntry<ModelFetcher>(query.value(0), * model_);
        item = getEntry<ChildFetcher>(query.value(1), * item);
        item = getEntry<ChildFetcher>(query.value(2), * item);
        item = getEntry<ChildFetcher>(query.value(3), * item);
        if ( hasManyDataVersions(query) )
            item = getEntry<ChildFetcher>(query.value(4), * item);
        item = getEntry<ChildFetcher>(query.value(5), * item);
        item->setData(query.value(6), Qt::UserRole); // storing GID value in UserRole
    }

    view_->setModel(model_);
    //view_->expandAll();
    connect(view_->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(entryActivated(QItemSelection,QItemSelection)));
}

void DataSelector::entryActivated(const QModelIndex & index)
{
    if ( not index.isValid() )
        return;
    QStandardItem *	item = model_->itemFromIndex(index);
    if ( item->hasChildren() )
        return;

    QString parameter = item->parent()->text();

    //QModelIndex i = index.sibling(index.row(), 1);
    QVariant vdata = model_->data(index, Qt::UserRole); // getting GID value from UserRole

    QString q = "SELECT wci.begin('wdb'); SELECT grid, numberx, numbery FROM wci.fetch(" + vdata.toString() + ", NULL::wci.grid)";
    qDebug() << q;
    QSqlQuery query = database_.exec(q);

    if ( not query.next() )
        return;

    QSqlRecord record = query.record();
    int w = record.value(1).toDouble();
    int h = record.value(2).toDouble();

    qDebug() << vdata.toString() << ":\t" << w << ", " << h;

    QVariant grid = record.value(0);
    QByteArray bdata = grid.toByteArray();
    float * data = (float *) bdata.data();

    if ( ! data )
        qDebug("No data");
    else
    {
        gridData_->set(parameter, data, w, h);
        emit selected(* gridData_);
        emit selected(data, w, h);
    }
}

void DataSelector::entryActivated(const QItemSelection & selection, const QItemSelection & /*old*/)
{
    QModelIndexList modelIndexes = selection.indexes();
    if ( not modelIndexes.empty() )
        entryActivated(modelIndexes.front());
}
