#ifndef GRIDDATADISPLAYWIDGET_H
#define GRIDDATADISPLAYWIDGET_H

#include <QWidget>

class GridData;
class GridDataDisplay;


class GridDataDisplayWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GridDataDisplayWidget(const GridData * gridData, QWidget *parent = 0);

signals:
    void currentMouseOverValue(float value) const;
    void mouseAtIndex(int x, int y) const;
    void mouseLeftDisplay() const;

public slots:

    void refreshImage(const GridData * data);

    /**
     * Save currently displayed image to file
     */
    void saveCurrentImage();

    void zoomTo(double scaleFactor);

private:
    GridDataDisplay * display_;
};

#endif // GRIDDATADISPLAYWIDGET_H
