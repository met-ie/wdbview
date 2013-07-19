#include "griddatadisplay.h"
#include <QtGui>


#define LOG_FUNCTION struct L { L(const char * f) { qDebug() << f; }  ~L() { qDebug("done"); } } l(__func__);

GridDataDisplay::GridDataDisplay(QWidget *parent) :
    QLabel(parent)
{
}

void GridDataDisplay::setImage(int width, int height, float * data)
{
    LOG_FUNCTION

    int size = width * height;

    uchar * imageData = getData_(data, size);

    image_ = QImage(imageData, width, height, width, QImage::Format_Indexed8);

    setPixmap(QPixmap::fromImage(image_));
}

namespace
{
uchar scale(float value, float min, float max)
{
    if ( value < min )
        return 0;
    if ( value > max )
        return 0;

    float range = max - min;
    float step = range / 256;
    return (value - min) / step;
}
}

void GridDataDisplay::saveCurrentImage()
{
    QString saveFile = QFileDialog::getSaveFileName(this, "Save file", "wdbview.png");
    qDebug() << saveFile;

    if ( not saveFile.isEmpty() )
        if ( ! QPixmap::fromImage(image_).save(saveFile) )
            QMessageBox::critical(this, "Uanble to save", "An error occured when trying to save image " + saveFile, QMessageBox::Ok);
}


uchar * GridDataDisplay::getData_(float * data, int size) const
{
    LOG_FUNCTION

    float min = * std::min_element(data, data + size);
    float max = * std::max_element(data, data + size);

//    min = 99000;
//    max = 103000;


    qDebug() << "range: " << min << " - " << max;
    if ( min == max )
        qDebug("damn");

    uchar * ret = new uchar[size];

    for ( int i = 0; i < size; ++ i )
        ret[i] = (uchar) scale(data[i], min, max);

    return ret;
}
