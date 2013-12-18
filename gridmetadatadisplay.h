#ifndef GRIDMETADATADISPLAY_H
#define GRIDMETADATADISPLAY_H

#include <QWidget>


class GridData;
class QLabel;


class GridMetadataDisplay : public QWidget
{
    Q_OBJECT
public:
    explicit GridMetadataDisplay(QWidget *parent = 0);

public slots:
    void refresh(const GridData * gridData);
    void setCurrent(float value);

private:
    QLabel * parameter;
    QLabel * maxValue;
    QLabel * minValue;
    QLabel * currentValue;
};

#endif // GRIDMETADATADISPLAY_H
