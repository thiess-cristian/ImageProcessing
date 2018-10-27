#pragma once

#include <qwidget.h>
#include <memory>

class Ui_GraphWindow;

class PlotterViewer :public QWidget
{
public:
    PlotterViewer();
    ~PlotterViewer();

private:
    std::unique_ptr<Ui_GraphWindow> m_ui;
};