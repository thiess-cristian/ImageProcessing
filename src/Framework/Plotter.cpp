#include "Plotter.h"

Plotter::Plotter(QObject* parent):
    QObject(parent),
    m_viewer()
{

}

Plotter::~Plotter()
{
}

void Plotter::processMouseMove(QGraphicsSceneMouseEvent * mouseEvent)
{}

void Plotter::processMousePress(QGraphicsSceneMouseEvent * mouseEvent)
{}

void Plotter::processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent)
{}

void Plotter::plot(size_t y)
{

}
