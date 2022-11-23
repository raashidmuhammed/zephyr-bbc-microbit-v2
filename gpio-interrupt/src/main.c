#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>

#define GPIO_PIN_NO  14

static struct gpio_callback button_cb_data;

void button_pressed(const struct device *gpio, struct gpio_callback *cb, uint32_t pins)
{
	if (gpio_pin_get(gpio, GPIO_PIN_NO))
		printk("Button is released\n");
	else
		printk("Button is pressed\n");
}

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

	err = gpio_pin_interrupt_configure(gpio, GPIO_PIN_NO, GPIO_INT_EDGE_BOTH);
	if (err < 0) {
		printk("Error %d: failed to configure interrupt\n");
		return;
	}

	gpio_init_callback(&button_cb_data, button_pressed, BIT(GPIO_PIN_NO));
	gpio_add_callback(gpio, &button_cb_data);

	printk("Press the button\n");
	while(1) {}
}
