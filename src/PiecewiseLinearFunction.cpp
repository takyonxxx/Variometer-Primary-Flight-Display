#include "PiecewiseLinearFunction.h"
#include <QDebug>
#include <QtMath>

PiecewiseLinearFunction::PiecewiseLinearFunction()
{
    posInfValue = 0.0;
    negInfValue = 0.0;
}


void PiecewiseLinearFunction::addNewPoint(QPointF point)
{
    if (point.x() == 0|| point.y() == 0) {
        return;
    } else if (points.size() == 0) {
        points.push_back(point);
        return;
    } else if (point.x() > (points.at(points.size() - 1)).x()) {
        points.push_back(point);
        return;
    } else {
        for (int i = 0; i < points.size(); i++) {
            if ((points.at(i)).x() > point.x()) {
                points.insert(i, point);
                return;
            }
        }
    }
}


qreal PiecewiseLinearFunction::getValue(qreal x)
{
    QPointF point;
    QPointF lastPoint = points.at(0);
    if (x <= lastPoint.x()) {
        return lastPoint.y();
    }
    for (int i = 1; i < points.size(); i++) {
        point = points.at(i);
        if (x <= point.x()) {
            double ratio = (x - lastPoint.x()) / (point.x() - lastPoint.x());
            return lastPoint.y() + ratio * (point.y() - lastPoint.y());
        }
        lastPoint = point;
    }
    return lastPoint.y();
}


int PiecewiseLinearFunction::getSize()
{
    return points.size();
}
