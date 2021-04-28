#include "platform.h"
#include <QPainter>

Platform::Platform(QWidget *parent) : QWidget(parent)
{
    int p;

    for (p = 0; p < MAX_PLATFORM_INDEX; p++)
    {
        strcpy(m_plat_label[p],"");
    }

    m_display_border = true;
    m_disused_state = false;
    m_type = PLATFORM_TYPE;
}

//!
//! \brief Determine whether a Border should be displayed
//!
//! \param display_border IN TRUE or FALSE
//!
//! \return None
//!
void Platform::setBorderState (bool display_border)
{
    m_display_border = display_border;
    update();
}


//!
//! \brief Gets the State of the Border Display
//!
//! \param None
//!
//! \return TRUE or FALSE
//!
bool Platform::getBorderState ()
{
    return m_display_border;
}

//!
//! \brief Determine whether the Platform is disused
//!
//! \param disused_state IN TRUE or FALSE
//!
//! \return None
//!
void Platform::setDisusedState (bool disused_state)
{
    m_disused_state = disused_state;
    update();
}


//!
//! \brief Gets the Platform Disused State
//!
//! \param None
//!
//! \return TRUE or FALSE
//!
bool Platform::getDisusedState ()
{
    return m_disused_state;
}

//!
//! \brief Sets the Control Type
//!
//! \param type IN The control type (PLATFORM, IMR)
//!
//! \return None
//!
void Platform::setType (int type)
{
    if (type < UNKNOWN_PLATFORM_TYPE)
    {
        m_type = type;
    }
    update();
}

//!
//! \brief gets the Control Type
//!
//! \param None
//!
//! \return The control type (PLATFORM, IMR)
//!
int Platform::getType ()
{
    return m_type;
}

//!
//! \brief Sets the Platform Label
//!
//! \param platform IN The Platform Index
//! \param label IN The Top Platform Label
//!
//!	\return None
//!
void Platform::setPlatformLabel (int platform, char *label)
{
    if (label != nullptr && platform < MAX_PLATFORM_INDEX)
    {
        strncpy(m_plat_label[platform], label, 16);
    }
}


//!
//! \brief Gets the Platform Label
//!
//! \param platform IN The Platform Index
//!
//!	\return The Platform Label
//!
char *Platform::getPlatformLabel(int platform)
{
    char *label = nullptr;

    if (platform < MAX_PLATFORM_INDEX)
    {
        label = m_plat_label[platform];
    }

    return label;
}

//!
//! \brief Draws the Platform
//!
//! \param Invalid IN The Area in which to draw the Platform
//!
//! \return None
//!
void Platform::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);
    QBrush platform_brush;
    QPen platform_pen;
    QColor fill_colour;

    //Set Platform Colours
    platform_brush.setStyle(Qt::SolidPattern);

    //Determine whether the platform is disused
    if (m_disused_state == true)
    {
        fill_colour = Qt::darkGray;
    }
    else
    {
        if (m_type == IMR_TYPE)
        {
            fill_colour = Qt::white;
            platform_pen.setWidth(5);
        }
        else
        {
            fill_colour = Qt::yellow;
        }
    }

    //Determine whether a border should be displayed
    if (m_display_border == true)
    {
        //Border
        platform_pen.setColor (Qt::black);
    }
    else
    {
        //No Border
        platform_pen.setColor (fill_colour);
    }

    platform_brush.setColor(fill_colour);

    painter.setBrush(platform_brush);
    painter.setPen(platform_pen);
    painter.drawRect(this->rect());

    drawPlatformLabels();
}

void Platform::drawPlatformLabels()
{
    QPainter painter(this);
    QPen platform_pen;
    QPoint centre_point;
    QPoint plat_label_point;
    QColor text_colour;
    QFont font;
    QFontMetrics *metrics;
    int centre_top_y;
    int centre_bottom_y;

    platform_pen.setColor(Qt::black);

    font.setFamily("Tahoma");
    font.setPointSize(12);

    metrics = new QFontMetrics(font);
    painter.setFont(font);

    text_colour = Qt::black;

    // Calculate positions for labels

    centre_point.setX(this->rect().center().x());
    centre_point.setY(this->rect().center().y());

    centre_top_y = this->rect().top()  +  ((centre_point.y() - this->rect().top()) / 2);
    centre_bottom_y = centre_point.y() + ((this->rect().bottom()  - centre_point.y()) / 2);

    // Labels
    // Top Platform Label
    if (m_plat_label[TOP_PLATFORM] != nullptr && m_plat_label[TOP_PLATFORM][0] != 'C')
    {
        plat_label_point.setX(centre_point.x() -
                ( metrics->horizontalAdvance(m_plat_label[TOP_PLATFORM]) / 2));

        // Set Y Position
        if ((m_type == IMR_TYPE) &&
            (m_plat_label[BOTTOM_PLATFORM] == nullptr || strlen(m_plat_label[BOTTOM_PLATFORM]) == 0))
        {
            plat_label_point.setY(centre_point.y() + (metrics->capHeight() / 2));
        }
        else
        {
            plat_label_point.setY(centre_top_y + (metrics->capHeight() / 2));
        }

        platform_pen.setColor(text_colour);

        painter.setPen(platform_pen);
        painter.drawText (plat_label_point, m_plat_label[TOP_PLATFORM]);
    }

    // Bottom Platform Label
    if (m_plat_label[BOTTOM_PLATFORM] != nullptr)
    {
        //Bottom Label
         plat_label_point.setX(centre_point.x() -
                (metrics->horizontalAdvance (m_plat_label[BOTTOM_PLATFORM]) / 2));

        // Set Y Position
        if ((m_type == IMR_TYPE) &&
            (m_plat_label[TOP_PLATFORM] == nullptr || strlen(m_plat_label[TOP_PLATFORM]) == 0))
        {
            plat_label_point.setY(centre_point.y() + (metrics->capHeight() / 2));
        }
        else
        {
            plat_label_point.setY(centre_bottom_y + (metrics->capHeight() / 2));
        }

        platform_pen.setColor(text_colour);

        painter.setPen(platform_pen);
        painter.drawText (plat_label_point, m_plat_label[BOTTOM_PLATFORM]);
    }

    delete metrics;

}

void Platform:: hideEvent(QHideEvent * /* unused */)
{
    update();
}
