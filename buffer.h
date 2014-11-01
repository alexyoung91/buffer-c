#ifndef BUFFER_H_
#define BUFFER_H_

#include <stdint.h>

#define		BUFFER_BLOCK_SIZE		4096;

typedef struct {
	uint8_t* raw;
	uint32_t capacity; // buffer capacity (multiple of BLOCK_SIZE)
	uint32_t size; // amount of data in the buffer;
} buffer_t;

void 		buffer_init(buffer_t *buffer);
void 		buffer_init_with_capacity(buffer_t *buffer, uint32_t capacity);
uint32_t 	buffer_get_block_capacity(uint32_t capacity);
int 		buffer_resize(buffer_t *buffer, uint32_t capacity);
void 		buffer_clear(buffer_t *buffer, uint32_t index);

void 		buffer_write_uint8(buffer_t *buffer, uint8_t value);
void 		buffer_write_buffer(buffer_t *dst, buffer_t *src);
void 		buffer_write_raw(buffer_t *buffer, void *data, uint32_t size);

void 		buffer_clean(buffer_t *buffer);
void 		buffer_free(buffer_t *buffer);

#endif

// TODO: use macros instead of tones of buffer functions?
