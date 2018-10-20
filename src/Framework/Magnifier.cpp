#include "Magnifier.h"
#include "ProcessedImageScene.h"
#include "MagnifiedPixel.h"

#include <qgraphicssceneevent.h>
#include <vector>
#include <iostream>


Magnifier::Magnifier(QObject* parent) :
    QObject(parent), 
    m_viewer()
{
    
}

Magnifier::~Magnifier()
{

}

void Magnifier::processMouseMove(QGraphicsSceneMouseEvent * mouseEvent)
{

}

void Magnifier::processMousePress(QGraphicsSceneMouseEvent * mouseEvent)
{
    ProcessedImageScene* imageScene = dynamic_cast<ProcessedImageScene*>(parent());
    QImage* image = imageScene->getImage();

    int x = mouseEvent->scenePos().x();
    int y = mouseEvent->scenePos().y();

    std::vector<MagnifiedPixel*> pixels;
    int width = m_viewer.width()/NumOfLines-3;

    int lineSegment = NumOfLines / 2;
    int colSegment = NumOfCols / 2;
    
    int pixelX = 0;
    for (int i = x-lineSegment; i < x+lineSegment; i++) {
        int pixelY = 0;
        for (int j = y-colSegment; j < y+colSegment; j++) {
            QColor pixelColor = image->pixelColor(i, j);
            std::string value = QString::number(qGray(image->pixel(i, j))).toStdString();

            MagnifiedPixel* magnifiedPixel = new MagnifiedPixel(pixelX*width,pixelY*width,width,pixelColor,value);
            pixels.push_back(magnifiedPixel);

            pixelY++;

        }
        pixelX++;
    }
    std::cout << std::endl;
    
    m_viewer.update(pixels);
}

void Magnifier::processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent)
{

}
