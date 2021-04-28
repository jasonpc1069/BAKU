#include "drawsignals.h"
#include "graphicshelper.h"
#include "qfontdatabase.h"
#include "qstringlist.h"

DrawSignals::DrawSignals(QFrame *frame)
{
    m_frame = frame;
}

//!
//! \brief Draws the Signalling Signals
//!
//! Draws all of the relevant Signals that are controlled by state
//!
//!
//! \return None
//!
void DrawSignals::drawIndicators ()
{
    int s;

    //Determine whether track should be drawn, and relates to the selected m_screen
    for (s = 0; ( (s < MAX_SCREEN_SIGNALS) && (s < g_baku_dynamic_data.num_signals)); s++)
    {
        drawIndicator (&g_baku_dynamic_data.signal[s]);
    }
}

//!
//! \brief Draws an individual Signalling Signal
//!
//! Draws the relevant Signal that is controlled by state
//!
//! \param signal_data IN Details of the screen Signals
//!
//! \return None
//!
void DrawSignals::drawIndicator (BAKU_Dynamic_Signal *signal_data)
{
    QRect signal_rect;
    QPoint indicator_point;
    QPoint signal_position;
    unsigned short radius = 0;

    // Determine Radius
    switch (signal_data->data.signal_type)
    {
        case ASPECT_SIGNAL:
        case FIXED_RED_SIGNAL:
            radius = ASPECT_SIG_DEFAULT_RADIUS;
            break;
        case SHUNT_SIGNAL:
            radius = SHUNT_SIG_DEFAULT_RADIUS;
            break;
        default:
            radius = DEFAULT_SIG_RADIUS;
            break;
    }


    // Determine whether the signal is a valid type
    if ((signal_data->signal == nullptr) &&
        ((signal_data->data.signal_type == COLOURED_SIGNAL) ||
         (signal_data->data.signal_type == SMALL_COLOURED_SIGNAL) ||
         (signal_data->data.signal_type == YELLOW_COLOURED_SIGNAL) ||
         (signal_data->data.signal_type == ASPECT_SIGNAL) ||
         (signal_data->data.signal_type == FIXED_RED_SIGNAL)))

    {
        // Calculate the Signal position
        calculateSignalPosition (&signal_data->data, signal_position);

        if (signal_data->data.signal_type == COLOURED_SIGNAL ||
            signal_data->data.signal_type == SMALL_COLOURED_SIGNAL ||
            signal_data->data.signal_type == YELLOW_COLOURED_SIGNAL)
        {
            calculateColouredSignalRect(&signal_data->data, signal_position, signal_rect);
            signal_data->signal = new ColouredSignal(m_frame);
            signal_data->signal->setGeometry(signal_rect);
            qobject_cast<ColouredSignal*>(signal_data->signal)->setPostPosition(signal_data->data.post_pos);
            qobject_cast<ColouredSignal*>(signal_data->signal)->setDirection(signal_data->data.signal_dir);
            signal_data->signal->setState(OFF);

        }
        else
        {
            // Calculate the Signal Centre Position
            calculateIndicatorCentrePoint (&signal_data->data, signal_position, indicator_point);

            signal_rect.setCoords ((indicator_point.x() - radius),
                                   (indicator_point.y() - radius),
                                   (indicator_point.x() + radius),
                                   (indicator_point.y() + radius));
        }

        //Create Signal Icon
        if (signal_data->data.signal_type == ASPECT_SIGNAL || signal_data->data.signal_type == FIXED_RED_SIGNAL)
        {
            signal_data->signal = new AspectSignal(m_frame);
            signal_data->signal->setGeometry(signal_rect);
            qobject_cast<AspectSignal*>(signal_data->signal)->setType(signal_data->data.signal_type);
            qobject_cast<AspectSignal*>(signal_data->signal)->setCentrePoint (indicator_point);
            qobject_cast<AspectSignal*>(signal_data->signal)->setRadius (radius);
            signal_data->signal->setState(INITIAL_STATE);
        }

        signal_data->signal->show();
    }
}

