#ifndef C2SPACKET_H
#define C2SPACKET_H

#include <QObject>
/**
 * @brief The C2SPacket class This class will be used for transfering data packets form client to server
 */
class C2SPacket {
public:

    C2SPacket();
    C2SPacket(const qreal x, const qreal y);
    ~C2SPacket();
    int id;
    qreal x, y;
};

static int c2spacket_id = qRegisterMetaType<C2SPacket>("C2SPacket");

#endif // C2SPACKET_H
