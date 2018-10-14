#include "HistogramEqualizer.h"
#include <qimage.h>


HistogramEqualizer::HistogramEqualizer()
{

}

HistogramEqualizer::~HistogramEqualizer()
{

}

QImage * HistogramEqualizer::modify(QImage * image)
{
    QImage* modifiedImage = nullptr;
    if (image != nullptr) {
        for (size_t i = 0; i < image->width(); i++) {
            for (size_t j = 0; j < image->height(); j++) {
                QColor color = image->pixelColor(i, j);
                m_valueCount[color.value()]++;
            }
        }
    }

    std::map<size_t, double> prob;
    size_t numOfPixels = image->width()*image->height();

    double probability = static_cast<double>(m_valueCount[0]) / numOfPixels;
    prob[0] = probability;
    double cumulativeProb=0.0;

    for (size_t i = 1; i < m_valueCount.size();i++) {
        probability = static_cast<double>(m_valueCount[i]) / numOfPixels;

        cumulativeProb = prob[i - 1] + probability;
        prob[i] = cumulativeProb;
    }

    std::map<size_t, size_t> valueTable;

    for (size_t i = 0; i < 256; i++) {
        valueTable[i] = (prob[i] - prob[0]) / (1 - prob[0]) * 255;
    }

    modifiedImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);

    for (size_t i = 0; i < image->width(); i++) {
        for (size_t j = 0; j < image->height(); j++) {
            QColor hsvColor = image->pixelColor(i, j);

            hsvColor.setHsv(hsvColor.hsvHue(), hsvColor.hsvSaturation(), valueTable[hsvColor.value()]);

            modifiedImage->setPixelColor(i, j, hsvColor);
        }
    }

    return modifiedImage;
}
