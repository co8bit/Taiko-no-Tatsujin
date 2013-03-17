#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QListWidget>
#include <Phonon>

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
    void on_playButton_clicked();
    void on_exitButton_clicked();

private:
    Ui::MainWindow *ui;

    void keyPressEvent(QKeyEvent *e);

    Phonon::MediaObject *sound_menu;
};

#endif // MAINWINDOW_H
