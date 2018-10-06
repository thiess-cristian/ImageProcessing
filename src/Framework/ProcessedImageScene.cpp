#include "ProcessedImageScene.h"

#include "qgraphicsitem.h"
#include "qimage.h"

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
    if (m_image != nullptr) {
        delete m_image;
    }
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
