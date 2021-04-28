#include "screenframe.h"



ScreenFrame::ScreenFrame(QWidget *parent) : QFrame(parent)
{
    m_draw_signals = new DrawSignals(this);
    m_draw_tracks = new DrawTracks(this);
    m_draw_labels = new DrawScreenLabels(this);
}

void ScreenFrame::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);

    if (m_draw_signals)
    {
        m_draw_signals->draw(&painter);
    }

    if (m_draw_tracks)
    {
        m_draw_tracks->draw(&painter);
    }

    if (m_draw_labels)
    {
        m_draw_labels->draw(&painter);
    }
}
