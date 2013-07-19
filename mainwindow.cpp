#include "mainwindow.h"
#include "dataselector.h"
#include "griddatadisplay.h"
#include <QtGui>
#include <algorithm>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget * displayArea_ = new QWidget(this);
    DataSelector * selector = new DataSelector(this);
    GridDataDisplay * display = new GridDataDisplay(this);

    QHBoxLayout * layout = new QHBoxLayout(displayArea_);
    layout->addWidget(selector);
    layout->addWidget(display);

    setCentralWidget(displayArea_);

    connect(selector, SIGNAL(selected(int,int,float*)), display, SLOT(setImage(int,int,float*)));
}

MainWindow::~MainWindow()
{   
}

