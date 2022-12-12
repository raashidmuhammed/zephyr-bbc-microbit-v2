#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define GPIO_PIN_NO  2
#define GPIO_SET_HIGH 1
#define GPIO_SET_LOW 0

void main(void)
{
	int err;
	struct device *gpio;

	gpio = device_get_binding("GPIO_0");
	if (gpio == 0) {
		printk("Error acquiring GPIO 0 interface\n");
	}

	err = gpio_pin_configure(gpio, GPIO_PIN_NO, GPIO_OUTPUT);
	if (err < 0) {
		printk("failed to configure button gpio: %d", err);
		return;
	}

	while(1) {
		gpio_pin_set(gpio, GPIO_PIN_NO, GPIO_SET_HIGH);
		k_msleep(500);
		gpio_pin_set(gpio, GPIO_PIN_NO, GPIO_SET_LOW);
		k_msleep(500);
	}
}
