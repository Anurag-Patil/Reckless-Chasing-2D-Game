#include "mythread.h"
MyThread::MyThread(const qintptr desc, QObject *parent) : QThread(parent) {
    this->socket_descriptor = desc;
    this->socket = new QTcpSocket();

    if (!this->socket->setSocketDescriptor(this->socket_descriptor)) {
        emit this->error(this->socket->error());
        return;
    }
}

void MyThread::run() {
    qDebug() << "Thread Class: Starting thread for: " << this->socket_descriptor;

    connect(socket, SIGNAL(readyRead()), this, SLOT(onRecv()), Qt::DirectConnection);
    connect(socket, SIGNAL(disconnected()), this, SLOT(onDisconnect()), Qt::DirectConnection);

    exec();
}
/**
 * @brief MyThread::onRecv Thsi function is called when the thread receives a data packet
 */
void MyThread::onRecv() {
    // qDebug() << "Thread Class: Data rcvd";
    this->socket->read(reinterpret_cast<char*>(&this->cpkt), sizeof(this->cpkt));

    // qDebug() << "Thread Class: Signal Emited";
    emit this->dataAvailable(this->cpkt);
}
/**
 * @brief MyThread::sendPacket This is used to send packet to the clients
 * @param spkt It is the packet that will be sent
 */
void MyThread::sendPacket(S2CPacket spkt) {
    this->socket->write(reinterpret_cast<char*>(&spkt), sizeof(spkt));
}
/**
 * @brief MyThread::sendInt This is used to send the integer id to the respective client
 */
void MyThread::sendInt(int data) {
    char c = char(data + int('0'));
    qDebug() << "this is id:" << c;
    this->socket->write(&c, sizeof(c));
}
/**
 * @brief MyThread::onDisconnect This function is called when the client disconnects
 */
void MyThread::onDisconnect() {
    qDebug() << "Thread Class: Disconnecting " << this->socket_descriptor;

    this->socket->deleteLater();
    emit this->exiting(this->id);
    exit(0);
}
