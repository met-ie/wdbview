#ifndef GRIDDATADISPLAYWIDGET_H
#define GRIDDATADISPLAYWIDGET_H

#include <QWidget>

class GridData;
class GridDataDisplay;


class GridDataDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridDataDisplayWidget(GridData * gridData, QWidget *parent = 0);

signals:
    void currentMouseOverValue(float value) const;

public slots:

    /**
     * Save currently displayed image to file
     */
    void saveCurrentImage();

private:
    GridDataDisplay * display_;
};

#endif // GRIDDATADISPLAYWIDGET_H
