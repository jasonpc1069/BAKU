#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFormLayout>
#include "component_common.h"
#include "bakudataconfig.h"
#include "heathrowt123.h"
#include "turnhamgreen.h"
#include "piccadillycircus.h"
#include "oxfordcircus.h"
#include "oakwood.h"
#include "dynamicdataconfig.h"

PICU_Static_Site_Cfg g_picu_static_data;
BAKU_Dynamic_Data_Cfg g_baku_dynamic_data;
BAKU_Site_Cfg g_baku_data;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup Data
    createStateMap();
    memcpy (&g_baku_data, &oxfordcircus_data, sizeof(BAKU_Site_Cfg));
    updateDynamicData();

    m_site_id = OXFORD_CIRCUS;

    // Initialise Components
    m_screen_frame = new ScreenFrame(this);
    m_screen_frame->setGeometry(QRect(0,0,1920,651));
    m_screen_frame->setStyleSheet("background-color: rgb(204, 204, 204)");

    m_draw_platforms = new DrawPlatforms(m_screen_frame);
    m_draw_platforms->addPlatforms();

    m_draw_tracks = new DrawTracks(m_screen_frame);
    m_draw_tracks->drawSignallingTracks();

    m_draw_signals = new DrawSignals(m_screen_frame);
    m_draw_signals->drawIndicators();

    m_screen_frame->show();

    // Initialise Trains
    m_num_trains = 0;
    m_trn = 1;
    memset(m_trains,0,sizeof(m_trains));

    // Initialise Timer
    m_state_timer = new QTimer(this);
    connect(m_state_timer, SIGNAL(timeout()), this, SLOT(updateState()));
    m_state_timer ->start(2000);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::updateDynamicData()
{
    int c;
    memset(&g_baku_dynamic_data, 0, sizeof(g_baku_dynamic_data));

    // Tracks
    g_baku_dynamic_data.num_tracks = g_baku_data.num_tracks;

    for (c=0; c < g_baku_data.num_tracks; c++)
    {
        memcpy(&g_baku_dynamic_data.track[c].data, &g_baku_data.track[c], sizeof(BAKU_Track));
    }

    // Signals
    g_baku_dynamic_data.num_signals = g_baku_data.num_signals;

    for (c=0; c < g_baku_data.num_signals; c++)
    {
        memcpy(&g_baku_dynamic_data.signal[c].data, &g_baku_data.signal[c], sizeof(BAKU_Signal));
    }

    // Platforms
    g_baku_dynamic_data.num_platforms = g_baku_data.num_platforms;

    for (c=0; c < g_baku_data.num_platforms; c++)
    {
        memcpy(&g_baku_dynamic_data.platform[c].data, &g_baku_data.platform[c], sizeof(BAKU_Platform));
    }


    // Screen Labels
    g_baku_dynamic_data.num_labels = g_baku_data.num_labels;

    for (c=0; c < g_baku_data.num_labels; c++)
    {
        memcpy(&g_baku_dynamic_data.label[c].data, &g_baku_data.label[c], sizeof(BAKU_Screen_Label));
    }

}

