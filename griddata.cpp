#include "griddata.h"
#include "logging.h"
#include <QDebug>
#include <boost/scoped_array.hpp>
#include <cassert>
#include <algorithm>
#include <limits>



GridData::GridData(QObject * parent) :
    QObject(parent),
    xSize_(1)
{
}

GridData::GridData(const float * data, size_type xSize, size_type ySize, QObject * parent) :
    QObject(parent)
{
    set(data, xSize, ySize);
}

GridData::~GridData()
{
}

void GridData::set(const float * data, size_type xSize, size_type ySize)
{
    LOG_FUNCTION

    imageData_.clear();

    size_type size = xSize * ySize;

    if ( data_.size() != size )
        data_.resize(size);
    std::copy(data, data + size, data_.begin());

    xSize_ = xSize;

    emit newData(this);
}

void GridData::set(const QString & parameter, const float * data, unsigned xSize, unsigned ySize)
{
       parameter_ = parameter;
       qDebug() << "Parameter: " << parameter_;
       set(data, xSize, ySize);
}

GridData::size_type GridData::size() const
{
    return data_.size();
}

GridData::size_type GridData::xSize() const
{
    return xSize_;
}

GridData::size_type GridData::ySize() const
{
    assert(size() % xSize_ == 0);
    return size() / xSize_;
}

float GridData::value(size_type x, size_type y) const
{
    if ( x >= xSize() or y >= ySize() )
        return std::numeric_limits<float>::quiet_NaN();

    size_type index = (y * xSize()) + x;
    return data_[index];
}

float GridData::min() const
{
    return * std::min_element(data_.begin(), data_.end());
}

float GridData::max() const
{
    return * std::max_element(data_.begin(), data_.end());
}


namespace
{
uchar scale(float value, float min, float max)
{
    if ( value < min )
        return 0;
    if ( value >= max )
        return 255;

    float range = max - min;
    float step = range / 256;
    return (value - min) / step;
}
}

QImage GridData::getImage() const
{
    LOG_FUNCTION

    if ( imageData_.empty() )
    {
        imageData_.resize(data_.size());
        float min = this->min();
        float max = this->max();
        for ( unsigned i = 0; i < data_.size(); ++ i )
            imageData_[i] = (uchar) scale(data_[i], min, max);
    }
    return QImage(&imageData_[0], xSize(), ySize(), xSize(), QImage::Format_Indexed8);
}
