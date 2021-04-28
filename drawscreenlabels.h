#ifndef DRAWSCREENLABELS_H
#define DRAWSCREENLABELS_H

#include "qpainter.h"
#include <QFrame>

class DrawScreenLabels
{
public:
    DrawScreenLabels(QFrame *frame);
    void draw(QPainter *painter);

private:
    QFrame *m_frame;
    QPen m_pen;
    QBrush m_brush;
    QPainter *m_painter;
};

#endif // DRAWSCREENLABELS_H
