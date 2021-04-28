#ifndef DRAWPLATFORMS_H
#define DRAWPLATFORMS_H

#include "qpainter.h"
#include "platform.h"
#include <QFrame>

class DrawPlatforms
{
public:
    DrawPlatforms(QFrame *frame);
    void addPlatforms();
    void clearCurrentPlatforms();

private:
    QFrame *m_frame;

};

#endif // DRAWPLATFORMS_H
