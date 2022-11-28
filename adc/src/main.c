#include <zephyr/zephyr.h>
#include <zephyr/sys/printk.h>
#include <zephyr/device.h>
#include <zephyr/display/mb_display.h>
#include <stdio.h>
#include "adc.h"

void main(void)
{
  	struct mb_display *disp;
	int ret;

	ret = adc_begin();
	if (ret < 0)
	{
		printf("\nError initializing adc.  Error code = %d\n",ret);
		while(1);
	}

	while (1) {
		uint32_t adcvalue = adc_readDigital();
		printf("ADC Digital = %u\n",adcvalue);
		/* The default version of printf does not support floating point numbers so scale up to an integer */
		printf("ADC Voltage (mV) = %d\n",(int)(1000*adc_readVoltage()));

		disp = mb_display_get();
		mb_display_print(disp, MB_DISPLAY_MODE_DEFAULT, 1000, "%u", adcvalue);

		k_msleep(4000);
	}
}
