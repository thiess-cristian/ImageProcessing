#pragma once
#include "IMouseTool.h"

#include <qobject.h>
#include <map>
#include <memory>

class AverageColorsViewer;

class AverageColors :public QObject,public IMouseTool
{
    Q_OBJECT
public:
    AverageColors(QObject* parent);
    ~AverageColors();

    double getMean()const;
    double getSquaredDeviation()const;

    // Inherited via IMouseTool
    virtual void processMouseMove(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMousePress(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent) override;

private:
    std::unique_ptr<AverageColorsViewer> m_viewer;

    double m_mean;
    double m_squaredDeviation;

};