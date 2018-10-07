#pragma once

#include <qgraphicsscene.h>
#include <memory>

class QImage;
class QGraphicsSceneMouseEvent;

class ProcessedImageScene :public QGraphicsScene
{
    Q_OBJECT

public:
    ProcessedImageScene();
    ~ProcessedImageScene();

    void addImage(QImage* image,bool grey=false);
    QImage* getImage()const;

    void toggleSelection();

signals: 
    void selectedImage(QImage* image);

public slots:
    void getSelectedImage(QImage* image);

protected:
    void mouseMoveEvent(QGraphicsSceneMouseEvent* mouseEvent)override;
    void mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* mouseEvent)override;


private:
    bool m_selectionEnabled=false;

    QRect m_selection;
    QImage* m_image;

};