#ifndef COLOUREDSIGNAL_H
#define COLOUREDSIGNAL_H

#include "component_common.h"
#include "SignalIndicator.h"
#include "qpainterpath.h"

class ColouredSignal: public SignalIndicator
{
     Q_OBJECT
public:
    ColouredSignal(QWidget *parent = nullptr);
    void setSignalState(int state, int type);
    void setDirection(int direction);
    int getDirection();

protected:
    void paintEvent(QPaintEvent *e) override;
    void hideEvent(QHideEvent *e) override;

private:
    void drawBody(QPainter *painter);
    int m_red_state;
    int m_green_state;
    int m_direction;
    QWidget *m_parent;

signals:

public slots:
};


#endif // COLOUREDSIGNAL_H
