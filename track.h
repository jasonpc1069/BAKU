#ifndef TRACK_H
#define TRACK_H

#include <QWidget>
#include "component_common.h"
#include "qpainterpath.h"
#include "train.h"

class Q_WIDGETS_EXPORT Track : public QWidget
{
    Q_OBJECT

    //Q_PROPERTY(int type READ getType WRITE setType)
    //Q_PROPERTY(int state READ getState WRITE setState)
public:
    explicit Track(QWidget *parent = nullptr);
    void setPoints (int *points, int number_points);
    void setType (int type);
    int getType();
    void setState (int state);
    int getState();
    void addTrain(BAKU_Train &train_data);
    void removeTrain();
    void updateTrain(BAKU_Train &train_data);

protected:
    void paintEvent(QPaintEvent *e) override;
    void hideEvent(QHideEvent *e) override;

private:
    void calculateTrainRect(QRect &train_rect);
    QPainterPath m_path;
    QWidget *m_parent;
    int m_points [MAX_TRACK_POINTS*2];
    int m_state;
    int m_type;
    int m_number_points;
    Train *m_train;



signals:

public slots:


};

#endif // TRACK_H
