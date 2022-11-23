#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>

/* https://tech.microbit.org/software/spec-i2c-protocol/#i2c-nrf--kl27-configcomms-interface */

#define READ_REQUEST_CMD_ID 0x10
#define READ_RESPONSE_CMD_ID 0x11
#define I2C_VER_PROPERTY_ID 0x02
#define DATA_SIZE_BYTES 0x02

#define KL27_CONFIG_INTERFACE_I2C_ADDR 0x70

static const struct device *i2c;

void main(void)
{
	int err;
	uint32_t num_bytes;
	uint8_t cmd[2] = {READ_REQUEST_CMD_ID, I2C_VER_PROPERTY_ID};
	uint8_t buf[5] = {READ_RESPONSE_CMD_ID, I2C_VER_PROPERTY_ID, DATA_SIZE_BYTES};

  	// Set up the I2C interface
	i2c = device_get_binding("I2C_1");
	if (i2c == NULL) {
		printf("Error acquiring i2c1 interface\n");
		return -1;
	}

	num_bytes = 2;
	err = i2c_write(i2c, cmd, num_bytes, KL27_CONFIG_INTERFACE_I2C_ADDR);
	if (err < 0) {
		printk("Error during I2C write\n");
		return -1;
	}

	do {
		num_bytes = 5;
		err = i2c_read(i2c, buf, num_bytes, KL27_CONFIG_INTERFACE_I2C_ADDR);
		if (err < 0) {
			printk("Error during I2C read\n");
			return -1;
		}
		k_msleep(100);
	} while (buf[2] == 0);

	printk("Cmd response: %02X\n", buf[0]);
	printk("Cmd response: %02X\n", buf[1]);
	printk("Cmd response: %02X\n", buf[2]);
	printk("Cmd response: %02X\n", buf[3]);
	printk("Cmd response: %02X\n", buf[4]);
}
