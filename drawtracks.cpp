#include "drawtracks.h"
#include "dynamicdataconfig.h"


DrawTracks::DrawTracks(QFrame *frame)
{
    m_frame = frame;
}

//!
//! \brief Draws the static Track information
//!
//! Draws all of the relevant static track information onto the Signalling Screen
//!
//!
//! \return None
//!
void DrawTracks::draw (QPainter *painter)
{
    int t;

    m_painter = painter;

    m_track_brush.setStyle(Qt::SolidPattern);
    m_track_brush.setColor(Qt::black);
    m_track_pen.setColor(Qt::black);
    m_track_pen.setStyle(Qt::SolidLine);

    m_painter->setPen(m_track_pen);
    m_painter->setBrush(m_track_brush);

    //Determine whether track should be drawn, and relates to the selected screen
    for (t = 0; t < g_baku_dynamic_data.num_tracks && t < MAX_SCREEN_TRACKS; t++)
    {
        //Determine whether Labels should be displayed
        if ( (strlen(g_baku_data.track[t].track_label) > 0) &&
             (g_baku_data.track[t].label_pos != DONT_DISPLAY))
        {
            //Draw Labels
            drawLabel (&g_baku_dynamic_data.track[t].data, g_baku_dynamic_data.track[t].state);
        }
    }
}

//!
//! \brief Draws the Track Label
//!
//! Draws the label associated with the current track
//!
//! \param track_data IN Details of the screen track
//!
//! \return None
//!
void DrawTracks::drawLabel (BAKU_Track *track_data, int state)
{
    QPoint text_point;
    int track_width = 0;
    int text_width = 0;
    int text_height = 0;
    QFont font;
    QFontMetrics *metrics;
    QRect track_rect;
    int tokens = 0;
    int additional_text_height = 0;

    font.setFamily("Tahoma");
    font.setPointSize(11);

    m_painter->setFont(font);

    metrics = new QFontMetrics(font);

    //Determine whether the track is Occupied
    if (state == OCCUPIED)
    {
        //Occupied Track
        m_track_pen.setColor(Qt::red);
    }
    else
    {
        //Determine whether the track is a Dynamic Signalling Track
        if (track_data->track_type != DYNAMIC_SIGNALLING_TRACK)
        {
            m_track_pen.setColor(Qt::black);
        }
        else
        {
            //Dynamic Signalling Track
            m_track_pen.setColor(Qt::blue);
        }
    }

    m_painter->setPen(m_track_pen);

    text_width = metrics->horizontalAdvance(track_data->track_label);
    text_height = metrics->capHeight();

    // Calculate the coordinates of the track
    calculateRect (track_data, false, track_rect);

    if (track_data->label_pos != DONT_DISPLAY)
    {
        //Calculate Text Position
        calculateTextPosition (track_data, text_width, text_height, track_rect, text_point);

        // Calculate the Track Width
        calculateTrackWidth (track_data, track_rect, track_width);

        tokens = countTokens (&track_data->track_label[0]);

        //Count Tokens
        if ( (text_width > track_width) && tokens > 1)
        {
            if (track_data->label_pos == RIGHT || track_data->label_pos == LEFT)
            {
                // Adjust start Y position of the text
                additional_text_height = ((tokens-1) * (text_height-1));
                text_point.setY(text_point.y() - (additional_text_height/2));
            }
            splitLabel (text_point, track_data, metrics);
        }
        else
        {
            m_painter->drawText (text_point, track_data->track_label);
        }
    }
}

//!
//! \brief Calculates the Text Position
//!
//! Calculates the position where the text label should be drawn
//!
//! \param track_data IN Details of the screen track
//! \param text_width IN The Width of the text
//! \param text_height IN The Height of the text
//! \param font_id IN The font of the text
//! \param OUT track_point The calculated text position
//!
//! \return None
//!
void DrawTracks::calculateTextPosition (BAKU_Track *track_data,
                                        int text_width,
                                        int text_height,
                                        QRect track_rect,
                                        QPoint &text_point)
{
    QPoint centre_point;

    //Calculate Centre Point
    centre_point.setX(track_rect.left() + ( (track_rect.right() - track_rect.left()) / 2));
    centre_point.setY(track_rect.top() + ( (track_rect.bottom() - track_rect.top()) / 2));

    // Determine the Label Position in relation to the track
    if ( (track_data->label_pos == ABOVE) ||
         (track_data->label_pos == BELOW))
    {
        // Above or Below
        text_point.setX(centre_point.x() - (text_width / 2));

        if (track_data->label_pos == ABOVE)
        {
            text_point.setY(track_rect.top() - TRACK_LABEL_SPCR);
        }
        else
        {
            text_point.setY(track_rect.bottom() + TRACK_LABEL_SPCR + text_height);
        }
    }
    else
    {
        // Left or Right
        text_point.setY(centre_point.y() + (text_height / 2));

        // Determine whether track is displayed diagonally
        if (track_rect.right() - track_rect.left() > MAIN_TRACK_WIDTH)
        {
            if (track_data->label_pos == LEFT)
            {
                text_point.setX(centre_point.x() - (MAIN_TRACK_WIDTH /2) - text_width - TRACK_LABEL_SPCR);
            }
            else
            {
                text_point.setX(centre_point.x() + (MAIN_TRACK_WIDTH / 2) + TRACK_LABEL_SPCR);
            }

            text_point.setX(text_point.x() - ((MAIN_TRACK_WIDTH / 2) + TRACK_LABEL_SPCR));
        }
        else
        {
            // Straight Track
            if (track_data->label_pos == LEFT)
            {
                // Left
                text_point.setX(track_rect.left() - text_width - TRACK_LABEL_SPCR);
            }
            else
            {
                // Right
                text_point.setX(track_rect.right() + TRACK_LABEL_SPCR);
            }
        }
    }
}

