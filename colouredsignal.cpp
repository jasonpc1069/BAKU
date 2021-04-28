#include "colouredsignal.h"
#include <QPainter>

ColouredSignal::ColouredSignal(QWidget *parent): SignalIndicator(parent)
{
    m_red_state = INITIAL_STATE;
    m_green_state = INITIAL_STATE;

    m_direction = RIGHT;
}

//!
//! \brief Set the state of the Signal
//!
//! \param state IN The signalling state of the component [ON/OFF/UNKNOWN]
//!	\param type IN RGKE or DGKE (Red, Green)
//!
//! \return None
//!
void ColouredSignal::setSignalState(int state, int type)
{
    if (state > 0 && state <= INVALID_COMPONENT_STATE)
    {
        if (type == IO_TYPE_RGKE)
        {
            m_red_state = state;
        }
        else if (type == IO_TYPE_DGKE)
        {
            m_green_state = state;
        }
        update();
    }
}

//!
//! \brief Set the signal direction
//!
//! \param direction IN The signal direction
//!
//! \return None
//!
void ColouredSignal::setDirection(int direction)
{
    if (direction == LEFT || direction == RIGHT)
    {
        m_direction = direction;
    }
}

//!
//! \brief Get the signal direction
//!
//! \param None
//!
//! \return The signal direction
//!
int ColouredSignal::getDirection()
{
    return m_direction;
}

//!
//! \brief Draws the Aspect Signal
//!
//! \param Invalid IN The Area in which to draw the Platform
//!
//! \return None
//!
void ColouredSignal::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);
    QBrush rgke_signal_brush;
    QBrush dgke_signal_brush;
    QPen signal_pen;
    QPoint rgke_indicator_point;
    QPoint dgke_indicator_point;
    QPointF light_point;
    int radius = (COLOURED_SIG_HEIGHT / 2);
    QColor off_colour = Qt::black;

    painter.setRenderHints(QPainter::Antialiasing, true);

    drawBody(&painter);

    painter.setPen(Qt::NoPen);

    //Initialise Brush Styles
    rgke_signal_brush.setStyle(Qt::SolidPattern);
    dgke_signal_brush.setStyle(Qt::SolidPattern);

    // Code to set Red and Green States
    if (m_state == ON)
    {
        m_green_state = ON;
        m_red_state = OFF;
    }
    else if (m_state == OFF)
    {
        m_green_state = OFF;
        m_red_state = ON;
    }
    else
    {
        m_green_state = INITIAL_STATE;
        m_red_state = INITIAL_STATE;
    }

    //Set 'DGKE' Fill Colour
    if (m_green_state == ON)
    {
        // DGKE ON
        if (m_type == YELLOW_COLOURED_SIGNAL)
        {
            dgke_signal_brush.setColor(Qt::yellow);
        }
        else
        {
            dgke_signal_brush.setColor(Qt::green);
        }
    }
    else if (m_green_state == OFF)
    {
        // DGKE OFF
        dgke_signal_brush.setColor(off_colour);
    }
    else
    {
        // DGKE Unknown
        dgke_signal_brush.setColor(Qt::darkGray);
    }

    //Set 'RGKE' Fill Colour
    if (m_red_state == ON)
    {
        // RGKE ON
        rgke_signal_brush.setColor(Qt::red);
    }
    else if (m_red_state == OFF)
    {
        // RGKE OFF
        rgke_signal_brush.setColor(off_colour);
    }
    else
    {
        // RGKE Unknown
        rgke_signal_brush.setColor(Qt::darkGray);
    }

    // Calculate Bulb Positions
    if (m_post_position == ABOVE || m_post_position == BELOW)
    {
        if (m_direction == LEFT)
        {
            dgke_indicator_point.setX(rect().left() + radius + CLRD_BULB_IDNT);
            dgke_indicator_point.setY(rect().center().y());


            rgke_indicator_point.setX(rect().right() - radius - CLRD_BULB_IDNT);
            rgke_indicator_point.setY(rect().center().y());
        }
        else if (m_direction == RIGHT)
        {
            rgke_indicator_point.setX(rect().left() + radius + CLRD_BULB_IDNT);
            rgke_indicator_point.setY(rect().center().y());


            dgke_indicator_point.setX(rect().right() - radius - CLRD_BULB_IDNT);
            dgke_indicator_point.setY(rect().center().y());
        }
    }
    else
    {
        if (m_direction == RIGHT)
        {
            dgke_indicator_point.setY(rect().bottom()  - radius - CLRD_BULB_IDNT) ;
            dgke_indicator_point.setX(rect().center().x());


            rgke_indicator_point.setY(rect().top()  + radius + CLRD_BULB_IDNT) ;
            rgke_indicator_point.setX(rect().center().x());
        }
        else if (m_direction == LEFT)
        {
            rgke_indicator_point.setY(rect().bottom()  - radius - CLRD_BULB_IDNT) ;
            rgke_indicator_point.setX(rect().center().x());


            dgke_indicator_point.setY(rect().top()  + radius + CLRD_BULB_IDNT) ;
            dgke_indicator_point.setX(rect().center().x());
        }
    }

    painter.setBrush(dgke_signal_brush);

    //DGKE Signal
    painter.drawEllipse(dgke_indicator_point, CLRD_BULB_RADIUS, CLRD_BULB_RADIUS);

    painter.setBrush(rgke_signal_brush);

    //RGKE Signal
    painter.drawEllipse(rgke_indicator_point, CLRD_BULB_RADIUS, CLRD_BULB_RADIUS);

    signal_pen.setColor(Qt::white);
    painter.setPen(signal_pen);

    //Add RGKE 3D effect
    if (m_red_state == ON)
    {
        rgke_signal_brush.setColor(Qt::white);
        painter.setBrush(rgke_signal_brush);

        light_point.setX(rgke_indicator_point.x() - (CLRD_BULB_RADIUS / 4));
        light_point.setY(rgke_indicator_point.y() - (CLRD_BULB_RADIUS / 4));

        painter.drawEllipse(light_point, 1,1);

//        rgke_signal_brush.Style = PBS_SIMPLE_ALIAS;
//        rgke_signal_brush.Width = 1;

//        Screen()->Arc (rgke_indicator_point.x, rgke_indicator_point.y, CLRD_BULB_RADIUS + 1, CLRD_BULB_RADIUS + 1, -90, -180,
//                       rgke_signal_brush, 0);
    }

    //Add DGKE 3D effect
    if (m_green_state == ON)
    {
        dgke_signal_brush.setColor(Qt::white);
        painter.setBrush(dgke_signal_brush);

        light_point.setX(dgke_indicator_point.x() - (CLRD_BULB_RADIUS / 4));
        light_point.setY(dgke_indicator_point.y() - (CLRD_BULB_RADIUS / 4));

        painter.drawEllipse(light_point, 1,1);

//        //rgke_signal_brush.LineColor = GC (CID_BULB_SHADOW);
//        dgke_signal_brush.Style = PBS_SIMPLE_ALIAS;
//        dgke_signal_brush.Width = 1;

//        Screen()->Arc (dgke_indicator_point.x, dgke_indicator_point.y, CLRD_BULB_RADIUS + 1, CLRD_BULB_RADIUS + 1, -90, -180,
//                       dgke_signal_brush, 0);
    }
}

