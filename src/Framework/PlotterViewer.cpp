#include "PlotterViewer.h"
#include "ui_GraphWindow.h"


PlotterViewer::PlotterViewer()
{
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    m_ui = std::make_unique<Ui_GraphWindow>();
    m_ui->setupUi(this);

    blueSeries = new QLineSeries();
    greenSeries = new QLineSeries();
    redSeries = new QLineSeries();

    chart = new QChart();
    chart->legend()->hide();
    chart->createDefaultAxes();
    chart->setTitle("Simple line chart example");

    chart->addSeries(blueSeries);
    chart->addSeries(greenSeries);
    chart->addSeries(redSeries);

    m_ui->chartView->setChart(chart);
    m_ui->chartView->setRenderHint(QPainter::Antialiasing);
    QWidget::activateWindow();
    QWidget::show();
}

PlotterViewer::~PlotterViewer()
{}

void PlotterViewer::update(const std::map<size_t, QColor>& values)
{
    delete blueSeries;
    delete greenSeries;
    delete redSeries;

    blueSeries = new QLineSeries();
    blueSeries->setColor(QColor(0,0,255));
    greenSeries = new QLineSeries();
    greenSeries->setColor(QColor(0, 255, 0));
    redSeries = new QLineSeries();
    redSeries->setColor(QColor(255, 0, 0));

    for (const auto& color : values) {
        
        blueSeries->append(color.first, color.second.blue());
        greenSeries->append(color.first, color.second.green());
        redSeries->append(color.first, color.second.red());
    }
    chart->addSeries(blueSeries);
    chart->addSeries(greenSeries);
    chart->addSeries(redSeries);
    m_ui->chartView->repaint();
    QWidget::show();
}

