#include <zephyr/kernel.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>

#define GPIO_P0_BASE_ADDR 0x50000000
#define GPIO_P0_OUTPUT_DIR_REG (GPIO_P0_BASE_ADDR + 0x518)
#define GPIO_P0_SET_BIT_REG (GPIO_P0_BASE_ADDR + 0x508)
#define GPIO_P0_CLEAR_BIT_REG (GPIO_P0_BASE_ADDR + 0x50C)
#define GPIO_P0_2 (1 << 2)

#define DELAY_MS 1000

volatile uint32_t *led_dir = (uint32_t *)GPIO_P0_OUTPUT_DIR_REG;
volatile uint32_t *led_set_val = (uint32_t *)GPIO_P0_SET_BIT_REG;
volatile uint32_t *led_clear_val = (uint32_t *)GPIO_P0_CLEAR_BIT_REG;

int main(void)
{
  	/* Configure LED as input */
	*led_dir |= (uint32_t)GPIO_P0_2;

	while (1) {
		*led_set_val |= (uint32_t)GPIO_P0_2;
		k_msleep(DELAY_MS);
		*led_clear_val |= (uint32_t)GPIO_P0_2;
		k_msleep(DELAY_MS);
	}

	return 0;
}
