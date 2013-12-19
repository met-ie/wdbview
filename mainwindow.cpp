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
#include <limits>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      zoom_(1)
{
    QWidget * displayArea_ = new QWidget(this);
    DataSelector * selector = new DataSelector(this);

    gridData_ = selector->gridData();

    display = new GridDataDisplayWidget(gridData_, this);
    GridMetadataDisplay * metadataDisplay = new GridMetadataDisplay(this);

    QHBoxLayout * layout = new QHBoxLayout(displayArea_);
    QVBoxLayout * metadataLayout = new QVBoxLayout;
    metadataLayout->addWidget(selector);
    metadataLayout->addWidget(metadataDisplay);
    layout->addLayout(metadataLayout);
    layout->addWidget(display);

    setCentralWidget(displayArea_);

    connect(gridData_, SIGNAL(newData(const GridData*)), display, SLOT(refreshImage(const GridData *)));
    connect(gridData_, SIGNAL(newData(const GridData*)), metadataDisplay, SLOT(refresh(const GridData *)));
    connect(selector, SIGNAL(selected(const float*,uint,uint)), gridData_, SLOT(set(const float*,uint,uint)));

    QAction * connectAction = new QAction("&Connect", this);
    connectAction->setShortcut(QKeySequence("CTRL+O"));
    connect(connectAction, SIGNAL(triggered()), selector, SLOT(connectToDatabase()));
    QAction * exitAction = new QAction("E&xit", this);
    connect(exitAction, SIGNAL(triggered()), SLOT(close()));
    QAction * saveImageAction = new QAction("&Save", this);
    saveImageAction->setShortcut(QKeySequence("CTRL+S"));
    connect(saveImageAction, SIGNAL(triggered()), display, SLOT(saveCurrentImage()));
    QAction * zoomInAction = new QAction("Zoom &in", this);
    zoomInAction->setShortcut((QKeySequence("CTRL++")));
    connect(zoomInAction, SIGNAL(triggered()), SLOT(zoomIn()));
    QAction * zoomOutAction = new QAction("Zoom &out", this);
    zoomOutAction->setShortcut((QKeySequence("CTRL+-")));
    connect(zoomOutAction, SIGNAL(triggered()), SLOT(zoomOut()));


    QMenu * fileMenu = menuBar()->addMenu("&File");
    fileMenu->addAction(connectAction);
    fileMenu->addAction(saveImageAction);
    fileMenu->addAction(exitAction);

    QMenu * viewMenu = menuBar()->addMenu("&View");
    viewMenu->addAction(zoomInAction);
    viewMenu->addAction(zoomOutAction);

    statusBar()->showMessage("Ready", 500);

    connect(gridData_, SIGNAL(newData(const GridData *)), SLOT(updateStatus(const GridData *)));

    connect(display, SIGNAL(mouseAtIndex(int,int)), SLOT(mouseAtImageIndex(int,int)));
    connect(display, SIGNAL(mouseLeftDisplay()), SLOT(mouseLeftImageDisplay()));

    connect(this, SIGNAL(mouseOverValue(float)), SLOT(updateCurrentValue(float)));
    connect(this, SIGNAL(mouseOverValue(float)), metadataDisplay, SLOT(setCurrent(float)));
}

MainWindow::~MainWindow()
{   
}

void MainWindow::updateStatus(const GridData * gridData)
{
    QString message = QString("Low: ") + QString::number(gridData->min()) + QString(" High: ") + QString::number(gridData->max());
    statusBar()->showMessage(message);
}

void MainWindow::updateCurrentValue(float mouseovervalue)
{
    QString message = QString("Current value: ") + QString::number(mouseovervalue);
    statusBar()->showMessage(message);
}

void MainWindow::mouseAtImageIndex(int x,int y) const
{
    emit mouseOverValue(gridData_->value(x, y));
}

void MainWindow::mouseLeftImageDisplay() const
{
    emit mouseOverValue(std::numeric_limits<float>::quiet_NaN());
}

void MainWindow::zoomIn()
{
    zoom_ *= 2;
    display->zoomTo(zoom_);
}

void MainWindow::zoomOut()
{
    zoom_ /= 2;
    display->zoomTo(zoom_);
}
