#include "Hough.h"
#include "Canny.h"
#include <qimage.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <qpixmap.h>
#include <qpainter.h>
#include <iostream>
#include "ValueInputDialog.h"

#define DEG2RAD 0.017453293f

Hough::Hough(Display display):m_display(display)
{}

QImage * Hough::modify(QImage * image)
{
   // ValueInputDialog dialog(1);

  //  auto thresholds = dialog.show();
   // m_threshold = thresholds[0];

    m_threshold = 200;
    Canny canny(false);

    QImage* thresholdImage = canny.modify(image);

    m_imgHeight = thresholdImage->height();
    m_imgWidth = thresholdImage->width();


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

    auto d = [this](auto x,auto maxR,auto maxTheta) {
        double thetaRadians = maxTheta * M_PI / m_matrixHeight;
        double scalledR = (maxR - m_matrixWidth / 2) / (m_matrixWidth / 2)*m_matrixWidth;
        return (scalledR - x*cos(thetaRadians))/sin(thetaRadians);
    };

    auto peaks=findPeaks2(m_matrix);

    for (const auto& peak : peaks) {       
        for (double x = 0; x < 1000; x+=0.01) {
            double y = d(x,peak.m_r,peak.m_theta);
            if (y >= 0 && y < image->height() && x>=0 && x<image->width()) {
            image->setPixelColor(x, y, QColor(255, 0, 0));
            }
        }
    }
    return resultImage;
}

std::vector<Peak> Hough::findPeaks2(const std::vector<int>& values)
{
    std::vector<Peak> peaks;

   for (int r = 0; r < m_matrixWidth; r++) {
      for (int t = 0; t < m_matrixHeight; t++) {
            if (m_matrix[r*m_matrixHeight + t] > m_threshold) {
                int max = m_matrix[r*m_matrixHeight + t];

                for (int ly = -4; ly <= 4; ly++) {
                    for (int lx = -4; lx <= 4; lx++) {
                        if ((ly + r >= 0 && ly + r < m_matrixWidth) && (lx + t >= 0 && lx + t < m_matrixHeight)) {
                            if (m_matrix[(ly + r) *m_matrixHeight + (lx + t)] > max) {
                                max = m_matrix[(ly + r)*m_matrixHeight + (lx + t)];
                                ly = 5;
                                lx = 5;
                            }
                        }
                    }
                }

                if (max >(int)m_matrix[r*m_matrixHeight + t]) {
                    continue;
                }

                Peak peak(r,t, max);
                peaks.push_back(peak);
            }
        }
    }
    return peaks;
}

Peak::Peak(double r, double theta, double val):m_r(r),m_theta(theta),m_val(val)
{}

bool Peak::operator>(const Peak & peak)
{
    return this->m_val > peak.m_val;
}

bool Peak::operator>(double values)
{
    return this->m_val > values;
}