//!
//! \brief Clears the Current Signals
//!
//! Removes all of the relevant Signals from the Signalling Screen
//!
//!
//! \return None
//!
void DrawSignals::clearCurrentIndicators()
{
    int s;

    for (s = 0; ( (s < MAX_SCREEN_SIGNALS) && (s < g_baku_dynamic_data.num_signals)); s++)
    {
        if (g_baku_dynamic_data.signal[s].signal != nullptr)
        {
            g_baku_dynamic_data.signal[s].signal->hide();
            g_baku_dynamic_data.signal[s].signal = nullptr;
        }
    }
}

void DrawSignals::draw(QPainter* painter)
{
    int s;
    QPoint indicator_point;
    QPoint signal_position;
    QRect coloured_rect;

    m_painter = painter;

    m_signal_brush.setStyle(Qt::SolidPattern);
    m_signal_brush.setColor(Qt::black);
    m_signal_pen.setColor(Qt::black);
    m_signal_pen.setStyle(Qt::SolidLine);
    //m_signal_pen.setBrush(m_signal_brush);

    m_painter->setPen(m_signal_pen);
    m_painter->setBrush(m_signal_brush);

    //Determine whether track should be drawn, and relates to the selected screen
    for (s = 0; ( (s < MAX_SCREEN_SIGNALS) && (s < g_baku_data.num_signals)); s++)
    {
        // Determine whether the signal should be displayed
        if (g_baku_data.signal[s].post_x > 0 && g_baku_data.signal[s].post_y >0)
        {
            //Calculate the signal position
            calculateSignalPosition (&g_baku_data.signal[s], signal_position);

            // Draw the Post
            drawPost (&g_baku_data.signal[s], signal_position);

            // Calculate the centre point of the signal
            calculateIndicatorCentrePoint (&g_baku_data.signal[s], signal_position, indicator_point);

            // Draw the Signal Label
            if (g_baku_data.signal[s].signal_type == COLOURED_SIGNAL ||
                g_baku_data.signal[s].signal_type == YELLOW_COLOURED_SIGNAL ||
                g_baku_data.signal[s].signal_type == SMALL_COLOURED_SIGNAL)
            {
                calculateColouredSignalRect(&g_baku_data.signal[s], signal_position, coloured_rect);
                drawColouredSignalLabel(&g_baku_data.signal[s], coloured_rect);
            }
            else
            {
                drawSignalLabel(&g_baku_data.signal[s], indicator_point);
            }


        }
    }
}

//!
//! \brief Draws the post for the signal
//!
//! Draws the signal post onto the Signalling Screen
//!
//! \param signal_data IN Details of the screen Signals
//! \param signal_position IN The calculated signal position
//!
//! \return None
//!
void DrawSignals::drawPost (BAKU_Signal *signal_data,
                            QPoint signal_position)
{
    QPoint post_start;
    QRect sig_lg_spcr_rect;
    QRect sig_sm_spcr_rect;
    QPoint end;
    GraphicsHelper helper;

    // Calculate Post Start
    helper.calculatePoint(m_frame->rect().left(),
                          m_frame->rect().top(),
                          signal_data->post_x,signal_data->post_y, post_start);

    //Draw Post
    m_signal_pen.setWidth(POST_WIDTH);
    m_painter->setPen(m_signal_pen);

    if (signal_data->draw_post != false)
    {
        m_painter->drawLine(post_start.x(), post_start.y(), signal_position.x(), signal_position.y());
    }

    if (signal_data->signal_type == SHUNT_SIGNAL)
    {
        m_signal_pen.setWidth(SHUNT_POST_WIDTH);
        m_painter->setPen(m_signal_pen);

        if (signal_data->draw_post != false)
        {
            // Calculate Signal Spacer Rectangles
            calculateSignalRectangles (signal_data, signal_position, sig_lg_spcr_rect, sig_sm_spcr_rect);

            m_painter->drawRect(sig_lg_spcr_rect);
            m_painter->drawRect(sig_sm_spcr_rect);
        }
    }
    else
    {
        if (signal_data->draw_post == true || signal_data->signal_type != FIXED_RED_SIGNAL)
        {
            //Calculate Signal Spacer Points
            calculateSignalSpacerEndPoint (signal_data, signal_position, end);

            m_painter->drawLine(signal_position.x(), signal_position.y(), end.x(), end.y());
        }
    }
}

