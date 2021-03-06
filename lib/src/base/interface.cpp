
#ifdef __unix
#include <sys/time.h>
#include <unistd.h>
#endif

#if (defined _WIN32) || (defined _WIN64)
#include <windows.h>
#endif

#include "interface.h"
#include "aes.h"
#include "timer.h"
#include "gametime.h"
#include "md5.h"

static unsigned char key[] = "jiaming";
static const int key_size = sizeof(key);

struct AesInfo
{
	int Nk;
	int Nr;
};

AesInfo InitAesInfo()
{
	AesInfo temp;
	switch (sizeof(key)) {
	default:
	case 16: temp.Nk = 4; temp.Nr = 10; break;
	case 24: temp.Nk = 6; temp.Nr = 12; break;
	case 32: temp.Nk = 8; temp.Nr = 14; break;
	}
	return temp;
}

static const AesInfo AI = InitAesInfo();

void Base::encrypt128(unsigned char *in, unsigned char *out)
{
	uint8_t w[11 * 4 * 4];
	key_expansion(key, w, AI.Nr, AI.Nk);
	cipher(in, out, w, AI.Nr);
}

void Base::decrypt128(unsigned char *in, unsigned char *out)
{
	uint8_t w[11 * 4 * 4];
	key_expansion(key, w, AI.Nr, AI.Nk);
	inv_cipher(in, out, w, AI.Nr);
}

std::string Base::MD5Encrypt(std::string &str)
{
	MD5 md5(str);
	return md5.toString();
}

std::string Base::MD5Encrypt(const unsigned char *input, size_t length)
{
	MD5 md5(input, length);
	return md5.toString();
}

void Time::Sleep(unsigned int ms)
{
#ifdef __unix
	usleep((ms << 10) - (ms << 4) - (ms << 3));		// 经测试，这种方法在linux下执行得更快一些（windows下差不多）
#endif
#if (defined _WIN32) || (defined _WIN64)
	::Sleep(ms);
#endif
}

GameTime * Time::_GameTime()
{
	return new GameTime();
}
