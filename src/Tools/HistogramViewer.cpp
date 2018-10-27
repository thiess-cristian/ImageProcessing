#include "HistogramViewer.h"
#include "ui_GraphWindow.h"

#include <qwidget.h>
#include <qbarset.h>
#include <qbarseries.h>
#include <iostream>
#include <vector>
#include <map>

HistogramViewer::HistogramViewer(const IHistogram& histogram):m_histogram(histogram)
{
    ui = std::make_unique<Ui_GraphWindow>();
    ui->setupUi(this);
    setAttribute(Qt::WA_DeleteOnClose, true); // delete the object after the window is closed   

    m_barSets.resize(256);

    m_series = new QBarSeries();
    m_series->setBarWidth(1);

    m_chart = new QChart();

    m_chart->setTitle("Histogram");
    m_chart->setAnimationOptions(QChart::SeriesAnimations);
    m_chart->setBackgroundBrush(QBrush(QColor(192, 210, 210)));
    m_chart->setMargins(QMargins(0, 0, 0, 0));
    m_chart->legend()->setVisible(false);
  
    ui->chartView->setChart(m_chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}

HistogramViewer::~HistogramViewer()
{
    delete m_chart;
    m_series->clear();
    delete m_series;
}

void HistogramViewer::display()
{
    show();

    auto histogram = m_histogram.getHistogramValues();


    auto setBarsColor = [&](auto barSets,auto i) {
        if (typeid(m_histogram) == typeid(GrayscaleHistogram)) {
            barSets->setBrush(QColor(i, i, i));
            barSets->setBorderColor(QColor(i, i, i));
        } else if (typeid(m_histogram) == typeid(ValueHistogram)) {
            barSets->setBrush(QColor(0, 0, 0));
            barSets->setBorderColor(QColor(0, 0, 0));
        }
    };

    for (size_t i = 0; i <256; i++) {
        m_barSets[i] = new QBarSet("");
        *m_barSets[i] << histogram[i];
        setBarsColor(m_barSets[i], i);
       
        m_series->append(m_barSets[i]);
    } 

    m_chart->addSeries(m_series);
    m_chart->createDefaultAxes();
}
