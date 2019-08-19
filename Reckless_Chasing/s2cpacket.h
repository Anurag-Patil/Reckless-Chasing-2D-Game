#ifndef S2CPACKET_H
#define S2CPACKET_H

#include <QObject>
/**
 * @brief The S2CPacket class It is the class that is used to send data from server to clients
 */
class S2CPacket {
public:
    S2CPacket();
    /**
     * @brief x It is the  array that stores horizontal coordinates of all the players
     */
    qreal x[4];
    /**
     * @brief y It is the array that stores the vertical coordinates of all the players
     */
    qreal y[4];
    /**
     * @brief exist It is the boolean array that stores whether the player is dead or alive
     */
    bool exist[4];
};

static int s2cpacket_id = qRegisterMetaType<S2CPacket>("S2CPacket");

#endif // S2CPACKET_H
