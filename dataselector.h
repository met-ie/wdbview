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
