#include <zephyr/kernel.h>
#include <stdio.h>

#define GPIO_P0_BASE_ADDR 0x50000000
#define GPIO_P0_IN_REG (GPIO_P0_BASE_ADDR + 0x510)
#define GPIO_P0_PIN_CNF_14 (GPIO_P0_BASE_ADDR + 0x738)
#define PIN_DIR_BIT 0
#define INPUT_CONNECT_BIT 1
#define PIN_SENSE_BIT 16

#define GPIO_PIN_NO  14
#define GPIO_P0_14 (1 << GPIO_PIN_NO)

volatile uint32_t *button_val = (uint32_t *)GPIO_P0_IN_REG;
volatile uint32_t *pin_cfg = (uint32_t *)GPIO_P0_PIN_CNF_14;

void main(void)
{
	uint32_t pin_val;
	/* Configure Button as input */
	*pin_cfg &= ~((1 << PIN_DIR_BIT) | (1 << INPUT_CONNECT_BIT) | (3 << PIN_SENSE_BIT));


	while(1) {
		pin_val = *button_val & GPIO_P0_14;

		if (pin_val == 0)
			printf("Button is pressed\n");

		if ((pin_val >> GPIO_PIN_NO) == 1)
			printf("Button is released\n");

		k_msleep(100);
	}
}
