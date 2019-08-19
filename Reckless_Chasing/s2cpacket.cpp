#include "s2cpacket.h"

S2CPacket::S2CPacket() {
    for (int i = 0; i < 4; i++) {
        this->x[i] = 0;
        this->y[i] = 0;
        this->exist[i] = true;
    }
}
