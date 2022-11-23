#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define GPIO_PIN_NO  14

void main(void)
{
	int err;
	struct device *gpio;

	gpio = device_get_binding("GPIO_0");
	if (gpio == 0) {
		printk("Error acquiring GPIO 0 interface\n");
	}

	err = gpio_pin_configure(gpio, GPIO_PIN_NO, GPIO_INPUT);
	if (err < 0) {
		printk("failed to configure button gpio: %d", err);
		return;
	}

	while(1) {
		if (gpio_pin_get(gpio, GPIO_PIN_NO))
			printk("Button is released\n");
		else
			printk("Button is pressed\n");
		k_msleep(100);
	}
}
