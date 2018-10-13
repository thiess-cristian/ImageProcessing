#pragma once

class QGraphicsSceneMouseEvent;

class IMouseTool
{
public:
    virtual void processMouseMove(QGraphicsSceneMouseEvent *mouseEvent) =0;
    virtual void processMousePress(QGraphicsSceneMouseEvent *mouseEvent) = 0;
    virtual void processMouseRelease(QGraphicsSceneMouseEvent *mouseEvent) = 0;
};