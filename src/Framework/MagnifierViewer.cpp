#include "MagnifierViewer.h"
#include "MagnifiedPixel.h"
#include "ui_GraphWindow.h"

#include <qgraphicsscene.h>

MagnifierViewer::MagnifierViewer()
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    m_ui = std::make_unique<Ui_GraphWindow>();
    m_ui->setupUi(this);
    this->setFixedWidth(400);
    this->setFixedHeight(400);
    m_magnifiedPixels = new QGraphicsScene(this);
    m_ui->chartView->setScene(m_magnifiedPixels);

    QWidget::activateWindow();
    QWidget::show();
}

MagnifierViewer::~MagnifierViewer()
{
}

void MagnifierViewer::update(std::vector<MagnifiedPixel*> pixels)
{
    m_magnifiedPixels->clear();

    for (const auto& pixel : pixels) {
        m_magnifiedPixels->addItem(pixel);
    }
    m_ui->chartView->repaint();
    QWidget::show();   
}
