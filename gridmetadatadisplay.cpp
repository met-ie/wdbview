#include "gridmetadatadisplay.h"

#include <QGridLayout>
#include <QLabel>
#include "griddata.h"


GridMetadataDisplay::GridMetadataDisplay(QWidget *parent) :
    QWidget(parent)
{
    parameter = new QLabel(this);
    maxValue = new QLabel(this);
    minValue = new QLabel(this);
    currentValue = new QLabel(this);

    QGridLayout * layout = new QGridLayout(this);
    int row = 0;
    layout->addWidget(new QLabel("Parameter"), row, 0);
    layout->addWidget(parameter, row++, 1);
    layout->addWidget(new QLabel("High"), row, 0);
    layout->addWidget(maxValue, row++, 1);
    layout->addWidget(new QLabel("Low"), row, 0);
    layout->addWidget(minValue, row++, 1);
    layout->addWidget(new QLabel("Current"), row, 0);
    layout->addWidget(currentValue, row++, 1);
}

void GridMetadataDisplay::refresh(const GridData * gridData)
{
    parameter->setText(gridData->parameter());
    maxValue->setText(QString::number(gridData->max()));
    minValue->setText(QString::number(gridData->min()));
}

void GridMetadataDisplay::setCurrent(float value)
{
    QString toShow = "-";
    if ( value == value ) // not NaN
        toShow = QString::number(value);

    currentValue->setText(toShow);
}
