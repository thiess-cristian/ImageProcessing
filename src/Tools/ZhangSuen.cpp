#include "ZhangSuen.h"
#include <qimage.h>
#include <qcolor.h>
#include <iostream>
#include <memory>

ZhangSuen::ZhangSuen():m_neighbors(std::vector<QColor>(8))
{
    
}

QImage * ZhangSuen::modify(QImage * image)
{
    if (image == nullptr) {
        return nullptr;
    }

    std::unique_ptr<QImage> tempImage1;
    std::unique_ptr<QImage> tempImage2;
    m_endImage= new QImage(image->copy(QRect(0, 0, image->width(), image->height())));

    auto step1Check = [this]() {
        QColor p2 = m_neighbors[0];
        QColor p4 = m_neighbors[2];
        QColor p6 = m_neighbors[4];
        QColor p8 = m_neighbors[6];

        QColor black(0, 0, 0);

        bool ok1 = p2 == black || p4 == black || p6 == black;
        bool ok2 = p4 == black || p6 == black || p8 == black;

        return ok1 &&ok2;
    };

    auto step2Check = [this]() {
        QColor p2 = m_neighbors[0];
        QColor p4 = m_neighbors[2];
        QColor p6 = m_neighbors[4];
        QColor p8 = m_neighbors[6];

        QColor black(0, 0, 0);

        bool ok1 = p2 == black && p4 == black && p8 == black;
        bool ok2 = p2 == black && p6 == black && p8 == black;

        return ok1 && ok2;
    };
    int x = 0;
    bool imageWasModified;
    do {
        imageWasModified = false;

        tempImage1.reset(new QImage(m_endImage->copy(QRect(0, 0, m_endImage->width(), m_endImage->height()))));
        bool step1Result = changeImage(tempImage1.get(), step1Check);

        tempImage2.reset(new QImage(m_endImage->copy(QRect(0, 0, m_endImage->width(), m_endImage->height()))));
        bool step2Result = changeImage(tempImage2.get(), step2Check);

        if (step1Result || step2Result) {
            imageWasModified = true;
        }

        std::cout << x++ << std::endl;
   
   } while (imageWasModified);

    return m_endImage;
}

bool ZhangSuen::changeImage(QImage * modifiedImage, std::function< bool()> neighborCheck)
{
   
    size_t border = 1;

    for (size_t i = border; i < modifiedImage->width() - border; i++) {
        for (size_t j = border; j < modifiedImage->height() - border; j++) {
            if (modifiedImage->pixelColor(i, j) == QColor(0,0,0)) {
                continue;
            }

            setNeighbors(modifiedImage, i, j);

            if (checkPixel(neighborCheck)) {
                m_markedPixels.push_back(QPoint(i, j));
            }
        }
    }

    if (m_markedPixels.empty()) {
        return false;
    }

    for (const auto& markedPixel : m_markedPixels) {
        m_endImage->setPixelColor(markedPixel.x(), markedPixel.y(),QColor(0,0,0));
    }

    m_markedPixels.clear();
    return true;
}

void ZhangSuen::setNeighbors(QImage * image, size_t x, size_t y)
{
    m_neighbors[0] = image->pixelColor(x, y - 1);
    m_neighbors[1] = image->pixelColor(x + 1, y - 1);
    m_neighbors[2] = image->pixelColor(x + 1, y);
    m_neighbors[3] = image->pixelColor(x + 1, y + 1);
    m_neighbors[4] = image->pixelColor(x, y + 1);
    m_neighbors[5] = image->pixelColor(x - 1, y + 1);
    m_neighbors[6] = image->pixelColor(x - 1, y);
    m_neighbors[7] = image->pixelColor(x - 1, y - 1);
}

size_t ZhangSuen::nrOfTransitions()
{
    size_t transitions = 0;
    QColor white(255, 255, 255);
    QColor black(0, 0, 0);
    for (size_t i = 0; i < m_neighbors.size()-1; i++) {
        if (m_neighbors[i] == black && m_neighbors[i + 1] == white) {
            transitions++;
        }
    }

    if (m_neighbors[m_neighbors.size() - 1] == black && m_neighbors[0] == white) {
        transitions++;
    }
    return transitions;
}

size_t ZhangSuen::nrOfWhiteNeighbors()
{
    size_t nr = 0;
    QColor white(255, 255, 255);

    for (const auto& neighbor : m_neighbors) {
        if (neighbor == white) {
            nr++;
        }
    }
    return nr;
}

bool ZhangSuen::checkPixel(std::function< bool()> neighborCheck)
{
    bool transitions = nrOfTransitions() == 1;

    size_t nrOfNeighbors = nrOfWhiteNeighbors();
    bool neighbors = 2 <= nrOfNeighbors && nrOfNeighbors <= 6;

    bool check = neighborCheck();

    return transitions && neighbors && check;
}
