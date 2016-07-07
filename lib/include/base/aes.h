
#ifndef AES_H
#define AES_H

#include <stdint.h>

void key_expansion(uint8_t *key, uint8_t *w, int Nr, int Nk);

void cipher(uint8_t *in, uint8_t *out, uint8_t *w, int Nr);

void inv_cipher(uint8_t *in, uint8_t *out, uint8_t *w, int Nr);

#endif