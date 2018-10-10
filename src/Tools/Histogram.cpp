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


    ui->chartView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    ui->chartView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    
}

Histogram::~Histogram()
{
}

void Histogram::display(QImage * image)
{
    show();

    std::map<size_t, size_t> colorCount;

    for (int i = 0; i < 256; i++) {
        colorCount[i] = 0;
    }

    for (int i = 0; i < image->width(); i++) {
        for (int j = 0; j < image->height(); j++) {
            auto val = qGray(image->pixel(i, j));
            colorCount[val]++;
        }
    }
    QStringList categories;


    std::vector<QBarSet*> sets(colorCount.size());
    QBarSeries *series = new QBarSeries();
    series->setBarWidth(1);
    
    for (int i = 0; i < colorCount.size(); i++) {
        sets[i] = new QBarSet(std::to_string(i).c_str());

        *sets[i] << colorCount[i];
        sets[i]->setBrush(QColor(i, i, i));
        sets[i]->setBorderColor(QColor(0, 0, 0));
       
        series->append(sets[i]);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Simple barchart example");
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setBackgroundBrush(QBrush(QColor(192, 210, 210)));
    

    QBarCategoryAxis *axis = new QBarCategoryAxis();
    chart->createDefaultAxes();
    axis->append(categories);
    chart->setAxisX(axis, series);

    chart->legend()->setVisible(false);
    ui->chartView->setChart(chart);
    ui->chartView->setRenderHint(QPainter::Antialiasing);
}
