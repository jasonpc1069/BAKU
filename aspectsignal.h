#ifndef ASPECTSIGNAL_H
#define ASPECTSIGNAL_H
#include "component_common.h"
#include "SignalIndicator.h"
#include "qpainterpath.h"

class AspectSignal : public SignalIndicator
{
    Q_OBJECT
public:
    explicit AspectSignal(QWidget *parent = nullptr);
    void setRadius (int radius);
    int getRadius();

protected:
    void paintEvent(QPaintEvent *e) override;
    void hideEvent(QHideEvent *e) override;

private:
    int m_radius;
    QWidget *m_parent;
    QPainterPath m_path;


signals:

public slots:
};

#endif // ASPECTSIGNAL_H
