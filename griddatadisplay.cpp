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



GridDataDisplay::GridDataDisplay(GridData * gridData, QWidget *parent) :
    QLabel(parent),
    data_(gridData)
{    
    connect(data_, SIGNAL(newData(GridData)), SLOT(refreshImage()));
}

float GridDataDisplay::getCurrentMouseOverValue() const
{
    QPoint p = mapFromGlobal(QCursor::pos());
    //qDebug() << __func__ << ": " << p.x() << ", " <<  p.y() << " = " << data_->value(p.x(), p.y());
    return data_->value(p.x(), p.y());
}

void GridDataDisplay::refreshImage()
{
    QImage image = data_->getImage();
    setPixmap(QPixmap::fromImage(image));

    setMouseTracking(true);

    adjustSize();

    emit currentMouseOverValue(getCurrentMouseOverValue());
}

void GridDataDisplay::saveCurrentImage()
{
    QString saveFile = QFileDialog::getSaveFileName(this, "Save file", "wdbview.png");
    qDebug() << saveFile;

    if ( not saveFile.isEmpty() )
        if ( ! QPixmap::fromImage(data_->getImage()).save(saveFile) )
            QMessageBox::critical(this, "Uanble to save", "An error occured when trying to save image " + saveFile, QMessageBox::Ok);
}

void GridDataDisplay::mouseMoveEvent(QMouseEvent * event)
{
    emit currentMouseOverValue(data_->value(event->x(), event->y()));
}

void GridDataDisplay::leaveEvent(QEvent *)
{
    emit currentMouseOverValue(std::numeric_limits<float>::quiet_NaN());
}
