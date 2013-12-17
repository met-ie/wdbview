#include "griddatadisplaywidget.h"
#include "griddatadisplay.h"
#include <QVBoxLayout>
#include <QScrollArea>
#include <QMouseEvent>

GridDataDisplayWidget::GridDataDisplayWidget(GridData * gridData, QWidget *parent) :
    QWidget(parent)
{
    display_ = new GridDataDisplay(gridData, this);
    display_->setBackgroundRole(QPalette::Base);
    display_->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    display_->setScaledContents(true);

    QScrollArea * scrollArea = new QScrollArea(this);
    scrollArea->setBackgroundRole(QPalette::Dark);
    scrollArea->setWidget(display_);

    QVBoxLayout * mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(scrollArea);

    connect(display_, SIGNAL(currentMouseOverValue(float)), SIGNAL(currentMouseOverValue(float)));
}

float GridDataDisplayWidget::getCurrentMouseOverValue() const
{
    return display_->getCurrentMouseOverValue();
}


void GridDataDisplayWidget::saveCurrentImage()
{
    display_->saveCurrentImage();
}
