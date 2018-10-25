#include "AverageColors.h"
#include "ProcessedImageScene.h"
#include "AverageColorsViewer.h"

AverageColors::AverageColors(QObject* parent):
    QObject(parent)
{
    m_viewer = std::make_unique<AverageColorsViewer>(*this);
}

AverageColors::~AverageColors()
{}

double AverageColors::getMean() const
{
    return m_mean;
}

double AverageColors::getSquaredDeviation() const
{
    return m_squaredDeviation;
}

void AverageColors::processMouseMove(QGraphicsSceneMouseEvent * mouseEvent)
{}

void AverageColors::processMousePress(QGraphicsSceneMouseEvent * mouseEvent)
{
    ProcessedImageScene* imageScene = dynamic_cast<ProcessedImageScene*>(QObject::parent());
    QImage* image = imageScene->getImage();

    size_t sum=0;

    for (size_t i = 0; i < image->width(); i++) {
        for (size_t j = 0; j < image->height(); j++) {
            sum += qGray(image->pixel(i, j));
        }
    }
    size_t numOfPixels = image->width()*image->height();
    m_mean = static_cast<double>(sum) / numOfPixels;

    double deviation = 0.0;
    for (size_t i = 0; i < image->width(); i++) {
        for (size_t j = 0; j < image->height(); j++) {
            double pixel = qGray(image->pixel(i, j));

            deviation += pow(pixel - m_mean, 2);
        }
    }

    m_squaredDeviation = sqrt(deviation / numOfPixels);
    m_viewer->addValues(m_mean, m_squaredDeviation);
    m_viewer->show();
}

void AverageColors::processMouseRelease(QGraphicsSceneMouseEvent * mouseEvent)
{}
