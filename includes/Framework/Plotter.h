#pragma once

#include "IMouseTool.h"
#include "PlotterViewer.h"
#include <qobject.h>

class Plotter :public QObject, public IMouseTool
{
    Q_OBJECT
public:
    Plotter(QObject* parent);
    ~Plotter();

    // Inherited via IMouseTool
    virtual void processMouseMove(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMousePress(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent) override;

public slots:
    void plot(size_t y);

signals:
    void coordChanged(size_t y);

private:
    PlotterViewer m_viewer;
};