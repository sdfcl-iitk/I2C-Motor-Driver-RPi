# I2C-Motor-Driver-RPi

Raspberry Pi C++ motor driver for the I2C Motor Controller https://github.com/sdfcl-iitk/I2C-Motor-Controller

## Reference

- `I2CMotorDriver(i2c, dev_addr)` - Initializes the driver with an i2c bus reference and device address
- `isConnected()` - Returns true if the controller is connected
- `write(m1, m2, s1, s2)` - Writes the motor and servo values to the controller
