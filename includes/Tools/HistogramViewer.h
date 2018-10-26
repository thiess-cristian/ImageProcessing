#pragma once
#include "GrayscaleHistogram.h"

#include <memory>
#include <vector>
#include <map>
#include <qwidget.h>
#include <qbarseries.h>

class Ui_GraphWindow;

class HistogramViewer:public QWidget
{
public:
    HistogramViewer(const IHistogram& histogram);
    ~HistogramViewer();

    void display();

private:
    std::unique_ptr<Ui_GraphWindow> ui;

    QtCharts::QBarSeries* m_series;
    std::vector<QtCharts::QBarSet*> m_barSets;
    QtCharts::QChart *m_chart;

    const IHistogram& m_histogram;
};

