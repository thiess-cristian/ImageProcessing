#include "MagnifiedPixel.h"
#include <qpainter.h>
#include <qpainterpath.h>

MagnifiedPixel::MagnifiedPixel(size_t x, size_t y, size_t w, const QColor& color, const std::string& value):
    m_width(w),
    m_color(color),
    m_value(value)
{
    m_x = x;
    m_y = y;
}

MagnifiedPixel::~MagnifiedPixel()
{}

QPainterPath MagnifiedPixel::shape() const
{
    QPainterPath path;
    path.addRect(m_x, m_y, m_width, m_width);
    return path;
}

void MagnifiedPixel::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
    painter->setBrush(m_color);
    //painter->setPen(Qt::NoPen);
    painter->drawRect(m_x, m_y, m_width, m_width);

    QPainterPath path;
    path.addText(m_x, m_y + m_width, QFont("Arial", 15), m_value.c_str());
       
    painter->fillPath(path,QBrush(QColor(255,255,255)));
    painter->strokePath(path, QPen(Qt::black));
}

QRectF MagnifiedPixel::boundingRect() const
{
    return QRectF(m_x, m_y, m_width, m_width);
}
