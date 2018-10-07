#include "ProcessedImageScene.h"

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
    m_selectionEnabled = !m_selectionEnabled;
}

void ProcessedImageScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
   // std::cout << mouseEvent->scenePos().x()<<" "<< mouseEvent->scenePos().x()<<std::endl;

}
void ProcessedImageScene::mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent)
{
    if (m_selectionEnabled) {

        m_selection.setX(mouseEvent->scenePos().x());
        m_selection.setY(mouseEvent->scenePos().y());
    }
}

void ProcessedImageScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (m_selectionEnabled) {

        m_selection.setWidth(mouseEvent->scenePos().x()-m_selection.x());
        m_selection.setHeight(mouseEvent->scenePos().y()-m_selection.y());
        
        QImage* newImage = new QImage(m_image->copy(m_selection));

        emit selectedImage(newImage);
    }
}


void ProcessedImageScene::getSelectedImage(QImage* image)
{
    clear();
    addImage(image);
}
