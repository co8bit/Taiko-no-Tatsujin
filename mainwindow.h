#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <Phonon>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void menu_sound_finished();
    void on_playButton_clicked();
    void on_exitButton_clicked();
    void on_songsList_itemDoubleClicked();

private:
    Ui::MainWindow *ui;
    QTimer *timer;
    Game *game;

    void start_game(QString music_name);
    void hide_buttons();
    void show_buttons();

    Phonon::MediaObject *sound_menu;
    Phonon::MediaObject *music_song;
};

#endif // MAINWINDOW_H
