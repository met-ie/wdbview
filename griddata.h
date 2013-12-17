#ifndef GRIDDATA_H
#define GRIDDATA_H

#include <QImage>
#include <boost/noncopyable.hpp>
#include <vector>


/**
 * Data for a single grid, with metainformation.
 */
class GridData : boost::noncopyable
{
public:

    typedef std::vector<float>::size_type size_type;

    GridData();
    GridData(const float * data, size_type xSize, size_type ySize);
    ~GridData();

    bool empty() const { return data_.empty(); }
    size_type size() const;
    size_type xSize() const;
    size_type ySize() const;

    /// Get value of a single coordinate
    float value(size_type x, size_type y) const;

    /// Get lowest value in grid
    float min() const;

    /// Get highest value in grid
    float max() const;

    /// Get an image representation of this data
    QImage getImage() const;

    /**
     * Update contents of the object
     */
    void set(const float * data, size_type xSize, size_type ySize);

private:
    std::vector<float> data_;
    mutable std::vector<uchar> imageData_;
    size_type xSize_;
};

#endif // GRIDDATA_H
