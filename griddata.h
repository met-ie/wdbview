#ifndef GRIDDATA_H
#define GRIDDATA_H

#include <QObject>
#include <QImage>
#include <boost/noncopyable.hpp>
#include <vector>


/**
 * Data for a single grid, with metainformation.
 */
class GridData : public QObject, boost::noncopyable
{
    Q_OBJECT
public:

    typedef unsigned size_type;

    GridData(QObject * parent = 0);
    GridData(const float * data, size_type xSize, size_type ySize, QObject * parent = 0);
    virtual ~GridData();

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


public slots:
    /**
     * Update contents of the object
     */
    void set(const float * data, unsigned xSize, unsigned ySize);

signals:
    /**
     * Emitted when the contained data has changed
     */
    void newData(const GridData & gridData);


private:
    std::vector<float> data_;
    mutable std::vector<uchar> imageData_;
    size_type xSize_;
};

#endif // GRIDDATA_H
