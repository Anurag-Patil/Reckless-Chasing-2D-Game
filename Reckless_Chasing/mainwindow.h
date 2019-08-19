#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtTest>
#include <QString>
#include <serverscreen.h>
#include <clientscreen.h>

namespace Ui {
class MainWindow;
}
/**
 * @brief The MainWindow class It is the first screen that appears when we run the game. It asks the users for game settings
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QPointF window_size;
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_Play_Button_clicked();

    void on_Developer_Button_clicked();

    void on_Quit_Button_clicked();

    void on_actionPlay_triggered();

    void on_actionDeveloper_triggered();

    void on_actionQuit_triggered();

    void on_actionAbout_Game_triggered();

    void on_actionAbout_Qt_triggered();

    void on_actionHelp_triggered();

    void on_plus_button_clicked();

    void on_minus_button_clicked();

private:
    Ui::MainWindow *ui;
    QObject *screen;

    void show_error();
};

#endif // MAINWINDOW_H
