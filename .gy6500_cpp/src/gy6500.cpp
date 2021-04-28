#include <pigpio.h>

#include "gy6500.h"

Gy6500::Gy6500(int gpio_0, int gpio_1, Gy6500CB_t callback, int timeout){
	mygpio_0 = gpio_0;
	mygpio_1 = gpio_1;

	mycallback = callback;

	mytimeout = timeout
}
