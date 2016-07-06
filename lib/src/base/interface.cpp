
#include "interface.h"
#include "aes.h"
#include "timer.h"
#include "gametime.h"

static unsigned char key[] = "jiaming";

void Base::encrypt128(unsigned char *in, unsigned char *out)
{
	uint8_t w[11 * 4 * 4];
	key_expansion(key, w);
	cipher(in, out, w);
}

void Base::decrypt128(unsigned char *in, unsigned char *out)
{
	uint8_t w[11 * 4 * 4];
	key_expansion(key, w);
	inv_cipher(in, out, w);
}

void * Time::NewTimerManager()
{
	return new TimerManager();
}

void * Time::NewGameTime()
{
	return new GameTime();
}
