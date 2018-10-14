#pragma once

#include <qgraphicsscene.h>
#include <memory>

class QImage;
class QGraphicsSceneMouseEvent;
class IMouseTool;

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
    QImage* m_image;

    bool m_mouseToolEnabled=false;
    std::unique_ptr<IMouseTool> m_mouseTool;

};