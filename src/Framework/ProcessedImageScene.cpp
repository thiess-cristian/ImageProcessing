#include "ProcessedImageScene.h"
#include "MouseSelectionTool.h"
#include "Magnifier.h"

#include "qgraphicsitem.h"
#include "qimage.h"
#include "qgraphicssceneevent.h"
#include <iostream>

ProcessedImageScene::ProcessedImageScene():m_image(nullptr)
{
}

ProcessedImageScene::~ProcessedImageScene()
{
    if (m_image != nullptr) {
        delete m_image;
    }
}

void ProcessedImageScene::addImage(QImage * image)
{
    m_image=image; 
    QGraphicsPixmapItem* item = new QGraphicsPixmapItem(QPixmap::fromImage(*m_image));
    addItem(item);
}

QImage * ProcessedImageScene::getImage() const
{
    return m_image;
}

void ProcessedImageScene::toggleSelection()
{
    m_mouseToolEnabled = !m_mouseToolEnabled;
    if (m_mouseToolEnabled) {
        m_mouseTool.release();
        m_mouseTool.reset(new MouseSelectionTool(this));
    } else {
        m_mouseTool.release();
    }
}

void ProcessedImageScene::toggleMagnifier()
{
    m_mouseToolEnabled = !m_mouseToolEnabled;
    if (m_mouseToolEnabled) {
        m_mouseTool.release();
        m_mouseTool.reset(new Magnifier(this));
    } else {
        m_mouseTool.release();
    }
}

void ProcessedImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_mouseTool != nullptr) {
        m_mouseTool->processMouseMove(mouseEvent);
    }
}
void ProcessedImageScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (m_mouseTool != nullptr) {
        m_mouseTool->processMousePress(mouseEvent);
    }
}

void ProcessedImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_mouseTool != nullptr) {
        m_mouseTool->processMouseRelease(mouseEvent);
    }
}

void ProcessedImageScene::setSelectedImage(QImage* image)
{
    clear();
    addImage(image);
}
