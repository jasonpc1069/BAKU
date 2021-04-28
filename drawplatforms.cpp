#include "drawplatforms.h"
#include "dynamicdataconfig.h"

DrawPlatforms::DrawPlatforms(QFrame *frame)
{
    m_frame = frame;
}

//!
//! \brief Adds the Platform
//!
//! Creates and adds all of the relevant platforms onto the Signalling Screen
//!
//!
void DrawPlatforms::addPlatforms ()
{
    int p;
    QRect platform_rect;
    int start_x;
    int start_y;

    start_x = m_frame->rect().left();
    start_y = m_frame->rect().top();

    for (p = 0; ( (p < MAX_SCREEN_PLATFORMS) && (p < g_baku_dynamic_data.num_platforms)); p++)
    {
        //Create Indicator
        if (g_baku_dynamic_data.platform[p].platform == nullptr)
        {
            //Draw Platform
            platform_rect.setCoords(start_x + g_baku_dynamic_data.platform[p].data.x_pos,
                                    start_y + g_baku_dynamic_data.platform[p].data.y_pos,
                                    start_x + g_baku_dynamic_data.platform[p].data.x_pos +
                                        g_baku_dynamic_data.platform[p].data.length,
                                    start_y + g_baku_dynamic_data.platform[p].data.y_pos +
                                        g_baku_dynamic_data.platform[p].data.height);

            //Create platform
            g_baku_dynamic_data.platform[p].platform = new Platform (m_frame);

            //Border State
            g_baku_dynamic_data.platform[p].platform->setBorderState(g_baku_dynamic_data.platform[p].data.display_border);

            //Disused State
            g_baku_dynamic_data.platform[p].platform->setDisusedState(g_baku_dynamic_data.platform[p].data.disused_state);

            // Labels
            g_baku_dynamic_data.platform[p].platform->setPlatformLabel(TOP_PLATFORM, g_baku_dynamic_data.platform[p].data.top_plat_label);
            g_baku_dynamic_data.platform[p].platform->setPlatformLabel(BOTTOM_PLATFORM, g_baku_dynamic_data.platform[p].data.bottom_plat_label);

            // Type
            g_baku_dynamic_data.platform[p].platform->setType (g_baku_dynamic_data.platform[p].data.type);

            g_baku_dynamic_data.platform[p].platform->setGeometry(platform_rect);

            g_baku_dynamic_data.platform[p].platform->show();
        }
    }
}

//!
//! \brief Clears the Platform Indicators
//!
//! Removes all of the relevant platform indicators from the Signalling Screen
//!
//!
void DrawPlatforms::clearCurrentPlatforms()
{
    int p;

    for (p = 0; ( (p < MAX_SCREEN_PLATFORMS) && (p < g_baku_dynamic_data.num_platforms)); p++)
    {
        if (g_baku_dynamic_data.platform[p].platform != nullptr)
        {
            g_baku_dynamic_data.platform[p].platform->hide();
            g_baku_dynamic_data.platform[p].platform= nullptr;
        }
    }
}

