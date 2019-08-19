#ifndef MYSERVER_H
#define MYSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QDebug>
#include "mythread.h"
/**
 * @brief The MyServer class  A multithreaded socket server which listens and sends game packets
 */
class MyServer : public QTcpServer {
    Q_OBJECT

public:
    explicit MyServer(QObject *parent = nullptr);
    ~MyServer();
    void start(const QString ip, const quint16 port);
    void stopAccepting();

signals:
    void onNewConnection(MyThread *thread);

public slots:

protected:
    void incomingConnection(const qintptr socket_descriptor);
};

#endif // MYSERVER_H
