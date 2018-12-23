#include "Hough.h"
#include "Canny.h"
#include <qimage.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <iostream>

Hough::Hough(Display display):m_display(display)
{}

QImage * Hough::modify(QImage * image)
{
    
    Canny canny(false);

    QImage* thresholdImage = canny.modify(image);

    m_matrixWidth = sqrt(pow(image->width(), 2) + pow(image->height(), 2));
    m_matrixHeight = 270;

    m_matrix.resize(m_matrixWidth * m_matrixHeight);


    QColor white(255, 255, 255);

    for (int x = 0; x < image->width(); x++) {
        for (int y = 0; y < image->height(); y++) {

            if (thresholdImage->pixelColor(x,y) == white) {              
                for (int theta = m_matrixHeight - 1; theta >= 0; theta--) {
                    double thetaRadians = theta * M_PI / m_matrixHeight;
                    double r = x*cos(thetaRadians) + y*sin(thetaRadians);
                    
                    int rScaled = (int)(r * m_matrixWidth/2 / m_matrixWidth) + m_matrixWidth/2;

                    m_matrix[rScaled*m_matrixHeight + theta]++;                   
                }
            }
        }
    }

    QImage* resultImage= new QImage(m_matrixWidth, m_matrixHeight, QImage::Format_RGB32);

    int maxValue =*std::max_element(m_matrix.begin(), m_matrix.end());
    
    for (int x = 0; x < resultImage->width(); x++) {
        for (int y = 0; y < resultImage->height(); y++) {
            int n = std::min( m_matrix[x*resultImage->height()+y]* 255.0 / maxValue, 255.0);
            resultImage->setPixelColor(x, y, QColor(n, n, n));
        }
    }


    double maxR = 0;
    double maxTheta = 0;
    double maxVal = 0;
    for (int x = 0; x < resultImage->width(); x++) {
        for (int y = 0; y < resultImage->height(); y++) {
            if (m_matrix[x*resultImage->height() + y] > maxVal) {
                maxVal = m_matrix[x*resultImage->height() + y];
                maxR = x;
                maxTheta = y;
            }
        }
    }

    auto d = [this](auto x,auto maxR,auto maxTheta) {
        double thetaRadians = maxTheta * M_PI / m_matrixHeight;
        double scalledR = (maxR - m_matrixWidth / 2) / (m_matrixWidth / 2)*m_matrixWidth;
        return (scalledR - x*cos(thetaRadians))/sin(thetaRadians);
    };
    auto peaks=findPeaks(m_matrix);

    for (const auto& peak : peaks) {       
        for (double x = 0; x < 1000; x++) {
            double y = d(x,peak.m_r,peak.m_theta);
            if (y >= 0 && y < image->height() && x>=0 && x<image->width()) {
            image->setPixelColor(x, y, QColor(255, 0, 0));
            }
        }
    }
    return resultImage;
}

std::vector<Peak> Hough::findPeaks(const std::vector<int>& amp)
{
    const int NOISE = 200;              
    int wideStart = -1;                 
    int grad = -1;                     
                                                                      
    std::vector<Peak>peaks;

    for (int x = 0; x < m_matrixWidth - 1; x++) {
        for (int y = 0; y < m_matrixHeight - 1; y++) {

            double currentValue = m_matrix[x*m_matrixHeight + y];
            double nextValue = m_matrix[x*m_matrixHeight + y +1];

            if (nextValue < currentValue)         // Only possibility of a peak
            {
                if (grad == 1 && currentValue > NOISE) {

                    Peak peak(x,y,currentValue);
                    peaks.push_back(peak);

                    std::cout << "Sharp peak of " << currentValue << " at i = "<< x*m_matrixHeight + y << '\n';
                } else if (grad == 0 && currentValue > NOISE) {
                   // std::cout << "Wide peak of " << currentValue << " from i = " << wideStart << " to "  << '\n';
                }
                grad = -1;
            } else if (nextValue == currentValue)   // Check for start of a wide peak
            {
                if (grad == 1) {
                    wideStart = x*m_matrixHeight + y;
                    grad = 0;
                }
            } else {
                grad = 1;
            }
        }
    }
    return peaks;
}

Peak::Peak(double r, double theta, double val):m_r(r),m_theta(theta),m_val(val)
{}