//!
//! \brief Calculates the signal position
//!
//! Calculates the position on the Signalling Screen where the signal should be drawn
//!
//! \param signal_data IN Details of the screen Signals
//! \param OUT signal_position The calculated position (X and Y)
//!
//! \return None
//!
void DrawSignals::calculateSignalPosition (BAKU_Signal *signal_data,
                                           QPoint &signal_position)
{
    //Calculate Signal Position
    if (signal_data->post_pos == BELOW)
    {
        // Post Position: Below
        signal_position.setX(m_frame->rect().left() + signal_data->post_x);
        signal_position.setY(m_frame->rect().top()  + (signal_data->post_y + POST_HEIGHT));
    }
    else if (signal_data->post_pos == ABOVE)
    {
        // Above
        signal_position.setX(m_frame->rect().left() + signal_data->post_x);
        signal_position.setY(m_frame->rect().top() + (signal_data->post_y - POST_HEIGHT));

    }
    else if (signal_data->post_pos == RIGHT)
    {
        // Post Position: Right
        signal_position.setX(m_frame->rect().left() + (signal_data->post_x + POST_HEIGHT));
        signal_position.setY(m_frame->rect().top() + signal_data->post_y);
    }
    else
    {
        // Post Position: Left  or Default
        signal_position.setX(m_frame->rect().left() + (signal_data->post_x - POST_HEIGHT));
        signal_position.setY(m_frame->rect().top()+ signal_data->post_y);
    }
}

//!
//! \brief Calculates the centre point for the signal indicator
//!
//! Calculates the point on the signalling screen where the centre of the indicator
//! should be drawn
//!
//! \param signal_data IN 		Details of the screen Signals
//! \param signal_position IN 	The calculated signal position
//! \param OUT indicator_point	The centre point of the signal (X and Y)
//!
//! \return None
//!
void DrawSignals::calculateIndicatorCentrePoint (BAKU_Signal*signal_data,
                                                 QPoint signal_position,
                                                 QPoint &indicator_point)
{
    short radius;
    int post_pos = LEFT;
    int signal_dir = RIGHT;
    short spcr = 0;

    if (signal_data->signal_type == SHUNT_SIGNAL)
    {
        if (signal_data->draw_post != 0)
        {
            spcr = SIG_LG_SPCR_W + SIG_SM_SPCR_W;
        }
    }
    else
    {
        spcr = SIGNAL_SPCR_LGTH;
    }

    // Set Post Position
    if (signal_data->post_pos >= ABOVE && signal_data->post_pos <= RIGHT)
    {
        post_pos = signal_data->post_pos;
    }

    // Set Signal Direction
    if (signal_data->signal_dir >= LEFT && signal_data->signal_dir <= RIGHT)
    {
        signal_dir = signal_data->signal_dir;
    }

    // Determine Radius
    switch (signal_data->signal_type)
    {
        case ASPECT_SIGNAL:
        case FIXED_RED_SIGNAL:
            radius = ASPECT_SIG_DEFAULT_RADIUS;
            break;
        case SHUNT_SIGNAL:
            radius = SHUNT_SIG_DEFAULT_RADIUS;
            break;
        default:
            radius = DEFAULT_SIG_RADIUS;
            break;
    }

    //Calculate Signal Positions
    if ((post_pos == ABOVE) || (post_pos == BELOW))
    {
        if (signal_dir == RIGHT)
        {
            indicator_point.setX(signal_position.x() + POST_WIDTH  +  spcr + radius);
            indicator_point.setY(signal_position.y());

        }
        else
        {
            indicator_point.setX(signal_position.x() - spcr - 1 - radius);
            indicator_point.setY(signal_position.y());

        }
    }
    else if ((post_pos == LEFT) || (post_pos == RIGHT))
    {
        if (signal_dir == LEFT)
        {
            indicator_point.setX(signal_position.x());
            indicator_point.setY(signal_position.y() - spcr - 1 - radius);
        }
        else
        {
            indicator_point.setX(signal_position.x());
            indicator_point.setY(signal_position.y() + POST_WIDTH + spcr + 1 + radius);
        }
    }
}

