#ifndef GY6500_H
#define GY6500_H

#include <stdint.h>

typedef void (*Gy6500_t)(int, uint32_t);

class Gy6500{
	private:
		int mygpio_0;
		int mygpio_1;
		int mytimeout;
		int in_code;
		int bits;

		uint32_t num;
		uint32_t code_timeout;

	public:
		Gy6500(int gpio_0, int gpio_1, Gy6500CB_t callback, int timeout=5);

		void _cb(int gpio, int level, uint32_t tick);
		static void _cbEx(int gpio, int level, uint32_t tick, void *user);
		void cancel(void);
};


#endif
