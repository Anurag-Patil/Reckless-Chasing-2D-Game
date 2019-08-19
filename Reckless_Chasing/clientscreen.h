#ifndef CLIENTSCREEN_H
#define CLIENTSCREEN_H

#include <QObject>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTime>
#include <QTimer>
#include <QVector>
#include <QPointF>
#include "player.h"
#include "myserver.h"

#define CLIENT_INIT_SPEED 7
#define SPEED_AFTER_COLLISION 12

/**
 * @brief The ClientScreen class This class is used to play the game in the clients who join the server
 */
class ClientScreen : public QObject {
    Q_OBJECT
public:
    ClientScreen(QString ip, const quint16 port, int max_player, QObject *parent = nullptr);
    void show();

private slots:
    void onConnection();
    void idRcvd();
    void initObj();
    void dataRcvd();
    void onDisconnect();
    void sendUpdate();

private:
    int id;
    QGraphicsView *view;
    QGraphicsScene *scene;
    QTcpSocket *socket;
    QTimer timer;
    S2CPacket spkt;
    C2SPacket cpkt;
    QVector<Player*> players;
    QSet<int> pressedKeys;
    int max_players = 2;

    void extractData();
};

#endif // CLIENTSCREEN_H
