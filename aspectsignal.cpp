#include "aspectsignal.h"
#include <QPainter>

AspectSignal::AspectSignal(QWidget *parent) : SignalIndicator(parent)
{
    m_type = ASPECT_SIGNAL;
    m_radius = ASPECT_SIG_DEFAULT_RADIUS;
}

//!
//! \brief Sets the Indicator Radius
//!
//! \param radius IN The Indicator Radius
//!
//! \return None
//!
void AspectSignal::setRadius (int radius)
{
    if (radius > 0)
    {
        m_radius = radius;
    }
}

//!
//! \brief Gets the Indicator Radius
//!
//! \param None
//!
//! \return The Indicator Radius
//!
int AspectSignal::getRadius ()
{
    return m_radius;
}

//!
//! \brief Draws the Aspect Signal
//!
//! \param Invalid IN The Area in which to draw the Platform
//!
//! \return None
//!
void AspectSignal::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);
    QBrush signal_brush;
    QPen signal_pen;
    int center_x = rect().center().x();
    int center_y = rect().center().y();

    signal_pen.setColor(Qt::black);
    signal_pen.setStyle(Qt::SolidLine);

    //Set Fill Colour
    signal_brush.setStyle(Qt::SolidPattern);

    //Determine the signal type
    if (m_type == FIXED_RED_SIGNAL)
    {
        signal_brush.setColor(Qt::darkRed);
    }
    else
    {
        if(m_state == OFF)
        {
            signal_brush.setColor(Qt::darkRed);
        }
        else if(m_state == ON)
        {
            signal_brush.setColor(Qt::green);
        }
        else if (m_state == ASPECT_YELLOW_STATE)
        {
            signal_brush.setColor(Qt::yellow);
        }
        else
        {
            signal_brush.setColor(Qt::lightGray);
        }
    }

    //Draw Signal
   painter.setRenderHints(QPainter::Antialiasing, true);
   painter.setBrush(signal_brush);
   painter.setPen(signal_pen);
   painter.drawEllipse(QPoint(center_x,center_y), m_radius, m_radius);
}

void AspectSignal:: hideEvent(QHideEvent * /* unused */)
{
    update();
}
