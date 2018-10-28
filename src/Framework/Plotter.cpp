#include "Plotter.h"
#include "ProcessedImageScene.h"
#include <iostream>

#include <vector>
#include <qcolor.h>
#include <qgraphicssceneevent.h>

Plotter::Plotter(QObject* parent):
    QObject(parent),
    m_viewer()
{

}

Plotter::~Plotter()
{
}

void Plotter::processMouseMove(QGraphicsSceneMouseEvent * mouseEvent)
{
    size_t y = mouseEvent->scenePos().y();
    plot(y);
    emit coordChanged(y);
}

void Plotter::processMousePress(QGraphicsSceneMouseEvent * mouseEvent)
{
    size_t y = mouseEvent->scenePos().y();
    plot(y);
    emit coordChanged(y);
}

void Plotter::processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent)
{}

void Plotter::plot(size_t y)
{
    ProcessedImageScene* scene = dynamic_cast<ProcessedImageScene*>(QObject::parent());
    QImage* image = scene->getImage();
    std::map<size_t, QColor> colorLine;

    
    std::cout << y<<" "<<std::endl;
    for (int x = 0; x < image->width(); x++) {
        colorLine[x] = image->pixelColor(x, y);
    }
    m_viewer.update(colorLine);
}
