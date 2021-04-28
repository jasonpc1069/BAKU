#include "train.h"
#include <QPainter>

Train::Train(QWidget *parent) : QWidget(parent)
{
    Qt::WindowFlags flags = windowFlags();
    setWindowFlags(flags | Qt::WindowStaysOnTopHint);
}

void Train::setData(BAKU_Train data)
{
    memcpy(&m_train_data, &data, sizeof(BAKU_Train));
    update();

}

void Train::updateData(BAKU_Train data)
{
    memcpy(&m_train_data, &data, sizeof(BAKU_Train));
    update();
}

void Train::paintEvent(QPaintEvent * /* unused */)
{
    QPainter painter(this);
    QBrush brush;
    QPen pen;
    QPoint centre = rect().center();
    QPoint text_point;
    QFont font;
    QFontMetrics *metrics;
    int text_width;
    int text_height;
    char trn[8];

    font.setFamily("Tahoma");
    font.setPointSize(14);
    font.setBold(true);

    sprintf(trn, "%03d", m_train_data.trn);

    metrics = new QFontMetrics(font);
    text_width = metrics->horizontalAdvance(trn);
    text_height = metrics->capHeight();

    pen.setColor(Qt::black);
    pen.setStyle(Qt::SolidLine);

    brush.setColor(Qt::darkGreen);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);

     // Draw Train
    painter.drawRect(rect());

    // Draw TRN
    text_point.setX(centre.x() - (text_width/2));
    text_point.setY(centre.y() + (text_height/2));

    pen.setWidth(1);
    pen.setColor(Qt::white);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(pen);
    painter.setFont(font);

    painter.drawText(text_point, trn);
}

void Train:: hideEvent(QHideEvent * /* unused */)
{
    update();
}



