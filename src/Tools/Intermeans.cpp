#include "Intermeans.h"
#include "BinaryImage.h"
#include <qimage.h>
#include <vector>
#include <iostream>

Intermeans::Intermeans()
{}

QImage * Intermeans::modify(QImage * image)
{
    QImage* resultImage = new QImage(image->width(), image->height(), QImage::Format_RGB32);


    int maxValue = 0;
    int minValue = 255;
    for (int x = 0; x < image->width(); x++) {
        for (int y = 0; y < image->height(); y++) {
            int col = qGray(image->pixel(x, y));

            if (col > maxValue) {
                maxValue = col;
            }
            if (col < minValue) {
                minValue = col;
            }
        }
    }

    double t = (maxValue + minValue) / 2.0;
    double error=0;

    std::vector<int> firstGroup;
    std::vector<int> secondGroup;

    do {
        firstGroup.clear();
        secondGroup.clear();
        for (int x = 0; x < image->width(); x++) {
            for (int y = 0; y < image->height(); y++) {
                int pixelValue = qGray(image->pixel(x, y));

                if (pixelValue < t) {
                    firstGroup.push_back(pixelValue);
                } else {
                    secondGroup.push_back(pixelValue);
                }
            }
        }

        double firstMean = meanValue(firstGroup);
        double secondMean = meanValue(secondGroup);

        double ti = (firstMean + secondMean) / 2;

        error = abs(t - ti);
        t = ti;

        std::cout << error <<std::endl;

    } while (error>m_epsilon);

    BinaryImage mod;

    mod.computeBinarization(image, resultImage, t);

    return resultImage;
}

double Intermeans::meanValue(std::vector<int> values) const
{
    double sum = 0;

    for (const auto& value : values) {
        sum += value;
    }

    return sum / (double)values.size();
}
