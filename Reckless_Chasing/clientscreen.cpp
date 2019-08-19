#include "clientscreen.h"
#include <QPixmap>

/**
 * @brief ClientScreen::ClientScreen
 * @param ip It is the ip adress of the host/server
 * @param port It is the port number of the game running on the remote host
 * @param max_players The number of players participating in the game
 * @param parent It is the parent of the clientscreen (main window)
 */
ClientScreen::ClientScreen(QString ip, const quint16 port, int max_players, QObject *parent) : QObject(parent) {
    this->max_players = max_players;

    this->socket = new QTcpSocket(this);
    this->socket->connectToHost(ip, port);

    connect(this->socket, SIGNAL(connected()), this,  SLOT(onConnection()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(idRcvd()));
    connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()));

    this->scene = new QGraphicsScene();
    this->view = new QGraphicsView(scene);
    this->scene->setSceneRect(0, 0, 1050, 700);
    this->view->setWindowTitle("Client");
    this->view->setFixedSize(1050, 700);
    this->view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QPixmap background(":/images/Backgroung_play.jpg");
    background = background.scaled(this->view->size(), Qt::IgnoreAspectRatio);
    scene->setBackgroundBrush(background);
    QPalette palette;
    palette.setBrush(QPalette::Background, background);
    this->scene->setPalette(palette);

    this->socket->waitForConnected();
}

/**
 * @brief ClientScreen::show It will display the screen on which game will be played for the client
 */
void ClientScreen::show() {
    this->view->show();
}

/**
 * @brief ClientScreen::onConnection This is executed when client sucessfully connects to the server
 */
void ClientScreen::onConnection() {
    qDebug() << "Socket connected";
}

/**
 * @brief ClientScreen::idRcvd This is executed when the client receives a packet from the server
 */
void ClientScreen::idRcvd() {
    char c;
    this->socket->read(&c, sizeof(c));
    this->id = int(c-'0');

    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(idRcvd()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(initObj()));
}

/**
 * @brief ClientScreen::initObj This is used to create the players on the client screen
 */
void ClientScreen::initObj() {
    this->socket->read(reinterpret_cast<char*>(&this->spkt), sizeof(this->spkt));

    for (int i = 0; i < this->max_players; i++) {
        this->players.push_back(new Player());
        this->players[i]->initial_pos = QPointF(this->spkt.x[i], this->spkt.y[i]);
        //this->players[i]->setRect(0,0, this->players[i]->radius * 2, this->players[i]->radius * 2);
        if (i == 0) {
            this->players[i]->setPixmap(QPixmap(":/images/police.png"));
        }
        else if(i == this->id) {
            this->players[i]->setPixmap(QPixmap(":/images/chor.png"));
        }
        else {
            this->players[i]->setPixmap(QPixmap(":/images/black_chor.png"));
        }

        this->players[i]->setToolTip("player " + QString::number(i));
        this->players[i]->setX(this->spkt.x[i]);
        this->players[i]->setY(this->spkt.y[i]);

        this->players[i]->new_x = this->spkt.x[i];
        this->players[i]->new_y = this->spkt.y[i];

        this->scene->addItem(this->players[i]);
    }

    this->players[this->id]->setSpeed(CLIENT_INIT_SPEED);
    this->players[this->id]->setFlag(QGraphicsItem::ItemIsFocusable);
    this->players[this->id]->setFocus();

    connect(&this->timer, SIGNAL(timeout()), this, SLOT(sendUpdate()));
    this->timer.start(20);
    disconnect(this->socket, SIGNAL(readyRead()), this, SLOT(initObj()));
    connect(this->socket, SIGNAL(readyRead()), this, SLOT(dataRcvd()));
}

/**
 * @brief ClientScreen::extractData It processes the data received by the server
 */
void ClientScreen::extractData() {
    for (int i = 0; i < this->max_players; i++) {
        this->players[i]->setX(this->spkt.x[i] + this->players[i]->initial_pos.x());
        this->players[i]->setY(this->spkt.y[i] + this->players[i]->initial_pos.y());

        if (this->spkt.exist[i] == false) {
            this->players[i]->hide();

            if (i == this->id) {
                this->players[this->id]->clearFocus();
                this->players[0]->setFlag(QGraphicsItem::ItemIsFocusable);
                this->players[0]->setFocus();
                this->players[0]->setSpeed(SPEED_AFTER_COLLISION);
                this->players[0]->new_x = this->players[0]->x();
                this->players[0]->new_y = this->players[0]->y();
            }
        }
    }
}

/**
 * @brief ClientScreen::dataRcvd It  is called when the client recives data paceket
 */
void ClientScreen::dataRcvd() {
    this->socket->read(reinterpret_cast<char*>(&this->spkt), sizeof(this->spkt));
    this->extractData();
}

/**
 * @brief ClientScreen::onDisconnect This is called when the client disconnects from the server
 */
void ClientScreen::onDisconnect() {
    qDebug() << "Disconnected";
    this->socket->close();
    this->deleteLater();
    exit(0);
}
/**
 * @brief ClientScreen::sendUpdate Th is is used to send the updated position of the players to the server
 */
void ClientScreen::sendUpdate() {
    this->cpkt.id = this->id;

    if (this->spkt.exist[this->id]) {
        this->cpkt.x = this->players[this->id]->new_x;
        this->cpkt.y = this->players[this->id]->new_y;
    }
    else {
        this->cpkt.x = this->players[0]->new_x;
        this->cpkt.y = this->players[0]->new_y;
    }

    this->socket->write(reinterpret_cast<char*>(&(this->cpkt)), sizeof(this->cpkt));
}
