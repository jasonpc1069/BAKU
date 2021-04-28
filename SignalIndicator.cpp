#include "SignalIndicator.h"
#include "component_common.h"

SignalIndicator::SignalIndicator (QWidget *parent) : QWidget(parent)
{
    m_state = INITIAL_STATE;
    m_centre_point.setX(0);
    m_centre_point.setY(0);

    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::WindowStaysOnTopHint);
}

void SignalIndicator::setState(int state)
{
    m_state = state;
    update();
}

int SignalIndicator::getState()
{
    return m_state;
}

//!
//! \brief Sets the Indicator Centre Point
//!
//! \param centre_point IN The Indicator Centre Point
//!
//! \return None
//!
void SignalIndicator::setCentrePoint (QPoint centre_point)
{
    m_centre_point = centre_point;
}

//!
//! \brief Gets the Indicator Centre Point
//!
//! \param None
//!
//! \return The Indicator Centre Point
//!
QPoint SignalIndicator::getCentrePoint ()
{
    return m_centre_point;
}

//!
//! \brief Sets the post position of the signal
//!
//! \param post_position IN Position of the Signal Post [ABOVE/BELOW/LEFT/RIGHT]
//!
//! \return None
//!
void SignalIndicator::setPostPosition (int post_position)
{
    if (post_position > 0 && post_position < INVALID_POSITION)
    {
        m_post_position = post_position;
    }
}

//!
//! \brief Gets the post position of the shunt signal
//!
//! \param None
//!
//! \return Position of the Shunt Signal Post [ABOVE/BELOW/LEFT/RIGHT]
//!
int SignalIndicator::getPostPosition ()
{
    return m_post_position;
}

//!
//! \brief Sets the type of Signal
//!
//! \param type IN The Signal Type
//!
//! \return None
//!
void SignalIndicator::setType (int type)
{
    // Determine whether type is valid
    if ((type == ASPECT_SIGNAL) || (type == FIXED_RED_SIGNAL))
    {
        m_type = type;
    }
}

//!
//! \brief Sets the type of Signal
//!
//! \param IN None
//!
//! \return The Signal Type
//!
int SignalIndicator::getType ()
{
    return m_type;
}
