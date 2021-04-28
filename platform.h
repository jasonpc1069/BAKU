#ifndef PLATFORM_H
#define PLATFORM_H

#include <QWidget>
#include "component_common.h"

class Platform : public QWidget
{
    Q_OBJECT
public:
    explicit Platform(QWidget *parent = nullptr);
    void setPlatformLabel (int platform, char *label);
    char *getPlatformLabel(int platform);
    void setType (int type);
    int getType();
    void setDisusedState (bool disused_state);
    bool getDisusedState();
    void setBorderState (bool display_border);
    bool getBorderState();

protected:
    void paintEvent(QPaintEvent *e) override;
    void hideEvent(QHideEvent *e) override;

private:
    void drawPlatformLabels();
    char m_plat_label [MAX_PLATFORM_INDEX][16];
    bool m_disused_state;
    bool m_display_border;
    int m_type;


signals:

};

#endif // PLATFORM_H
