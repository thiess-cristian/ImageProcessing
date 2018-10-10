#pragma once

#include <memory>
#include <qwidget.h>

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

};