void MainWindow::mapPICUData()
{
    int c;

    memset (&g_baku_data, 0, sizeof(BAKU_Site_Cfg));

    // Copy Signals
    g_baku_data.num_signals = g_picu_static_data.num_signals;

    for (c=0; c < g_picu_static_data.num_signals; c++)
    {
        g_baku_data.signal[c].signal_id = g_picu_static_data.signal[c].signal_id;
        strncpy(g_baku_data.signal[c].signal_label, g_picu_static_data.signal[c].signal_label, 64);
        strncpy(g_baku_data.signal[c].signal_name, g_picu_static_data.signal[c].signal_name, 64);
        g_baku_data.signal[c].signal_type= g_picu_static_data.signal[c].signal_type;
        g_baku_data.signal[c].post_x = g_picu_static_data.signal[c].post_x;
        g_baku_data.signal[c].post_y = g_picu_static_data.signal[c].post_y;
        g_baku_data.signal[c].label_pos = g_picu_static_data.signal[c].label_pos;
        g_baku_data.signal[c].post_pos = g_picu_static_data.signal[c].post_pos;
        g_baku_data.signal[c].signal_dir = g_picu_static_data.signal[c].signal_dir;
        g_baku_data.signal[c].draw_post = g_picu_static_data.signal[c].draw_post;
        g_baku_data.signal[c].display_signal = g_picu_static_data.signal[c].display_signal;
        g_baku_data.signal[c].io_type = g_picu_static_data.signal[c].io_type;
    }

    // Copy Tracks
    g_baku_data.num_tracks = g_picu_static_data.num_tracks;

    for (c=0; c < g_picu_static_data.num_tracks; c++)
    {
        memcpy(&g_baku_data.track[c], &g_picu_static_data.track[c], sizeof(BAKU_Track));
    }

    // Copy Platforms
    g_baku_data.num_platforms = g_picu_static_data.num_platforms;

    for (c=0; c < g_picu_static_data.num_platforms; c++)
    {
        g_baku_data.platform[c].top_platform_id = g_picu_static_data.platform[c].top_platform_id;
        g_baku_data.platform[c].bottom_platform_id = g_picu_static_data.platform[c].bottom_platform_id;
        g_baku_data.platform[c].x_pos = g_picu_static_data.platform[c].x_pos;
        g_baku_data.platform[c].y_pos = g_picu_static_data.platform[c].y_pos;
        g_baku_data.platform[c].length = g_picu_static_data.platform[c].length;
        g_baku_data.platform[c].height = g_picu_static_data.platform[c].height;
        strncpy(g_baku_data.platform[c].top_plat_label, g_picu_static_data.platform[c].top_plat_label, 8);
        strncpy(g_baku_data.platform[c].bottom_plat_label, g_picu_static_data.platform[c].bottom_plat_label, 8);
        g_baku_data.platform[c].display_border = g_picu_static_data.platform[c].display_border;
        g_baku_data.platform[c].disused_state = g_picu_static_data.platform[c].disused_state;
        g_baku_data.platform[c].type = g_picu_static_data.platform[c].type;
    }

    // Copy Screen Labels
    g_baku_data.num_labels = g_picu_static_data.num_labels;

    for (c=0; c < g_picu_static_data.num_labels; c++)
    {
        g_baku_data.label[c].label_id = g_picu_static_data.label[c].label_id;
        g_baku_data.label[c].x_pos = g_picu_static_data.label[c].x_pos;
        g_baku_data.label[c].y_pos = g_picu_static_data.label[c].y_pos;
        g_baku_data.label[c].label_font_id = g_picu_static_data.label[c].label_font_id;
        strncpy(g_baku_data.label[c].label_name , g_picu_static_data.label[c].label_name , 20);
    }


}

