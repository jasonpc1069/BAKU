#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include "drawtracks.h"
#include "drawsignals.h"
#include "drawplatforms.h"
#include "screenframe.h"

typedef struct
{
    char tag[32];
    bool state;
    char signal_tag[32];
    bool has_signal;
    int trn;
} State_IO;

typedef struct
{
    int num_tracks[2];
    State_IO io[2][64];
} State_Map;

typedef struct
{
    int direction;
    int index;
    int trn;
} Train_Data;

#define MAX_TRAINS 6

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;


private slots:
    void on_screenButton_pressed();
    void updateState();
    void on_wbButton_pressed();
    void on_ebButton_pressed();

private:
    void mapPICUData();
    void updateDynamicData();
    void updateSignalling();
    void createStateMap();
    Ui::MainWindow *ui;
    unsigned short m_site_id;
    DrawTracks *m_draw_tracks;
    DrawSignals *m_draw_signals;
    DrawPlatforms *m_draw_platforms;
    ScreenFrame *m_screen_frame;
    QTimer *m_state_timer;
    State_Map m_state_map;
    Train_Data m_trains[MAX_TRAINS];
    int m_num_trains;
    int m_trn;
};

#endif // MAINWINDOW_H
