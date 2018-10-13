#include "ProcessedImageScene.h"
#include "MouseSelectionTool.h"

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

void ProcessedImageScene::addImage(QImage * image, bool grey)
{
    if (grey) {

        int width = image->width();
        int height = image->height();
        

        QImage* newImage = new QImage(width, height, QImage::Format_RGB32);

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                char cl = qGray(image->pixel(i, j));
                newImage->setPixelColor(i, j, qRgb(cl, cl, cl));
            }
        }

        m_image = newImage;
        delete image;
    } else {
        m_image=image;
    }
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


void ProcessedImageScene::getSelectedImage(QImage* image)
{
    clear();
    addImage(image);
}