//!
//! \brief Draws the Signal Label
//!
//! Draws the label associated with the current signal
//!
//! \param signal_data IN Details of the screen signal
//! \param signal_id   IN The index of the signal
//!
//! \return None
//!
void DrawSignals::drawSignalLabel (BAKU_Signal *signal_data,
                                   QPoint indicator_point)
{
    QPoint l_point;
    int text_width;
    int text_height;
    //int font_id;
    int radius;
    int spcr = 0;
    int post_pos = ABOVE;
    int label_pos = ABOVE;
    int signal_dir = RIGHT;
    unsigned short rotate = 0;
    QFont font;
    QFontMetrics *metrics;

    // Set Post Position
    if (signal_data->post_pos >= ABOVE && signal_data->post_pos <= RIGHT)
    {
        post_pos = signal_data->post_pos;
    }

    // Set Label Position
    if (signal_data->label_pos >= ABOVE && signal_data->label_pos <= RIGHT)
    {
        label_pos = signal_data->label_pos;
    }

    // Set Signal Direction
    if (signal_data->signal_dir >= LEFT && signal_data->signal_dir <= RIGHT)
    {
        signal_dir = signal_data->signal_dir;
    }

    // Determine Radius
    switch (signal_data->signal_type)
    {
        case ASPECT_SIGNAL:
        case FIXED_RED_SIGNAL:
            radius = ASPECT_SIG_DEFAULT_RADIUS;
            font.setFamily("Tahoma");
            font.setPointSize(10);
            break;
        case SHUNT_SIGNAL:
            radius = SHUNT_SIG_DEFAULT_RADIUS;
            font.setFamily("Times");
            font.setPointSize(10);
            break;
        default:
            radius = DEFAULT_SIG_RADIUS;
            font.setFamily("Times");
            font.setPointSize(10);
            break;
    }

    metrics = new QFontMetrics(font);

    text_width = metrics->horizontalAdvance(signal_data->signal_label);
    text_height = metrics->capHeight();

    //Draw Signal Label
    if ((post_pos == ABOVE) || (post_pos == BELOW))
    {
        // Calculate Spacer
        if (signal_data->signal_type == SHUNT_SIGNAL && signal_data->draw_post ==0)
        {
            spcr = 1; //1 for gap
        }
        else
        {
            spcr = SIG_LG_SPCR_W + SIG_SM_SPCR_W + 3; //2 for post thickness, 1 for gap
        }

        // Post Position Above or Below Signal
        if (label_pos == ABOVE)
        {
            // Label Position Above Signal
            l_point.setY(indicator_point.y() - radius - 2);
            l_point.setX(indicator_point.x() - (text_width / 2));
        }
        else if (label_pos == BELOW)
        {
            // Label Position Below Signal
            l_point.setY(indicator_point.y() + radius + text_height + 3);
            l_point.setX(indicator_point.x() - (text_width / 2));
        }
        else if (label_pos == RIGHT)
        {
            // Label Position Right of Signal
            if (signal_dir == LEFT)
            {
                // Signal Direction Left
                l_point.setX(indicator_point.x() + radius + spcr);
            }
            else
            {
                // Signal Direction Right
                l_point.setX(indicator_point.x() + radius + 2); //1 Added for gap
            }

            l_point.setY(indicator_point.y() + (text_height / 2));
        }
        else if (label_pos == LEFT)
        {
            // Label Position Left of Signal
            if (signal_dir == RIGHT)
            {
                // Signal Direction Right
                l_point.setX(indicator_point.x() - radius - spcr - text_width);
            }
            else
            {
                // Signal Direction Left
                l_point.setX(indicator_point.x() - radius - text_width - 1); //1 Added for gap
            }

            l_point.setY(indicator_point.y() + (text_height / 2));
        }
    }
    else
    {
        if (label_pos == LEFT)
        {
            // Post Position Left of Signal
            l_point.setX(indicator_point.x() - radius - 2 - text_width);
            l_point.setY(indicator_point.y() - (text_height / 2));
        }
        else if (label_pos == RIGHT)
        {
            // Post Position Right of Signal
            l_point.setX(indicator_point.x() + radius + 2);
            l_point.setY(indicator_point.y() - (text_height / 2));
        }
        else if (label_pos == ABOVE)
        {
            l_point.setX(indicator_point.x() - radius - text_height);
            l_point.setY(indicator_point.y());
            rotate = 1;
        }
        else
        {
            // Calculate Spacer
            if (signal_data->signal_type == SHUNT_SIGNAL && signal_data->draw_post ==0)
            {
                spcr = 1; //1 for gap
            }
            else
            {
                spcr = SIGNAL_SPCR_LGTH;
            }

            // Label Position Below Signal
            if (signal_dir == LEFT)
            {
                // Signal Left
                l_point.setY(indicator_point.y() + radius + spcr);
                l_point.setX(indicator_point.x() - (text_width / 2));
            }
            else
            {
                // Signal Right
                l_point.setY(indicator_point.y() + radius);
                l_point.setX(indicator_point.x() - (text_width / 2));
            }
        }
    }

    m_signal_pen.setColor(Qt::black);
    m_signal_pen.setStyle(Qt::SolidLine);
    m_signal_pen.setWidth(1);

    m_painter->setPen(m_signal_pen);
    m_painter->setFont(font);

    if (rotate != 0)
    {
        m_painter->rotate(90);
        m_painter->drawText (l_point, signal_data->signal_label);
        m_painter->rotate(-90);
    }
    else
    {
        m_painter->drawText (l_point, signal_data->signal_label);
    }
}

