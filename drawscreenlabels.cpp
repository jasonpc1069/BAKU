#include "drawscreenlabels.h"
#include "dynamicdataconfig.h"
#include "component_common.h"
#include "graphicshelper.h"

DrawScreenLabels::DrawScreenLabels(QFrame *frame)
{
    m_frame = frame;
}

void DrawScreenLabels::draw(QPainter* painter)
{
    int l;
    QPoint label_point;
    QFont font;
    GraphicsHelper helper;

    m_painter = painter;

    font.setFamily("Tahoma");
    font.setPointSize(20);
    font.setBold(true);

    m_brush.setStyle(Qt::SolidPattern);
    m_brush.setColor(Qt::black);
    m_pen.setColor(Qt::black);
    m_pen.setStyle(Qt::SolidLine);

    m_painter->setPen(m_pen);
    m_painter->setBrush(m_brush);


    for (l = 0; ( (l < MAX_SCREEN_LABELS) && (l < g_baku_dynamic_data.num_labels)); l++)
    {
        //Determine the size of the font
        if (g_baku_dynamic_data.label[l].data.label_font_id == FONT_SIZE_LARGE)
            //Large Font
            font.setPointSize(24);
        else if (g_baku_dynamic_data.label[l].data.label_font_id == FONT_SIZE_MEDIUM)
            //Medium Font
           font.setPointSize(18);
        else if (g_baku_dynamic_data.label[l].data.label_font_id  == FONT_SIZE_SMALL)
            //Small Font
            font.setPointSize(16);
        else if (g_baku_dynamic_data.label[l].data.label_font_id == FONT_SIZE_TRACK)
        {
            // Track Font
            font.setPointSize(10);
            font.setBold(false);
        }

        m_painter->setFont(font);

        helper.calculatePoint(m_frame->rect().left(),  m_frame->rect().top(),
               g_baku_dynamic_data.label[l].data.x_pos,
               g_baku_dynamic_data.label[l].data.y_pos, label_point);


        painter->drawText (label_point, g_baku_dynamic_data.label[l].data.label_name);
    }
}
