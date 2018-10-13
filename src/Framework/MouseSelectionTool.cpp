#include "MouseSelectionTool.h"
#include "ProcessedImageScene.h"

#include <qgraphicssceneevent.h>

MouseSelectionTool::MouseSelectionTool(QObject* parent):QObject(parent)
{

}

MouseSelectionTool::~MouseSelectionTool()
{}

void MouseSelectionTool::processMouseMove(QGraphicsSceneMouseEvent * mouseEvent)
{

}

void MouseSelectionTool::processMousePress(QGraphicsSceneMouseEvent * mouseEvent)
{
    m_selection.setX(mouseEvent->scenePos().x());
    m_selection.setY(mouseEvent->scenePos().y());
}

void MouseSelectionTool::processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent)
{
    auto imageScene = dynamic_cast<ProcessedImageScene*>(parent());

    m_selection.setWidth(mouseEvent->scenePos().x() - m_selection.x());
    m_selection.setHeight(mouseEvent->scenePos().y() - m_selection.y());

    QImage* newImage = new QImage(imageScene->getImage()->copy(m_selection));

    emit imageScene->selectedImage(newImage);
}
