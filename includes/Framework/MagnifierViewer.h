#pragma once

#include <vector>
#include <memory>
#include <qwidget.h>

class Ui_GraphWindow;
class MagnifiedPixel;
class QGraphicsScene;

class MagnifierViewer :public QWidget
{
public:
    MagnifierViewer();
    ~MagnifierViewer();

    void update(std::vector<MagnifiedPixel*> pixels);

private:
    std::unique_ptr<Ui_GraphWindow> m_ui;
    QGraphicsScene* m_magnifiedPixels;

};