//!
//! \brief Draws the Signal Label for a coloured signal
//!
//! \param signal_data IN 	Details of the screen Signals
//! \param signal_rect IN 	The bounding rect for the signal
//!
//! \return None
//!
void DrawSignals::drawColouredSignalLabel (BAKU_Signal *signal_data, QRect signal_rect)
{
    QPoint c_point;
    QPoint l_point;
    int text_width;
    int text_height;
    unsigned short rotate = 0;
    QFont font;
    QFontMetrics *metrics;

    font.setFamily("Tahoma");
    font.setPointSize(10);

    metrics = new QFontMetrics(font);

    text_width = metrics->horizontalAdvance(signal_data->signal_label);
    text_height = metrics->capHeight();

    //Calculate Centre Point
    c_point.setX(signal_rect.center().x());
    c_point.setY(signal_rect.center().y());

    //Draw Signal Label

    //Signal Above or Below Track
    if ( (signal_data->post_pos == ABOVE) || (signal_data->post_pos == BELOW))
    {
        if (signal_data->label_pos == ABOVE)
        {
            //Label Located Above Signal
            l_point.setY(signal_rect.top() - 2);
            l_point.setX(c_point.x() - (text_width / 2));
        }
        else if (signal_data->label_pos == BELOW)
        {
            //Label Located Below Signal
            l_point.setY(signal_rect.bottom() + text_height + 3);
            l_point.setX(c_point.x() - (text_width / 2));
        }
        else
        {
            l_point.setY(c_point.y() - (text_height / 2));

            //Left Direction
            if (signal_data->signal_dir == LEFT)
            {
                if (signal_data->label_pos == LEFT)
                {
                    //Label Located Left of Signal
                    l_point.setX(signal_rect.left() - CLRD_SPCR_LGTH - text_width);
                }
                else if (signal_data->label_pos == RIGHT)
                {
                    //Label Located Right of Signal
                    l_point.setX(signal_rect.right() + 1 + CLRD_SPCR_LGTH + POST_WIDTH);
                }
            }
            //Right Direction
            else if (signal_data->signal_dir == RIGHT)
            {
                if (signal_data->label_pos == LEFT)
                {
                    //Label Located Left of Signal
                    l_point.setX(signal_rect.left() - CLRD_SPCR_LGTH -
                                           POST_WIDTH - 1 - text_width);
                }
                else if (signal_data->label_pos == RIGHT)
                {
                    //Label Located Right of Signal
                    l_point.setX(signal_rect.right() + (COLOURED_SIG_HEIGHT / 2));
                }
            }
        }
    }
    //Signal Left or Right Track
    else
    {
        if (signal_data->label_pos == ABOVE)
        {
            //Label Located Above Signal
            l_point.setX(signal_rect.left() - text_height);
            l_point.setY(c_point.y());
            rotate = 1;
        }
        else if (signal_data->label_pos == BELOW)
        {
            //Label Located Below Signal
            l_point.setY(signal_rect.bottom() + text_height + 3);
            l_point.setX(c_point.x() - (text_width / 2));
        }
        else if (signal_data->label_pos == LEFT)
        {
            //Label Located Left of Signal
            l_point.setX(signal_rect.left() - 2 - text_width);
            l_point.setY(c_point.y() - (text_height / 2));
        }
        else if (signal_data->label_pos == RIGHT)
        {
            //Label Located Right of Signal
            l_point.setX(signal_rect.right() + 2);
            l_point.setY(c_point.y() - (text_height / 2));
        }
    }

    m_signal_pen.setColor(Qt::black);
    m_signal_pen.setWidth(1);

    m_painter->setPen(m_signal_pen);
    m_painter->setFont(font);

    if (rotate != 0)
    {
        m_painter->rotate(90);
        m_painter->drawText (l_point, signal_data->signal_label);
        m_painter->rotate(-90);
    }
    else
    {
        m_painter->drawText (l_point, signal_data->signal_label);
    }
}

