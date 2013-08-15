#ifndef GRIDDATADISPLAYWIDGET_H
#define GRIDDATADISPLAYWIDGET_H

#include <QWidget>

class GridDataDisplay;


class GridDataDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridDataDisplayWidget(QWidget *parent = 0);

signals:
    void newMinMax(float min, float max) const;

public slots:

    /**
     * Set current image
     */
    void setImage(int width, int height, float * data);

    /**
     * Save currently displayed image to file
     */
    void saveCurrentImage();

private:
    GridDataDisplay * display_;
};

#endif // GRIDDATADISPLAYWIDGET_H
