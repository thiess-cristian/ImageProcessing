#pragma once

#include <memory>
#include <vector>
#include <map>
#include <qwidget.h>
#include <qbarseries.h>

class Ui_GraphWindow;
class QImage;



class Histogram:public QWidget
{
public:
    Histogram();
    ~Histogram();

    void display(QImage* image);

private:
    std::unique_ptr<Ui_GraphWindow> ui;

    std::map<size_t, size_t> m_colorCount;
    QtCharts::QBarSeries* m_series;
    std::vector<QtCharts::QBarSet*> m_barSets;
    QtCharts::QChart *m_chart;

};

