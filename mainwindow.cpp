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

#include "mainwindow.h"
#include "dataselector.h"
#include "gridmetadatadisplay.h"
#include "griddatadisplaywidget.h"
#include "griddata.h"
#include <QtGui>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget * displayArea_ = new QWidget(this);
    DataSelector * selector = new DataSelector(this);


    GridData * gridData = new GridData(this);

    GridDataDisplayWidget * display = new GridDataDisplayWidget(gridData, this);
    GridMetadataDisplay * metadataDisplay = new GridMetadataDisplay(gridData, this);

    QHBoxLayout * layout = new QHBoxLayout(displayArea_);
    QVBoxLayout * metadataLayout = new QVBoxLayout;
    metadataLayout->addWidget(selector);
    metadataLayout->addWidget(metadataDisplay);
    layout->addLayout(metadataLayout);
    layout->addWidget(display);

    setCentralWidget(displayArea_);

    connect(selector, SIGNAL(selected(const float*,uint,uint)), gridData, SLOT(set(const float*,uint,uint)));

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

    statusBar()->showMessage("Ready", 500);

    connect(gridData, SIGNAL(newData(GridData)), SLOT(updateStatus(GridData)));

    connect(display, SIGNAL(currentMouseOverValue(float)), SLOT(updateCurrentValue(float)));
    connect(display, SIGNAL(currentMouseOverValue(float)), metadataDisplay, SLOT(setCurrent(float)));
}

MainWindow::~MainWindow()
{   
}

void MainWindow::updateStatus(const GridData & gridData)
{
    QString message = QString("Low: ") + QString::number(gridData.min()) + QString(" High: ") + QString::number(gridData.max());
    statusBar()->showMessage(message);
}

void MainWindow::updateCurrentValue(float mouseovervalue)
{
    QString message = QString("Current value: ") + QString::number(mouseovervalue);
    statusBar()->showMessage(message);
}
