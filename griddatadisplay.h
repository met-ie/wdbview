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

#ifndef GRIDDATADISPLAY_H
#define GRIDDATADISPLAY_H

#include "griddata.h"
#include <QLabel>

/**
 * Display area for grid images
 */
class GridDataDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit GridDataDisplay(GridData * gridData, QWidget *parent = 0);

    float getCurrentMouseOverValue() const;

signals:
    void newMinMax(float min, float max) const;
    void currentMouseOverValue(float value) const;

public slots:

    void refreshImage();

    /**
     * Save currently displayed image to file
     */
    void saveCurrentImage();


protected:
    void mouseMoveEvent(QMouseEvent * event);

private:
    GridData * data_;
};

#endif // GRIDDATADISPLAY_H