//!
//! \brief Draws the Signal Body
//!
//! \param None
//!
//! \return None
//!
void ColouredSignal::drawBody (QPainter *painter)
{
    QBrush signal_brush;
    QPen signal_pen;
    QRect signal_rect;
    int radius = (COLOURED_SIG_HEIGHT / 2);
    int l_arc_start = 0;
    int r_arc_start = 0;
    QRect l_rect;
    QRect r_rect;

    signal_pen.setWidth(1);
    signal_brush.setStyle(Qt::SolidPattern);

    if (m_state != ON && m_state != OFF)
    {
        signal_pen.setColor(Qt::darkGray);
        signal_brush.setColor(Qt::darkGray);
    }
    else
    {
        signal_pen.setColor(Qt::black);
        signal_brush.setColor(Qt::black);
    }

    //Calculate signal coordinates
    signal_rect = rect();
    l_rect = rect();
    r_rect = rect();

    if (m_post_position == ABOVE || m_post_position == BELOW)
    {
        // Above or Below
        signal_rect.setLeft(signal_rect.left() + radius);
        signal_rect.setRight(signal_rect.right() - radius);
        l_rect.setRight(l_rect.left() + (radius*2));
        r_rect.setLeft(r_rect.right() - (radius*2));
        l_arc_start = 90;
        r_arc_start = -90;
    }
    else
    {
        // Left or Right
        signal_rect.setTop(signal_rect.top() + radius);
        signal_rect.setBottom(signal_rect.bottom() - radius);
        l_rect.setTop(l_rect.bottom() - (radius*2));
        r_rect.setBottom(r_rect.top() + (radius*2));

        l_arc_start = 180;
        r_arc_start = 0;
    }

    painter->setBrush(signal_brush);
    painter->setPen(signal_pen);

    painter->drawRect (signal_rect);

    //Left End
    painter->drawChord(l_rect, (l_arc_start * 16), (180 * 16));

    //Right End
    painter->drawChord(r_rect, (r_arc_start * 16), (180* 16));
}

void ColouredSignal:: hideEvent(QHideEvent * /* unused */)
{
    update();
}
