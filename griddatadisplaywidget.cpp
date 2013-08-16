#include "griddatadisplaywidget.h"
#include "griddatadisplay.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMouseEvent>

GridDataDisplayWidget::GridDataDisplayWidget(QWidget *parent) :
    QWidget(parent)
{
    display_ = new GridDataDisplay(this);
    display_->setBackgroundRole(QPalette::Base);
    display_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display_->setScaledContents(true);

    QScrollArea * scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(display_);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    connect(display_, SIGNAL(newMinMax(float,float)), SIGNAL(newMinMax(float,float)));
    connect(display_, SIGNAL(currentMouseOverValue(float)), SIGNAL(currentMouseOverValue(float)));
}

void GridDataDisplayWidget::setImage(int width, int height, float * data)
{
    display_->setImage(width, height, data);
    display_->adjustSize();
}

void GridDataDisplayWidget::saveCurrentImage()
{
    display_->saveCurrentImage();
}
