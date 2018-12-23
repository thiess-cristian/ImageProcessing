#include "Hough.h"
#include "Canny.h"
#include <qimage.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <qpixmap.h>
#include <qpainter.h>

Hough::Hough(Display display):m_display(display)
{}

QImage * Hough::modify(QImage * image)
{
    
    Canny canny(false);

    QImage* thresholdImage = canny.modify(image);

    m_matrixWidth = sqrt(pow(image->width(), 2) + pow(image->height(), 2));
    m_matrixHeight = 270;

    m_matrix.resize(m_matrixWidth * m_matrixHeight);

    std::vector<double> edgeDir = canny.getEdgeDir();
    std::vector<double> angles = canny.getAngles();
    
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

    auto d = [maxR,maxTheta,this](auto x) {
        double thetaRadians = maxTheta * M_PI / m_matrixHeight;
        double scalledR = (maxR - m_matrixWidth / 2) / (m_matrixWidth / 2)*m_matrixWidth;
        return (scalledR - x*cos(thetaRadians))*sin(thetaRadians);
    };

    for (int x = 0; x < 1000; x++) {
        int y = d(x);
        image->setPixelColor(x, y, QColor(255, 0, 0));
    }


    return resultImage;
}

QImage * Hough::displayEdges(QImage * image)
{
    return nullptr;
}

QImage * Hough::displayMatrix(QImage * image)
{
    return nullptr;
}
