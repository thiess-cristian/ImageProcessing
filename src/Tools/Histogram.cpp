#include "Histogram.h"
#include "ui_GraphWindow.h"

#include <qwidget.h>
#include <qbarset.h>
#include <qbarseries.h>
#include <iostream>
#include <vector>
#include <map>


Histogram::Histogram()
{
    ui = std::make_unique<Ui_GraphWindow>();
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true); // delete the object after the window is closed   

    m_barSets.resize(256);

    m_series = new QBarSeries();
    m_series->setBarWidth(1);

    m_chart = new QChart();

    m_chart->setTitle("Grayscale histogram");
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setBackgroundBrush(QBrush(QColor(192, 210, 210)));
    m_chart->setMargins(QMargins(0, 0, 0, 0));
    m_chart->legend()->setVisible(false);
  
    ui->chartView->setChart(m_chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

Histogram::~Histogram()
{
}

void Histogram::display(QImage * image)
{
    show();
    for (size_t i = 0; i < image->width(); i++) {
        for (size_t j = 0; j < image->height(); j++) {
            auto val = qGray(image->pixel(i, j));
            m_colorCount[val]++;
        }
    }
    
    for (int i = 0; i <256; i++) {
        m_barSets[i] = new QBarSet("");
        *m_barSets[i] << m_colorCount[i];
        m_barSets[i]->setBrush(QColor(i, i, i));
        m_barSets[i]->setBorderColor(QColor(i, i, i));
       
        m_series->append(m_barSets[i]);
    } 

    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}
