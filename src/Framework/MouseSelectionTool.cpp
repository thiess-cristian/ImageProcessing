#include "MouseSelectionTool.h"
#include "ProcessedImageScene.h"

#include <qgraphicssceneevent.h>
#include <qgraphicsitem.h>

MouseSelectionTool::MouseSelectionTool(QObject* parent):QObject(parent)
{
}

MouseSelectionTool::~MouseSelectionTool()
{}

void MouseSelectionTool::processMouseMove(QGraphicsSceneMouseEvent * mouseEvent)
{
    auto imageScene = dynamic_cast<ProcessedImageScene*>(parent());


    m_selection.setWidth(mouseEvent->scenePos().x() - m_selection.x());
    m_selection.setHeight(mouseEvent->scenePos().y() - m_selection.y());

    if (m_addedRect != nullptr) {
        imageScene->removeItem(m_addedRect);
    }

    m_addedRect = imageScene->addRect(m_selection, QPen(Qt::DashLine));
}

void MouseSelectionTool::processMousePress(QGraphicsSceneMouseEvent * mouseEvent)
{
    m_selection.setX(mouseEvent->scenePos().x());
    m_selection.setY(mouseEvent->scenePos().y());

    auto imageScene = dynamic_cast<ProcessedImageScene*>(parent());

    m_addedRect = imageScene->addRect(m_selection, QPen(Qt::DashLine));
}

void MouseSelectionTool::processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent)
{
    auto imageScene = dynamic_cast<ProcessedImageScene*>(parent());

    
    m_selection.setWidth(mouseEvent->scenePos().x() - m_selection.x());
    m_selection.setHeight(mouseEvent->scenePos().y() - m_selection.y());

    QImage* newImage = new QImage(imageScene->getImage()->copy(m_selection));

    emit imageScene->selectedImage(newImage);

    m_selection.setWidth(0);
    m_selection.setHeight(0);
    imageScene->removeItem(m_addedRect);
}
