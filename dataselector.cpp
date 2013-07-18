#include "dataselector.h"
#include <QtGui>
#include <QtSql/QSqlQueryModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlRecord>
#include <stdexcept>


DataSelector::DataSelector(QWidget *parent) :
    QWidget(parent)
{
    database_ = QSqlDatabase::addDatabase("QPSQL");
    database_.setDatabaseName("wdb");

    if ( ! database_.open() )
        throw std::runtime_error("unable to connect to database");

    model_ = new QSqlQueryModel;
    model_->setQuery("SELECT wci.begin('wdb'); SELECT value, dataprovidername, placename, referencetime, validtimeto, valueparametername, dataversion FROM wci_int.gridvalue_v", database_);

    view_ = new QTableView(this);
    view_->setSortingEnabled(true);
    view_->setModel(model_);
    view_->hideColumn(0);
    view_->setSelectionBehavior(QTableView::SelectRows);
    view_->resizeColumnsToContents();
    connect(view_, SIGNAL(activated(QModelIndex)), SLOT(entryActivated(QModelIndex)));
    connect(view_->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)), SLOT(entryActivated(QItemSelection,QItemSelection)));


    QHBoxLayout * layout = new QHBoxLayout(this);
    layout->addWidget(view_);
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
