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

    QAction * connectAction = new QAction("&Connect", this);
    connectAction->setShortcut(QKeySequence("CTRL+O"));
    connect(connectAction, SIGNAL(triggered()), selector, SLOT(connectToDatabase()));
    QAction * exitAction = new QAction("E&xit", this);
    connect(exitAction, SIGNAL(triggered()), SLOT(close()));
    QAction * saveImageAction = new QAction("&Save", this);
    saveImageAction->setShortcut(QKeySequence("CTRL+S"));
    connect(saveImageAction, SIGNAL(triggered()), display, SLOT(saveCurrentImage()));


    QMenu * fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(connectAction);
    fileMenu->addAction(saveImageAction);
    fileMenu->addAction(exitAction);


}

MainWindow::~MainWindow()
{   
}