//!
//! \brief Calculates the Signal spacer rectangles
//!
//! Calculates the spacer rectangles to drawn for Shunt signals
//!
//! \param signal_data IN		Details of the screen Signals
//! \param signal_position IN 	The calculated signal position
//! \param OUT sig_lg_spcr_rect	The large spacer rectangle
//! \param OUT sig_sm_spcr_rect The small spacer rectangle
//!
//! \return None
//!
void DrawSignals::calculateSignalRectangles (BAKU_Signal *signal_data,
                                             QPoint signal_position,
                                             QRect &sig_lg_spcr_rect,
                                             QRect &sig_sm_spcr_rect)
{
    int post_pos = LEFT;
    int signal_dir = RIGHT;

    // Set Post Position
    if (signal_data->post_pos >= ABOVE && signal_data->post_pos <= RIGHT)
    {
        post_pos = signal_data->post_pos;
    }

    // Set Signal Direction
    if (signal_data->signal_dir >= LEFT && signal_data->signal_dir <= RIGHT)
    {
        signal_dir = signal_data->signal_dir;
    }

    //Calculate Signal Positions
    if ( (post_pos == ABOVE) || (post_pos == BELOW))
    {
        // Above or Below Position
        if (signal_dir == RIGHT)
        {
            // Right Direction
            sig_lg_spcr_rect.setCoords(signal_position.x(),
                                      (signal_position.y() - (SIG_LG_SPCR_H / 2)),
                                      (signal_position.x() + (POST_WIDTH / 2) + SIG_LG_SPCR_W),
                                      (signal_position.y() + (SIG_LG_SPCR_H / 2)));

            sig_sm_spcr_rect.setCoords  (sig_lg_spcr_rect.right(),
                                        (signal_position.y() - (SIG_SM_SPCR_H / 2)),
                                        (sig_lg_spcr_rect.right() + SIG_SM_SPCR_W),
                                        (signal_position.y() + (SIG_SM_SPCR_H / 2)));
        }
        else
        {
            // Left Direction
            sig_lg_spcr_rect.setCoords ((signal_position.x() - SIG_LG_SPCR_W),
                                        (signal_position.y() - (SIG_LG_SPCR_H / 2)),
                                        signal_position.x() + (POST_WIDTH / 2),
                                        (signal_position.y() + (SIG_LG_SPCR_H / 2)));

            sig_sm_spcr_rect.setCoords ((sig_lg_spcr_rect.left() - SIG_SM_SPCR_W),
                                        (signal_position.y() - (SIG_SM_SPCR_H / 2)),
                                        sig_lg_spcr_rect.left(),
                                        (signal_position.y() + (SIG_SM_SPCR_H / 2)));

        }

    }
    else if ( (post_pos == LEFT) || (post_pos == RIGHT))
    {
        // Left or Right Position
        if (signal_dir == LEFT)
        {
            // Left Direction
            sig_lg_spcr_rect.setCoords ((signal_position.x() - (SIG_LG_SPCR_H / 2)),
                                        (signal_position.y() - SIG_LG_SPCR_W),
                                        (signal_position.x() + (SIG_LG_SPCR_H / 2)),
                                        (signal_position.y() + (POST_WIDTH / 2)));

            sig_sm_spcr_rect.setCoords ((signal_position.x() - (SIG_SM_SPCR_H / 2)),
                                        (sig_lg_spcr_rect.top()- SIG_SM_SPCR_W),
                                        (signal_position.x() + (SIG_SM_SPCR_H / 2)),
                                        sig_lg_spcr_rect.top());

        }
        else
        {
            // Right Direction
            sig_lg_spcr_rect.setCoords ((signal_position.x() - (SIG_LG_SPCR_H / 2)),
                                        signal_position.y(),
                                        (signal_position.x() + (SIG_LG_SPCR_H / 2)),
                                        (signal_position.y() + (POST_WIDTH / 2) + SIG_LG_SPCR_W));

            sig_sm_spcr_rect.setCoords ((signal_position.x() - (SIG_SM_SPCR_H / 2)),
                                        sig_lg_spcr_rect.bottom(),
                                        (signal_position.x() + (SIG_SM_SPCR_H / 2)),
                                        (sig_lg_spcr_rect.bottom() + SIG_SM_SPCR_W));

        }
    }
}

