#include "c2spacket.h"

C2SPacket::C2SPacket() {}
/**
 * @brief C2SPacket::C2SPacket
 * @param x It is the horizontal coordinate
 * @param y It is the vertical coordinate
 */
C2SPacket::C2SPacket(const qreal x, const qreal y) {
    this->x = x;
    this->y = y;
}

C2SPacket::~C2SPacket() {}
