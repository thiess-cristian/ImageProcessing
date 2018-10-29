#pragma once
#include "IMouseTool.h"
#include <qobject.h>
#include <qrect.h>

class QGraphicsRectItem;

class MouseSelectionTool:public QObject,public IMouseTool
{
public:
    MouseSelectionTool(QObject* parent);
    ~MouseSelectionTool();

    // Inherited via IMouseTool
    virtual void processMouseMove(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMousePress(QGraphicsSceneMouseEvent * mouseEvent) override;
    virtual void processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent) override;

private:
    QRect m_selection;
    QGraphicsRectItem* m_addedRect=nullptr;
};