//!
//! \brief Calculates the Signal spacer end point
//!
//! Calculates the spacer end points for the line to be drawn between the post and signal
//!
//! \param signal_data IN		Details of the screen Signals
//! \param signal_position IN 	The calculated signal position
//! \param OUT sig_spcr_end		The spacer end points (X and Y)
//!
//! \return None
//!
void DrawSignals::calculateSignalSpacerEndPoint (BAKU_Signal *signal_data,
                                                 QPoint signal_position,
                                                 QPoint &sig_spcr_end)
{
    int post_pos = LEFT;
    int signal_dir = RIGHT;

    // Set Post Position
    if (signal_data->post_pos >= ABOVE && signal_data->post_pos <= RIGHT)
    {
        post_pos = signal_data->post_pos;
    }

    // Set Signal Direction
    if (signal_data->signal_dir >= LEFT && signal_data->signal_dir <= RIGHT)
    {
        signal_dir = signal_data->signal_dir;
    }

    //Calculate Spacer Points
    if ((post_pos == ABOVE) || (post_pos == BELOW))
    {
        //Post Position: Above or Below
        if (signal_dir == RIGHT)
        {
            //Signal Direction: Right
            sig_spcr_end.setX(signal_position.x() + POST_WIDTH + SIGNAL_SPCR_LGTH);
            sig_spcr_end.setY(signal_position.y());
        }
        else
        {
            //Signal Direction: Left
            sig_spcr_end.setX(signal_position.x() - SIGNAL_SPCR_LGTH);
            sig_spcr_end.setY(signal_position.y());
        }
    }
    else if ((post_pos == LEFT) || (post_pos == RIGHT))
    {
        //Post Position: Left or Right
        if (signal_dir == LEFT)
        {
            //Signal Direction: Left
            sig_spcr_end.setX(signal_position.x());
            sig_spcr_end.setY(signal_position.y() - SIGNAL_SPCR_LGTH);
        }
        else
        {
            //Signal Direction: Right
            sig_spcr_end.setX(signal_position.x());
            sig_spcr_end.setY(signal_position.y() + POST_WIDTH + SIGNAL_SPCR_LGTH);
        }
    }
}

