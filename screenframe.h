#ifndef SCREENFRAME_H
#define SCREENFRAME_H

#include <QWidget>
#include <QFrame>
#include "qpainter.h"
#include "drawsignals.h"
#include "drawtracks.h"
#include "drawscreenlabels.h"


class ScreenFrame : public QFrame
{
    Q_OBJECT
public:
    explicit ScreenFrame(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *e) override;

private:
    DrawSignals *m_draw_signals = nullptr;
    DrawTracks *m_draw_tracks = nullptr;
    DrawScreenLabels *m_draw_labels = nullptr;

signals:

};

#endif // SCREENFRAME_H
