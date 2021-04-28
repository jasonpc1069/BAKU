#include "track.h"
#include <QPainter>

Track::Track(QWidget *parent) : QWidget(parent)
{
    m_number_points = 0;
    m_parent = parent;
    m_state = INITIAL_STATE;
    m_type = SIGNALLING_TRACK;
    m_train = nullptr;

    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::WindowStaysOnTopHint);
}

void Track::setState(int state)
{
    m_state = state;
    update();
}

int Track::getState()
{
    return m_state;
}

void Track::setType(int type)
{
    if (type < INVALID_TRACK_TYPE)
    {
        m_type = type;
    }
}

int Track::getType()
{
    return m_type;
}

void Track::setPoints (int *points, int number_points)
{
    int p;

    for (p = 0; p < (number_points*2) && p < (MAX_TRACK_POINTS*2); p++)
    {
        m_points[p] = points[p];
    }

    m_number_points = number_points;
}

void Track::addTrain(BAKU_Train &train_data)
{
    QRect train_rect;

    if (m_train != nullptr)
    {
        updateTrain(train_data);
    }
    else
    {
        calculateTrainRect(train_rect);

        m_train = new Train(m_parent);
        m_train->setData(train_data);
        m_train->setGeometry(train_rect);
        m_train->show();
    }

}

void Track::removeTrain()
{
    if (m_train != nullptr)
    {
        m_train->hide();
        m_train = nullptr;
    }
}

void Track::updateTrain(BAKU_Train &train_data)
{
    if (m_train != nullptr)
    {
        m_train->updateData(train_data);
    }
    else
    {
        addTrain(train_data);
    }
}

void Track::calculateTrainRect(QRect &train_rect)
{
    QPoint center = this->rect().center();

    center.setX(x() + center.x());
    center.setY(y() + center.y());

    train_rect.setLeft(center.x() - (TRAIN_WIDTH / 2));
    train_rect.setRight(center.x() + (TRAIN_WIDTH / 2));
    train_rect.setTop(center.y() - (TRAIN_HEIGHT / 2));
    train_rect.setBottom(center.y() + (TRAIN_HEIGHT / 2));
}

void Track::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);
    QPolygon poly;
    QBrush brush;
    QPen pen;

    painter.begin(this);

    if (m_number_points > 0)
    {
        poly.setPoints(m_number_points, m_points);
        if (m_type == NON_SIGNALLING_TRACK)
        {
           pen.setStyle(Qt::DashLine);
           pen.setColor(Qt::darkGray);

          painter.setPen(pen);

            // Draw polygon
           painter.drawPolygon(poly);
        }
        else
        {
            // Initialise Brush
            if (m_type == END_TRACK)
            {
                brush.setColor(Qt::black);
                brush.setStyle(Qt::SolidPattern);
            }
            else
            {
                if (m_state == UNOCCUPIED)
                {
                    brush.setColor("#812118");
                }
                else if (m_state == OCCUPIED)
                {
                    brush.setColor(Qt::red);
                }
                else
                {
                    brush.setColor(Qt::lightGray);
                }

                brush.setStyle(Qt::SolidPattern);
            }

            painter.setBrush(brush);
            painter.setPen(Qt::NoPen);

             // Draw polygon
            painter.drawPolygon(poly);
        }
     }

    painter.end();
}

void Track:: hideEvent(QHideEvent * /* unused */)
{
    if (m_train != nullptr)
    {
        removeTrain();
    }
    update();
}



