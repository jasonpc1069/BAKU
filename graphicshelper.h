#ifndef GRAPHICSHELPER_H
#define GRAPHICSHELPER_H

#include "qpoint.h"

class GraphicsHelper
{
public:
    GraphicsHelper();
    ~GraphicsHelper();
    void calculateCirclePoint(QPoint centre_point, unsigned short radius,
            short angle, bool inverse_vertical, QPoint &circle_point);
    void calculatePoint (int start_x, int start_y,
            int  comp_x, int  comp_y, QPoint &point);
};

#endif // GRAPHICSHELPER_H
