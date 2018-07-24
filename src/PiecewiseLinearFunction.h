#ifndef PIECEWISELINEARFUNCTION_H
#define PIECEWISELINEARFUNCTION_H
#include <QVector>
#include <QPoint>

class PiecewiseLinearFunction
{
public:
    PiecewiseLinearFunction();    

    QVector <QPointF> points;
    double posInfValue;
    double negInfValue;

    void addNewPoint(QPointF point);
    qreal getValue(qreal x);
    int getSize();

};

#endif // PIECEWISELINEARFUNCTION_H
