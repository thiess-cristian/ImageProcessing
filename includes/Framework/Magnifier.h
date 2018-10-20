#pragma once
#include "IMouseTool.h"
#include "MagnifierViewer.h"
#include "qobject.h"

class QImage;

class Magnifier:public QObject, public IMouseTool
{
    Q_OBJECT
public:
    Magnifier(QObject* parent);
    ~Magnifier();

    // Inherited via IMouseTool
    virtual void processMouseMove(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMousePress(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent) override;

private:

    const size_t NumOfLines = 10;
    const size_t NumOfCols = 10;

    MagnifierViewer m_viewer;

};