//!
//! \brief Calculates the Track Width
//!
//! Calculates the width of the current track
//!
//! \param track_data IN Details of the screen track
//! \param track_rect IN The Bounding Rectangle of the Track
//! \param OUT track_width The calculated width of the track
//!
//! \return None
//!
void DrawTracks::calculateTrackWidth (BAKU_Track *track_data,
                                      QRect track_rect,
                                      int &track_width)
{
    // Determine the Label Position in relation to the track
    if ( (track_data->label_pos == ABOVE) ||
         (track_data->label_pos == BELOW))
    {
        track_width = (track_rect.right() - track_rect.left());
    }
    else
    {
        track_width = (track_rect.bottom() - track_rect.top());
    }
}

//!
//! \brief Calculate Track Bounds
//!
//! Calculates the rectangular bound of the track
//!
//! \param track_data IN Details of the screen track
//! \param extend_boundary IN Determines whether the track boundary should be extended
//! \param OUT rect The calculated rect for the track
//!
//! \return None
//!
void DrawTracks::calculateRect (BAKU_Track *track_data,
                                bool extend_boundary,
                                QRect &rect)
{
    int p;
    QPoint lowest;
    QPoint highest;

    lowest.setX(MAX_SCREEN_WIDTH);
    lowest.setY(m_frame->rect().bottom());
    highest.setX(0);
    highest.setY(0);

    for (p = 0; ((p < track_data->number_points*2) && (p < MAX_TRACK_POINTS*2)); p+=2)
    {
        // Set Highest and Lowest x,y co-ordinates
        if (track_data->track_points[p] > highest.x())
        {
            highest.setX(track_data->track_points[p]);
        }

        if (track_data->track_points[p] < lowest.x())
        {
            lowest.setX(track_data->track_points[p]);
        }

        if (track_data->track_points[p+1] > highest.y())
        {
            highest.setY(track_data->track_points[p+1]);
        }

        if (track_data->track_points[p+1] < lowest.y())
        {
            lowest.setY(track_data->track_points[p+1]);
        }
    }

    // Calculate bounds
    rect.setCoords( m_frame->rect().left() + lowest.x(), m_frame->rect().top() + lowest.y(),
                    m_frame->rect().left() + highest.x(), m_frame->rect().top() + highest.y());

    // Determine whether the track boundary should be extended
    if (extend_boundary == true)
    {
        // Extend Boundary to provide an improved clickable area
        rect.setLeft(rect.left() - TRACK_BUFFER);
        rect.setRight(rect.right() + TRACK_BUFFER);
        rect.setTop(rect.top() - TRACK_BUFFER);
        rect.setBottom(rect.bottom() + TRACK_BUFFER);
    }
}

//!
//! \brief Count the Label Tokens
//!
//! Calculate the number of elements of the track label. All
//! of the elements are separated by '.'
//!
//! \param track_label IN The Track Label
//!
//! \return The number of tokens
//!
int DrawTracks::countTokens (char *track_label)
{
    int count = 0;
    char * pch = nullptr;
    int c;
    char char_label[32];

    for (c = 0; c < 32; c++)
    {
        char_label[c] = track_label[c];
    }

    // Split the label into tokens
    pch = strtok (char_label, ".");

    if (pch != nullptr)
    {
        // Iterate the tokens
        while (pch != nullptr)
        {
            count++;
            pch = strtok (nullptr, ".");

        }
    }

    return count;
}