//!
//! \brief Calculates the Bounding Rectangle for a Coloured Signal
//!
//! \param signal_data IN 	Details of the screen Signals
//! \param signal_position IN 	The calculated signal position
//! \param OUT signal_rect	The bounding rectangle
//!
//! \return None
//!
void DrawSignals::calculateColouredSignalRect(BAKU_Signal *signal_data, QPoint signal_position, QRect &signal_rect)
{
    int radius;
    int post_pos = LEFT;
    int signal_dir = RIGHT;
    int spcr;
    int signal_size = 0;
    int width = COLOURED_SIG_BODY_WIDTH;

    if (signal_data->signal_type == SMALL_COLOURED_SIGNAL)
    {
        width = SMALL_COLOURED_SIG_BODY_WIDTH;
    }

    spcr = SIGNAL_SPCR_LGTH;

    // Set Post Position
    if (signal_data->post_pos >= ABOVE && signal_data->post_pos <= RIGHT)
    {
        post_pos = signal_data->post_pos;
    }

    // Set Signal Direction
    if (signal_data->signal_dir >= LEFT && signal_data->signal_dir <= RIGHT)
    {
        signal_dir = signal_data->signal_dir;
    }

    radius = (COLOURED_SIG_HEIGHT / 2);
    signal_size = (radius * 2) + width;
    //Calculate Signal Positions
    if ((post_pos == ABOVE) || (post_pos == BELOW))
    {
        if (signal_dir == RIGHT)
        {
            signal_rect.setLeft(signal_position.x() + POST_WIDTH + spcr + 1);
            signal_rect.setRight(signal_rect.left() + signal_size);

        }
        else
        {
            signal_rect.setLeft(signal_position.x() - spcr - 1 - signal_size);
            signal_rect.setRight(signal_rect.left() + signal_size);
        }

        signal_rect.setTop(signal_position.y() - (COLOURED_SIG_HEIGHT / 2));
        signal_rect.setBottom(signal_rect.top() + COLOURED_SIG_HEIGHT);
    }
    else if ((post_pos == LEFT) || (post_pos == RIGHT))
    {
        if (signal_dir == LEFT)
        {
            signal_rect.setTop(signal_position.y() - spcr - 1 - signal_size);
            signal_rect.setBottom(signal_rect.top() + signal_size);
        }
        else
        {
            signal_rect.setTop(signal_position.y() + POST_WIDTH + spcr + 1);
            signal_rect.setBottom(signal_rect.top() + signal_size);
        }

        signal_rect.setLeft(signal_position.x() - (COLOURED_SIG_HEIGHT / 2));
        signal_rect.setRight(signal_rect.left() + COLOURED_SIG_HEIGHT);
    }
}


