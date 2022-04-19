#pragma once

#include "i2c-utils.h"
#include <cstring>

class I2CMotorDriver {
    private:
    const I2CUtils &i2c;
    const uint8_t dev_addr;

    // registers
    const uint8_t ping_reg = 0x2C;
    const uint8_t cmd_reg =  0x3C;

    // responses
    const uint8_t ack = 0x31;
    const uint8_t nack = 0x17;

    public:
    I2CMotorDriver(const I2CUtils &i2c, const uint8_t dev_addr)
        : i2c(i2c), dev_addr(dev_addr) {}

    bool isConnected() const {
        uint8_t resp;
        i2c.read_byte(dev_addr, ping_reg, resp);
        return resp == ack;
    }

    bool write(float m1, float m2, float s1, float s2) const {
        int8_t m1_8 = (int8_t)m1;
        int8_t m2_8 = (int8_t)m2;
        int8_t s1_8 = (int8_t)s1;
        int8_t s2_8 = (int8_t)s2;

        uint8_t packet[4];
        std::memcpy(&packet[0], &m1_8, 1);
        std::memcpy(&packet[1], &m2_8, 1);
        std::memcpy(&packet[2], &s1_8, 1);
        std::memcpy(&packet[3], &s2_8, 1);

        i2c.write_block(dev_addr, cmd_reg, 4, packet);
    }
};
