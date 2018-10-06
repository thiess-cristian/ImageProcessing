#pragma once

#include <qgraphicsscene.h>
#include <memory>

class QImage;

class ProcessedImageScene :public QGraphicsScene
{
public:
    ProcessedImageScene();
    ~ProcessedImageScene();

    void addImage(QImage* image,bool grey=false);

private:

    QImage* m_image;

};