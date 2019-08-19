#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QString>
#include <QThread>
#include <QTcpSocket>
#include "s2cpacket.h"
#include "c2spacket.h"
/**
 * @brief The MyThread class It is used to handle clinent connections using multithreaded paradigms
 */
class MyThread : public QThread {
    Q_OBJECT

public:
    int id;
    explicit MyThread(const qintptr desc, QObject *parent = nullptr);
    void run();
    void sendPacket(S2CPacket pkt);
    void sendInt(int);

signals:
    void error(QTcpSocket::SocketError err);
    void dataAvailable(C2SPacket);
    void exiting(int);

public slots:
    void onRecv();
    void onDisconnect();

private:
    QTcpSocket *socket;
    qintptr socket_descriptor;
    C2SPacket cpkt;
};

#endif // MYTHREAD_H
