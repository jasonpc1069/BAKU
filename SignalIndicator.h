#ifndef SIGNALINDICATOR_H
#define SIGNALINDICATOR_H

#include <QWidget>

class SignalIndicator : public QWidget
{
    Q_OBJECT
public:
    explicit SignalIndicator (QWidget *parent = nullptr);
    void setState (int state);
    int getState();
    virtual void setPostPosition (int post_position);
    virtual int getPostPosition();
    virtual void setCentrePoint (QPoint centre_point);
    virtual QPoint getCentrePoint ();
    virtual void setType (int type);
    virtual int getType ();

protected:
     int m_state;
     unsigned short m_post_position;
     int m_type;
     QPoint m_centre_point;

signals:

public slots:

};

#endif // SIGNALINDICATOR_H
