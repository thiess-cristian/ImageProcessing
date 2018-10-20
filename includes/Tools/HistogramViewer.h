#pragma once

#include "Histogram.h"

#include <memory>
#include <vector>
#include <map>
#include <qwidget.h>
#include <qbarseries.h>

class Ui_GraphWindow;
class QImage;

class HistogramViewer:public QWidget
{
public:
    HistogramViewer(const Histogram& histogram);
    ~HistogramViewer();

    void display();

private:
    std::unique_ptr<Ui_GraphWindow> ui;

    QtCharts::QBarSeries* m_series;
    std::vector<QtCharts::QBarSet*> m_barSets;
    QtCharts::QChart *m_chart;

    const Histogram& m_histogram;
};

