#include "gridmetadatadisplay.h"

#include <QGridLayout>
#include <QLabel>
#include "griddata.h"


GridMetadataDisplay::GridMetadataDisplay(GridData * gridData, QWidget *parent) :
    QWidget(parent)
{
    maxValue = new QLabel(this);
    minValue = new QLabel(this);
    currentValue = new QLabel(this);

    QGridLayout * layout = new QGridLayout(this);
    layout->addWidget(new QLabel("High"), 0, 0);
    layout->addWidget(maxValue, 0, 1);
    layout->addWidget(new QLabel("Low"), 1, 0);
    layout->addWidget(minValue, 1, 1);
    layout->addWidget(new QLabel("Current"), 2, 0);
    layout->addWidget(currentValue, 2, 1);

    connect(gridData, SIGNAL(newData(GridData)), SLOT(refresh(GridData)));
}

void GridMetadataDisplay::refresh(const GridData & gridData)
{
    maxValue->setText(QString::number(gridData.max()));
    minValue->setText(QString::number(gridData.min()));
    currentValue->setText("-");
}

void GridMetadataDisplay::setCurrent(float value)
{
    currentValue->setText(QString::number(value));
}
