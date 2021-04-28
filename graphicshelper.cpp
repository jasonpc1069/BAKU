#include "graphicshelper.h"

GraphicsHelper::GraphicsHelper()
{

}

//!
//! \brief Destructor
//!
//!	\param None
//!
//! \return None
//!
GraphicsHelper::~GraphicsHelper()
{
}

//!
//! \brief Calculates a point on a circle.
//!
//! \param IN centre_point		The centre point of the circle
//! \param IN radius			The radius of the circle
//! \param IN angle				The circle angle
//! \param IN inverse_vertical	Determines whether the x co-ordinate should be inversed
//!	\param OUT circle_point		The calculated point
//!
//! \return The Graphics Helper Instance
//!
void GraphicsHelper::calculateCirclePoint(QPoint centre_point,
                                          unsigned short radius,
                                          short angle,
                                          bool inverse_vertical,
                                          QPoint &circle_point)
{
    circle_point.setX(centre_point.x() + radius * cos(angle*(M_PI / 180)));

    // Determine whether vertical should be inversed
    if (inverse_vertical)
    {
        // Inverse Vertical
        circle_point.setY(centre_point.y() + radius * sin((angle*(-1))*(M_PI / 180)));
    }
    else
    {
        circle_point.setY(centre_point.y() + radius * sin(angle * (M_PI / 180)));
    }
}

//!
//! \brief Calculates a point on the screen.
//!
//! \param start_x IN	The starting x position
//! \param start_y IN	The starting y position
//! \param comp_x IN	The component x offset
//! \param comp_y IN	The component y offset
//!	\param point OUT	The calculated point
//!
//! \return The Graphics Helper Instance
//!
void GraphicsHelper::calculatePoint (int start_x,
                                     int start_y,
                                     int comp_x,
                                     int comp_y,
                                     QPoint &point)
{
    // Calculate Point
    point.setX(start_x + comp_x);
    point.setY(start_y + comp_y);
}
