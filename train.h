#ifndef TRAIN_H
#define TRAIN_H

#include <QWidget>
#include "component_common.h"

class Train : public QWidget
{
    Q_OBJECT

public:
    explicit Train(QWidget *parent = nullptr);
    void setData(BAKU_Train data);
    void updateData(BAKU_Train data);

protected:
    void paintEvent(QPaintEvent *e) override;
    void hideEvent(QHideEvent *e) override;

private:
    QWidget *m_parent;
    BAKU_Train m_train_data;


signals:

public slots:


};

#endif // TRAIN_H
