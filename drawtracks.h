#ifndef DRAWTRACKS_H
#define DRAWTRACKS_H

#include "component_common.h"
#include "bakudataconfig.h"
#include "track.h"
#include "ui_mainwindow.h"
#include <QFrame>
#include <QPainter>

class DrawTracks
{
public:
    DrawTracks(QFrame *frame);
    void draw(QPainter *painter);
    void drawSignallingTracks();
    void clearTracks();

private:
    void calculateTrackRect (int *points, int number_points, QRect *rect);
    void offsetPoints(int *points, int number_points, QRect rect, int *offset_points);
    void drawLabel (BAKU_Track *track_data, int state);
    void calculateTextPosition(BAKU_Track *track_data, int text_width,
                    int text_height, QRect track_rect, QPoint &text_point);
    void calculateTrackWidth(BAKU_Track *track_data, QRect track_rect, int &track_width);
    void calculateRect (BAKU_Track *track_data, bool extend_boundary, QRect &rect);
    int countTokens (char *track_label);
    void splitLabel (QPoint label_point, BAKU_Track *track_data, QFontMetrics *metrics);
    int calculateMaxLabelWidth (BAKU_Track *track_data, QFontMetrics *metrics);
    QFrame *m_frame;
    QPainter *m_painter;
    QPen m_track_pen;
    QBrush m_track_brush;
};

#endif // DRAWTRACKS_H
