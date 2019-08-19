#include "myserver.h"

MyServer::MyServer(QObject *parent) : QTcpServer(parent) {
    this->setMaxPendingConnections(1);
}
MyServer::~MyServer() {
    QList<QObject*> thread_list = this->children();

    for (QList<QObject*>::iterator itr = thread_list.begin(); itr != thread_list.end(); itr++) {
        reinterpret_cast<QThread*>(*itr)->deleteLater();
    }
}
/**
 * @brief MyServer::start This is used to start the server
 * @param ip This is the ip of the server
 * @param port This is the port number of the server
 */
void MyServer::start(const QString ip, const quint16 port) {
    QHostAddress addr;
    addr.setAddress(ip);
    if (!this->listen(addr, port)) {
        qDebug() << "Server Class: Server could not start";
        exit(1);
    }
    else {
        qDebug() << "Server Class: Server started";
    }
}



void MyServer::stopAccepting() {
    this->pauseAccepting();
}

void MyServer::incomingConnection(const qintptr socket_descriptor) {
    qDebug() << "Server Class: New Connection " << socket_descriptor;

    MyThread *thread = new MyThread(socket_descriptor, this);
    connect(thread, SIGNAL(dataAvailable(C2SPacket)), this->parent(), SLOT(dataRcvd(C2SPacket)), Qt::DirectConnection);
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    emit this->onNewConnection(thread);
    thread->start();
}
