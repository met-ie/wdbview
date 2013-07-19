#ifndef GRIDDATADISPLAY_H
#define GRIDDATADISPLAY_H

#include <QLabel>
#include <QtGui/QImage>


class GridDataDisplay : public QLabel
{
    Q_OBJECT
public:
    explicit GridDataDisplay(QWidget *parent = 0);

public slots:
    void setImage(int width, int height, float * data);

    void saveCurrentImage();
    
private:
    uchar * getData_(float * data, int size) const;

    QImage image_;
};

#endif // GRIDDATADISPLAY_H
