#pragma once

#include <qwidget.h>
#include <memory>
#include <map>
#include <qlineseries.h>
#include <qchart.h>

class Ui_GraphWindow;
class QColor;

class PlotterViewer :public QWidget
{
public:
    PlotterViewer();
    ~PlotterViewer();

    void update(const std::map<size_t,QColor>& values);

private:
    QtCharts::QLineSeries* blueSeries ;
    QtCharts::QLineSeries* greenSeries ;
    QtCharts::QLineSeries* redSeries ;
    QtCharts::QChart* chart;
    std::unique_ptr<Ui_GraphWindow> m_ui;
};