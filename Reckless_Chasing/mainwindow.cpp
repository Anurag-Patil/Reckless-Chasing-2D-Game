#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QPixmap>
#include <QToolTip>
#include <QToolBar>
#include <QRadioButton>
#include <QVector>
#include <QString>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);

    window_size = QPointF(900, 600);

    this->setFixedSize(window_size.x(), window_size.y());

    QPixmap background(":/images/Background_home.jpg");
    background = background.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->setPalette(palette);

    ui->player_count->display(2);
    ui->Name_lineEdit->setText("Player 1");
    ui->IP_Address_lineEdit->setText("10.42.0.1");
    ui->port_lineEdit->setText("7851");
}

MainWindow::~MainWindow() {
    delete ui;
}
/**
 * @brief MainWindow::on_plus_button_clicked This button is used to increase the number of players
 */
void MainWindow::on_plus_button_clicked() {
    int players = ui->player_count->intValue();

    if (players < 4) {
        ui->player_count->display(players+1);
    }
}
/**
 * @brief MainWindow::on_minus_button_clicked This button is used ot decrease the number of players
 */
void MainWindow::on_minus_button_clicked() {
    int players = ui->player_count->intValue();

    if (players > 2) {
        ui->player_count->display(players-1);
    }
}
/**
 * @brief MainWindow::on_Play_Button_clicked This is used to start the game
 */
void MainWindow::on_Play_Button_clicked() {
    if (ui->Name_lineEdit->text().isEmpty()) {
        this->show_error();
        return;
    }
    if (!ui->Join_Button->isChecked() && !ui->Host_Button->isChecked()) {
        this->show_error();
        return;
    }
    if (ui->IP_Address_lineEdit->text().isEmpty()) {
        this->show_error();
        return;
    }
    if (ui->Host_Button->isChecked() && (ui->player_count->intValue() < 2 || ui->player_count->intValue() > 4)) {
        this->show_error();
        return;
    }
    if (ui->port_lineEdit->text().isEmpty()){
        this->show_error();
        return;
    }


    if (ui->Host_Button->isChecked()) {
        quint16 port = quint16(ui->port_lineEdit->text().toInt());
        QString ip = ui->IP_Address_lineEdit->text();

        this->screen = new ServerScreen(ip, port, ui->player_count->intValue(), this);
        static_cast<ServerScreen*>(this->screen)->show();
        this->hide();
    }
    else if (ui->Join_Button->isChecked()) {
        quint16 port = quint16(ui->port_lineEdit->text().toInt());
        QString ip = ui->IP_Address_lineEdit->text();
        this->screen = new ClientScreen(ip, port, ui->player_count->intValue(), this);
        static_cast<ClientScreen*>(this->screen)->show();
        this->hide();
    }
}
/**
 * @brief MainWindow::show_error This is used to display error message if configuration is incorrect
 */
void MainWindow::show_error() {
    QVector<QString> Unfilled;

    if ((!(ui->Join_Button->isChecked())) && (!(ui->Host_Button->isChecked()))) {
        Unfilled.push_back("Host or Join");
    }
    if (ui->Name_lineEdit->text().isEmpty()) {
        Unfilled.push_back("Name");
    }
    if (ui->IP_Address_lineEdit->text().isEmpty()) {
        Unfilled.push_back("IP Address");
    }
    if (ui->port_lineEdit->text().isEmpty()){
        Unfilled.push_back("Port id");
    }


    QString temp = "Please fill up these information to continue :";

    for (int i = 0; i < Unfilled.size(); i++) {
        temp = temp + "\n" + char(i+49) + ".\t" +Unfilled[i];
    }

    QMessageBox::critical(this,"Error",temp);
    return;
}
/**
 * @brief MainWindow::on_Developer_Button_clicked Display the team members who developed the game
 */
void MainWindow::on_Developer_Button_clicked()
{
    QMessageBox::information(this,"Developer's","TEAM NO. : 14\n1.Deep Diwani\n2.Dheeraj Agarwalla\n3.Gajanan Shetkar\n4.Anurag Patil");
}
/**
 * @brief MainWindow::on_actionPlay_triggered It is used to start the game
 */
void MainWindow::on_actionPlay_triggered()
{
    on_Play_Button_clicked();
}
/**
 * @brief MainWindow::on_actionDeveloper_triggered It displays the names of the game developers
 */
void MainWindow::on_actionDeveloper_triggered()
{
    on_Developer_Button_clicked();
}
/**
 * @brief MainWindow::on_actionQuit_triggered It is used to quit the game
 */
void MainWindow::on_actionQuit_triggered()
{
    on_Quit_Button_clicked();
}
/**
 * @brief MainWindow::on_actionAbout_Qt_triggered Displays information about the qt software
 */
void MainWindow::on_actionAbout_Qt_triggered()
{
    QMessageBox::aboutQt(this,"About Qt");
}
/**
 * @brief MainWindow::on_Quit_Button_clicked It is used to quit the game
 */
void MainWindow::on_Quit_Button_clicked()
{
    QMessageBox::StandardButton reply = QMessageBox::question(this,"Quit","Do you want to quit ?");
    if( reply == QMessageBox::Yes)
    {
        QApplication::quit();
    }
}
/**
 * @brief MainWindow::on_actionAbout_Game_triggered Displays information about the game
 */
void MainWindow::on_actionAbout_Game_triggered()
{
    QMessageBox::information(this,"GAME PLAY","  PLAYERS : \n\tCHASER  (Police)\n"
                                              "\tMULTIPLE RUNNERS  (Chors)\n\n"
                             "CHASER : \nThe task of the Chaser is to catch the Runners."
                                              "He can move around the playarena and if he comes in contact with "
                                              " any Runner then the runner is caught."
                                              "\n\n"
                             "RUNNER : \nThe Runner has to run around the arena Recklessly to avoid contact with the Chaser."
                                              "If the Chaser touches him then he is caught.\n\tGAME OVER (Not Quite Yet)"
                                              "\n\n"
                                              "\n\t***TWIST***\n"
                             "After getting caught the Runners are combined with the Chaser "
                                              "and now they have to catch the remaining Runners."
                                              "Now they have to play as one.\n"
                                              "The game ends when all Runners are caught."

                             );

}
/**
 * @brief MainWindow::on_actionHelp_triggered This is e to display the how to play the game instructions
 */
void MainWindow::on_actionHelp_triggered()
{
    QMessageBox::information(this,"INSTRUCTIONS","KEYS:\n\n"
                                                 "Mouse Pointer ->"
                                                 " \n\tThe Mouse pointer *points* in the direction\n "
                                                 "\tthe player will move (doesn't cause movement).\n"
                                                 "\tThe pointer can be moved freely to point in any \n\tdirection."
                                                 "\n\n"
                                                 "    'W' ->"
                                                 "\n\t This will move the player in the direction of the "
                                                 "\n\tpointer."
                                                 "\n\n"
                                                 "    'S' ->"
                                                 "\n\tThis key will move the player in the opposite "
                                                 "\n\tdirection of the mouse pointer."
                                                 "\n\n"
                                                 "!Warning : Don't hold both (W & S) keys simultaneously.");

}
