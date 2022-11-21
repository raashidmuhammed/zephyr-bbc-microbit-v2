#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>

#define GPIO_P0_BASE_ADDR 0x50000000
#define GPIO_P0_SET_DIR_REG (GPIO_P0_BASE_ADDR + 0x518)
#define GPIO_P0_SET_BIT_REG (GPIO_P0_BASE_ADDR + 0x508)
#define GPIO_P0_CLEAR_BIT_REG (GPIO_P0_BASE_ADDR + 0x50C)
#define GPIO_P0_2 (1 << 2)

void main(void)
{
	*(volatile uint32_t *)GPIO_P0_SET_DIR_REG = (uint32_t)GPIO_P0_2;
	while (1) {
		*(volatile uint32_t *)GPIO_P0_SET_BIT_REG = (uint32_t)GPIO_P0_2;
		k_msleep(1000);
		*(volatile uint32_t *)GPIO_P0_CLEAR_BIT_REG = (uint32_t)GPIO_P0_2;
		k_msleep(1000);
	}
}
