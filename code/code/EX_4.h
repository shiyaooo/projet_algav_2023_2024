#ifndef EX_4_H
#define EX_4_H
uint8_t* leng_initial_hex(uint64_t length);
void pad_message(uint8_t *message, uint64_t length);
void MD5(char* input, uint64_t input_length, uint32_t *hash);
#endif