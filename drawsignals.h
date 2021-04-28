#ifndef DRAWSIGNALS_H
#define DRAWSIGNALS_H

#include "component_common.h"
#include "aspectsignal.h"
#include "colouredsignal.h"
#include "SignalIndicator.h"
#include "ui_mainwindow.h"
#include "bakudataconfig.h"
#include "dynamicdataconfig.h"
#include "qpainter.h"
#include <QFrame>

class DrawSignals
{
public:
    DrawSignals(QFrame *frame);
    void draw(QPainter *painter);
    void drawIndicators();
    void clearCurrentIndicators();

private:
    void drawPost (BAKU_Signal *signal_data, QPoint signal_position);
    void calculateSignalPosition (BAKU_Signal *signal_data, QPoint &signal_position);
    void calculateIndicatorCentrePoint (BAKU_Signal*signal_data, QPoint signal_position, QPoint &indicator_point);
    void drawSignalLabel (BAKU_Signal *signal_data, QPoint indicator_point);
    void calculateSignalRectangles (BAKU_Signal *signal_data, QPoint signal_position,
                                        QRect &sig_lg_spcr_rect, QRect &sig_sm_spcr_rect);
    void calculateSignalSpacerEndPoint (BAKU_Signal *signal_data, QPoint signal_position,
                                        QPoint &end);
    void drawIndicator(BAKU_Dynamic_Signal *signal_data);
    void calculateColouredSignalRect(BAKU_Signal *signal_data, QPoint signal_position, QRect &signal_rect);
    void drawColouredSignalLabel (BAKU_Signal *signal_data, QRect signal_rect);
    QFrame *m_frame;
    QPen m_signal_pen;
    QBrush m_signal_brush;
    QPainter *m_painter;

};

#endif // DRAWSIGNALS_H
