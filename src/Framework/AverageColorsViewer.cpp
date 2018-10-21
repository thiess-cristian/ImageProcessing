#include "AverageColorsViewer.h"
#include "ui_GraphWindow.h"
#include "MagnifiedPixel.h"
#include "ProcessedImageScene.h"

#include <qobject.h>
#include <qgraphicsscene.h>

AverageColorsViewer::AverageColorsViewer(const AverageColors& colors):
    m_colors(colors)
{
    m_ui = std::make_unique<Ui_GraphWindow>();
    m_ui->setupUi(this);
    this->setFixedWidth(400);
    this->setFixedHeight(400);
    setAttribute(Qt::WA_DeleteOnClose, true); // delete the object after the window is closed   

    m_averageColorsScene = new QGraphicsScene(this);
    m_ui->chartView->setScene(m_averageColorsScene);
}

AverageColorsViewer::~AverageColorsViewer()
{}

void AverageColorsViewer::addValues(double mean, double deviation)
{
    m_averageColorsScene->addItem(new MagnifiedPixel(0, 0, 150, QColor(mean, mean, mean), "Mean "+std::to_string(mean)));
    m_averageColorsScene->addItem(new MagnifiedPixel(200, 0, 150, QColor(deviation, deviation, deviation), "Deviation "+std::to_string(deviation)));
}
