#pragma once

#include <cstring>

extern "C" {
    #include <stdint.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <linux/i2c-dev.h>
    #include <i2c/smbus.h>
    #include <sys/ioctl.h>
}

class I2CMotorDriver {
    private:
    int i2c_bus;
    uint8_t dev_addr;

    // registers
    const uint8_t ping_reg = 0x2C;
    const uint8_t cmd_reg =  0x3C;

    // responses
    const uint8_t ack = 0x31;
    const uint8_t nack = 0x17;

    public:
    ~I2CMotorDriver() {
        // close the bus
		if (i2c_bus > 0) close(i2c_bus);
    }

    void begin(const uint8_t dev_addr) {
        this->dev_addr = dev_addr;

        i2c_bus = open("/dev/i2c-1", O_RDWR);
        ioctl(i2c_bus, I2C_SLAVE, this->dev_addr);
    }

    bool isConnected() const {
        uint8_t resp = i2c_smbus_read_byte_data(i2c_bus, ping_reg);
        return resp == ack;
    }

    void write(float m1, float m2, float s1, float s2) const {
        int8_t m1_8 = (int8_t)(m1 / 2);
        int8_t m2_8 = (int8_t)(m2 / 2);
        int8_t s1_8 = (int8_t)s1;
        int8_t s2_8 = (int8_t)s2;

        uint8_t packet[4];
        std::memcpy(&packet[0], &m1_8, 1);
        std::memcpy(&packet[1], &m2_8, 1);
        std::memcpy(&packet[2], &s1_8, 1);
        std::memcpy(&packet[3], &s2_8, 1);

        i2c_smbus_write_i2c_block_data(i2c_bus, cmd_reg, 4, packet);
    }
};