//!
//! \brief Split the label
//!
//! Split the label into elements and draw them onto the screen.
//! All of the elements are separated by '.'
//!
//! \param label_point IN The point where the label should start
//! \param track_data IN Details of the screen track
//! \param font_id IN the Font of the text
//!
//! \return None
//!
void DrawTracks::splitLabel (QPoint label_point,
                             BAKU_Track *track_data,
                             QFontMetrics *metrics)
{
    char * pch = nullptr;
    int c;
    int centre;
    char token[32];
    QPoint text_point;
    int text_height;
    int text_width;

    char char_label[32];

    for (c = 0; c < 32; c++)
    {
        char_label[c] = track_data->track_label[c];
    }

    // Calculate height and width of the text
    text_width =
        metrics->horizontalAdvance(track_data->track_label);

    if (track_data->label_pos == RIGHT || track_data->label_pos == LEFT)
    {
        if (track_data->label_pos == RIGHT)
        {
            centre = label_point.x() +
                    (calculateMaxLabelWidth(track_data, metrics) / 2);
        }
        else
        {
            centre = label_point.x() -
                    (calculateMaxLabelWidth(track_data, metrics) / 2);
        }
    }
    else
    {
        centre = label_point.x() + (text_width / 2);
    }
    text_point.setY(label_point.y());
    text_height = metrics->capHeight();

    pch = strtok (char_label, ".");

    // Draw the elements
    while (pch != nullptr)
    {
        strncpy (token, pch, 32);
        text_point.setX(centre - (metrics->horizontalAdvance (token) / 2));
        m_painter->drawText (text_point, token);
        if (track_data->label_pos == ABOVE)
        {
            text_point.setY(text_point.y() - text_height - 2);
        }
        else
        {
            text_point.setY(text_point.y() + text_height + 2);
        }
        pch = strtok (nullptr, ".");

    }
}

//!
//! \brief Calculate Max Label Width
//!
//! Calculates the max width of the track label
//!
//! \param track_data IN Details of the screen track
//! \param font_id IN the Font of the text
//!
//! \return None
//!
int DrawTracks::calculateMaxLabelWidth (BAKU_Track *track_data, QFontMetrics *metrics)
{
    char * pch = nullptr;
    int c;
    int width = 0;
    int max_width = 0;
    char token[32];

    char char_label[32];

    for (c = 0; c < 32; c++)
    {
        char_label[c] = track_data->track_label[c];
    }

    pch = strtok (char_label, ".");

    // Draw the elements
    while (pch != nullptr)
    {
        strcpy (token, pch);
        width = metrics->horizontalAdvance(token);

        if (width > max_width)
        {
            max_width = width;
        }
        pch = strtok (nullptr, ".");

    }

    return max_width;
}

void DrawTracks::drawSignallingTracks()
{
    int offset_points [MAX_TRACK_POINTS*2];
    int t;
    QRect rect;

    for (t = 0; t < g_baku_dynamic_data.num_tracks && t < MAX_SCREEN_TRACKS; t++)
    {
        g_baku_dynamic_data.track[t].track = new Track(m_frame);
        calculateTrackRect(g_baku_dynamic_data.track[t].data.track_points, g_baku_dynamic_data.track[t].data.number_points, &rect);
        offsetPoints(g_baku_data.track[t].track_points, g_baku_data.track[t].number_points, rect, offset_points);
        g_baku_dynamic_data.track[t].track->setGeometry(rect);
        g_baku_dynamic_data.track[t].track->setPoints(offset_points, g_baku_data.track[t].number_points);
        g_baku_dynamic_data.track[t].track->setType(g_baku_data.track[t].track_type);

        g_baku_dynamic_data.track[t].track->show();

        g_baku_dynamic_data.track[t].track->setState(UNOCCUPIED);

        if (g_baku_dynamic_data.track[t].has_train)
        {
            g_baku_dynamic_data.track[t].track->addTrain(g_baku_dynamic_data.track[t].train);
        }
    }
}

void DrawTracks::clearTracks()
{
    int t;

    for (t = 0; t < g_baku_dynamic_data.num_tracks && t < MAX_SCREEN_TRACKS; t++)
    {

        if (g_baku_dynamic_data.track[t].track != nullptr)
        {
            g_baku_dynamic_data.track[t].track->hide();
            g_baku_dynamic_data.track[t].track = nullptr;
        }
    }

    m_frame->repaint();

}

void DrawTracks::calculateTrackRect(int *points, int number_points, QRect *rect)
{
    int p;
    int x = m_frame->rect().right();
    int y = m_frame->rect().bottom();
    int x1 = 0;
    int y1 = 0;
    int point;

    for (p = 0; p < (number_points*2) && p < (MAX_TRACK_POINTS*2); p++)
    {
        if ((p % 2) == 0)
        {
            point= m_frame->rect().left() + points[p];

           if (point > x1)
           {
               x1 = point;
           }

           if (point < x)
           {
               x = point;
           }
        }
        else
        {
            point = m_frame->rect().top() + points[p];

            if (point > y1)
            {
                y1 = point;
            }

            if (point < y)
            {
                y = point;
            }
        }
    }

    rect->setCoords(x,y,x1,y1);
}

void DrawTracks::offsetPoints(int *points, int number_points, QRect rect, int *offset_points)
{
    int p;

    for (p = 0; p < (number_points*2) && p < (MAX_TRACK_POINTS*2); p++)
    {
        if ((p % 2) == 0)
        {
            offset_points[p] = (m_frame->rect().left() + points[p]) - rect.left();
        }
        else
        {
            offset_points[p] = (m_frame->rect().top() + points[p])- rect.top();
        }
    }
}
