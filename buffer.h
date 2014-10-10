#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

//#define BLOCK_SIZE 4096;
static const uint32_t BLOCK_SIZE = 4096;
// error caused in get block capacity function with define???

typedef struct {
	uint8_t* raw;
	uint32_t capacity; // buffer capacity (multiple of BLOCK_SIZE)
	uint32_t size; // amount of data in the buffer;
} buffer_t;

void buffer_new(buffer_t* buffer);
void buffer_new_with_capacity(buffer_t* buffer, uint32_t capacity);
uint32_t buffer_get_block_capacity(uint32_t capacity);
int buffer_resize(buffer_t* buffer, uint32_t capacity);
void buffer_clear(buffer_t* buffer, uint32_t index);

void buffer_write_uint8(buffer_t* buffer, uint8_t value);

#endif
