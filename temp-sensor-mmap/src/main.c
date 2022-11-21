#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>

#define TEMP_START_REG_ADDR 0x4000C000
#define TEMP_VALUE_REG_ADDR 0x4000C508
#define START_TEMP_MEASUREMENT 0x00000001

void main(void)
{
	while (1) {
		*(volatile uint32_t *)TEMP_START_REG_ADDR = START_TEMP_MEASUREMENT;
		k_msleep(1000);
		printk("Temperature: %u C\n", *(volatile uint32_t *)TEMP_VALUE_REG_ADDR / 4);
		k_msleep(1000);
	}
}
