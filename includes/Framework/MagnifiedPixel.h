#pragma once

#include <string>
#include <qgraphicsitem.h>
#include <qcolor.h>

class MagnifiedPixel : public QGraphicsItem
{
public:
    MagnifiedPixel(size_t x,size_t y,size_t w,const QColor& color,const std::string& value);
    ~MagnifiedPixel();

    virtual QPainterPath shape()const override;
    virtual void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget) override;

private:
    size_t m_x;
    size_t m_y;
    size_t m_width;
    QColor m_color;
    std::string m_value;
    
    // Inherited via QGraphicsItem
    virtual QRectF boundingRect() const override;

};