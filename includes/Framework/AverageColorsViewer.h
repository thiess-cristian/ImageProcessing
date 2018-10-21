#pragma once
#include "IMouseTool.h"
#include <memory>
#include <qwidget.h>

class Ui_GraphWindow;
class QGraphicsScene;
class AverageColors;

class AverageColorsViewer :public QWidget
{
public:
    AverageColorsViewer(const AverageColors& colors);
    ~AverageColorsViewer();
    void addValues(double means,double deviation);

private:
    std::unique_ptr<Ui_GraphWindow> m_ui;
    QGraphicsScene* m_averageColorsScene;

    const AverageColors& m_colors;
};