void MainWindow::updateSignalling()
{
    int s;
    int t;
    int d;
    int sig;

    BAKU_Train train;

    for (d = EASTBOUND; d <= WESTBOUND; d++)
    {
        for (s=0; s < m_state_map.num_tracks[d]; s++)
        {
            train.trn = m_state_map.io[d][s].trn;

            for (t=0; t < g_baku_dynamic_data.num_tracks; t++)
            {
                if (strcmp(g_baku_dynamic_data.track[t].data.track_name, m_state_map.io[d][s].tag) == 0)
                {
                    if (m_state_map.io[d][s].state)
                    {
                        if (g_baku_dynamic_data.track[t].data.display_train)
                        {
                            g_baku_dynamic_data.track[t].has_train = 1;
                            g_baku_dynamic_data.track[t].track->addTrain(train);
                        }
                        g_baku_dynamic_data.track[t].state = OCCUPIED;
                        g_baku_dynamic_data.track[t].track->setState(OCCUPIED);
                    }
                    else
                    {
                        if (g_baku_dynamic_data.track[t].has_train)
                        {
                            g_baku_dynamic_data.track[t].track->removeTrain();
                        }
                        g_baku_dynamic_data.track[t].has_train = 0;
                        g_baku_dynamic_data.track[t].state = UNOCCUPIED;
                        g_baku_dynamic_data.track[t].track->setState(UNOCCUPIED);
                    }

                    if (m_state_map.io[d][s].has_signal)
                    {
                        for (sig = 0; sig < g_baku_dynamic_data.num_signals; sig++)
                        {
                            if (strcmp(g_baku_dynamic_data.signal[sig].data.signal_name, m_state_map.io[d][s].signal_tag) == 0)
                            {
                                if (m_state_map.io[d][s].state)
                                {
                                    g_baku_dynamic_data.signal[sig].state = ON;
                                    g_baku_dynamic_data.signal[sig].signal->setState(ON);
                                }
                                else
                                {
                                    g_baku_dynamic_data.signal[sig].state = OFF;
                                    g_baku_dynamic_data.signal[sig].signal->setState(OFF);
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    m_screen_frame->update();
}

void MainWindow::createStateMap()
{
    int t,d,s;
    int id = OXFORD_CIRCUS;
    int idx = 0;
    BAKU_Site_Cfg baku_data;

    memcpy (&baku_data, &oxfordcircus_data, sizeof(BAKU_Site_Cfg));
    memset(&m_state_map,0,sizeof(m_state_map));

    //State Map
    for (d = EASTBOUND; d <= WESTBOUND; d++)
    {
        for (s = 0; s < 2; s++)
        {
            for (t = 0; t < baku_data.num_tracks; t++)
            {
                if (baku_data.track[t].display_train &&
                    baku_data.track[t].direction == d)
                {
                    idx = m_state_map.num_tracks[d];
                    strncpy(m_state_map.io[d][idx].tag, baku_data.track[t].track_name, 32);
                    m_state_map.io[d][idx].state = 0;
                    m_state_map.io[d][idx].has_signal = 0;

                    if (id == PICCADILLY_CIRCUS)
                    {
                        if (strcmp(baku_data.track[t].track_label, "362A") == 0)
                        {
                            strncpy(m_state_map.io[d][idx].signal_tag, "I_BP_120_GR", 32);
                            m_state_map.io[d][idx].has_signal = 1;
                        }
                        else if (strcmp(baku_data.track[t].track_label, "362B") == 0)
                        {
                            strncpy(m_state_map.io[d][idx].signal_tag, "I_BP_12_GR", 32);
                            m_state_map.io[d][idx].has_signal = 1;
                        }
                        else if (strcmp(baku_data.track[t].track_label, "362C") == 0)
                        {
                            strncpy(m_state_map.io[d][idx].signal_tag, "I_BP_11_GR", 32);
                            m_state_map.io[d][idx].has_signal = 1;
                        }
                        else if (strcmp(baku_data.track[t].track_label, "381B") == 0)
                        {
                            strncpy(m_state_map.io[d][idx].signal_tag, "I_BP_1_GR", 32);
                            m_state_map.io[d][idx].has_signal = 1;
                        }
                        else if (strcmp(baku_data.track[t].track_label, "NB") == 0)
                        {
                            strncpy(m_state_map.io[d][idx].signal_tag, "I_BP_9_GR", 32);
                            m_state_map.io[d][idx].has_signal = 1;
                        }
                    }

                    m_state_map.num_tracks[d]++;
                 }
            }

            // Change Site
            if (s == 0)
            {
                if (id == OXFORD_CIRCUS)
                {
                    memcpy (&baku_data, &piccadillycircus_data, sizeof(BAKU_Site_Cfg));
                    id = PICCADILLY_CIRCUS;
                }
                else
                {
                    memcpy (&baku_data, &oxfordcircus_data, sizeof(BAKU_Site_Cfg));
                    id = OXFORD_CIRCUS;
                }
            }
        }
    }
}

void MainWindow::on_screenButton_pressed()
{
    int t;

    m_draw_platforms->clearCurrentPlatforms();
    m_draw_tracks->clearTracks();
    m_draw_signals->clearCurrentIndicators();

    if (m_site_id == PICCADILLY_CIRCUS)
    {
        memcpy (&g_baku_data, &oxfordcircus_data, sizeof(BAKU_Site_Cfg));
        m_site_id = OXFORD_CIRCUS;
//        mapPICUData();
    }
//    else if (m_site_id == HEATHROW_T123)
//    {
//        memcpy (&g_picu_static_data, &oakwood_data, sizeof(PICU_Static_Site_Cfg));
//        m_site_id = OAKWOOD;
//        mapPICUData();
//        ui->stateButton->setEnabled(false);
//    }
//    else if (m_site_id == TURNHAM_GREEN)
//    {
//        memcpy (&g_picu_static_data, &heathrow_t1234_data, sizeof(PICU_Static_Site_Cfg));
//        m_site_id = HEATHROW_T123;
//        mapPICUData();
//        ui->stateButton->setEnabled(false);
//    }
    else if (m_site_id == OXFORD_CIRCUS)
    {
        memcpy (&g_baku_data, &piccadillycircus_data, sizeof(BAKU_Site_Cfg));
        m_site_id = PICCADILLY_CIRCUS;
    }
//    else if (m_site_id == OAKWOOD)
//    {
//        memcpy (&g_baku_data, &oxfordcircus_data, sizeof(BAKU_Site_Cfg));
//        m_site_id = PICCADILLY_CIRCUS;
//        ui->stateButton->setEnabled(false);
//    }

    updateDynamicData();

    m_draw_tracks->drawSignallingTracks();
    m_draw_signals->drawIndicators();
    m_draw_platforms->addPlatforms();

    m_screen_frame->update();

    updateSignalling();
}

void MainWindow::on_wbButton_pressed()
{
    if (m_num_trains < MAX_TRAINS)
    {
        // Create Westbound Train
        m_trains[m_num_trains].direction = WESTBOUND;
        m_trains[m_num_trains].index = 0;
        m_trains[m_num_trains].trn = m_trn;

        m_state_map.io[WESTBOUND][0].state = 1;
        m_state_map.io[WESTBOUND][0].trn = m_trn;
        m_num_trains++;
        m_trn++;
        updateSignalling();
    }

    ui->wbButton->setEnabled(false);

    // Determine whether the maximum number of trains have been added
    if (m_num_trains == MAX_TRAINS)
    {
        ui->ebButton->setEnabled(false);
    }
}

void MainWindow::on_ebButton_pressed()
{
    if (m_num_trains < MAX_TRAINS)
    {
        // Create Eastbound Train
        m_trains[m_num_trains].direction = EASTBOUND;
        m_trains[m_num_trains].index = 0;
        m_trains[m_num_trains].trn = m_trn;

        m_state_map.io[EASTBOUND][0].state = 1;
        m_state_map.io[EASTBOUND][0].trn = m_trn;
        m_num_trains++;
        m_trn++;
        updateSignalling();
    }


    ui->ebButton->setEnabled(false);

    // Determine whether the maximum number of trains have been added
    if (m_num_trains == MAX_TRAINS)
    {
        ui->wbButton->setEnabled(false);
    }

}

void MainWindow::updateState()
{
    int t,t1;
    int dir = 0;
    int idx = 0;

    // Set Train Positions
    for (t = 0; t < m_num_trains; t++)
    {
        dir = m_trains[t].direction;
        idx = m_trains[t].index;
        m_state_map.io[dir][idx].state = 0;

        idx++;

        if (idx==m_state_map.num_tracks[dir])
        {
            m_trains[t].index = -1;
        }
        else
        {
            m_state_map.io[dir][idx].state = 1;
            m_state_map.io[dir][idx].trn = m_trains[t].trn;
            m_trains[t].index = idx;
        }
    }

    // Check for Finished Trains
    for (t = 0; t < m_num_trains; t++)
    {
        if (m_trains[t].index == -1)
        {
            if (t+1 == MAX_TRAINS)
            {
                // Delete Last Train
                memset(&m_trains[t],0,sizeof(Train_Data));
                m_num_trains--;
            }
            else
            {
                // Delete Train and resort
                for (t1 = t; t1 < (m_num_trains-1); t1++)
                {
                    memcpy(&m_trains[t1],&m_trains[t1+1],sizeof(Train_Data));
                }

                memset(&m_trains[m_num_trains-1],0,sizeof(Train_Data));
                m_num_trains--;
            }
        }
    }

    // Update Buttons
    if (m_num_trains < MAX_TRAINS)
    {
        ui->ebButton->setEnabled(true);
        ui->wbButton->setEnabled(true);

        for (t=0; t < m_num_trains; t++)
        {
            if (m_trains[t].direction == EASTBOUND &&
                m_trains[t].index <= 2)
            {
                ui->ebButton->setEnabled(false);
            }

            if (m_trains[t].direction == WESTBOUND &&
                m_trains[t].index <= 2)
            {
                ui->wbButton->setEnabled(false);
            }
        }
    }


    updateSignalling();
}
