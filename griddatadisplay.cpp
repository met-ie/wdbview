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

#include "griddatadisplay.h"
#include "logging.h"
#include <QtGui>
#include <QDebug>
#include <QColor>
#include <limits>



GridDataDisplay::GridDataDisplay(const GridData * gridData, QWidget *parent) :
    QLabel(parent),
    data_(gridData)
{    
}

void GridDataDisplay::refreshImage(const GridData * data)
{
    QSize lastSize = size();
    if ( ! pixmap() )
        lastSize = QSize(data->xSize(), data->ySize());

    QImage image = data->getImage();
    setPixmap(QPixmap::fromImage(image));

    setMouseTracking(true);

    //adjustSize();
    resize(lastSize);

    QPoint p = mapFromGlobal(QCursor::pos());
    emit mouseAtIndex(p.x(), p.y());
}

void GridDataDisplay::saveCurrentImage()
{
    const QPixmap * image = pixmap();
    if ( ! image )
    {
        QMessageBox::critical(this, "No image", "No image to save");
        return;
    }

    QString saveFile = QFileDialog::getSaveFileName(this, "Save file", "wdbview.png");
    qDebug() << saveFile;

    if ( not saveFile.isEmpty() )
    {
        if ( ! image->save(saveFile) )
            QMessageBox::critical(this, "Uanble to save", "An error occured when trying to save image " + saveFile, QMessageBox::Ok);
    }
}

void GridDataDisplay::zoomTo(double scaleFactor)
{
    resize(pixmap()->size() * scaleFactor);
}

void GridDataDisplay::mouseMoveEvent(QMouseEvent * event)
{
    QSize displaySize = size();
    QSize pixmapSize = pixmap()->size();
    double scale = displaySize.width() / pixmapSize.width();
    emit mouseAtIndex(event->x() / scale, event->y() / scale);
}

void GridDataDisplay::leaveEvent(QEvent *)
{
    emit mouseLeftDisplay();
}

//void GridDataDisplay::mouseReleaseEvent(QMouseEvent * event)
//{
//    switch ( event->button() )
//    {
//    case Qt::LeftButton:
//        zoomIn();
//        break;
//    case Qt::RightButton:
//        zoomOut();
//        break;
//    default:
//        break;
//    }
//}
