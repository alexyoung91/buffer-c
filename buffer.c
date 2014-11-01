#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "buffer.h"

void buffer_init(buffer_t* buffer) {
	buffer->capacity = BUFFER_BLOCK_SIZE;
	buffer->size = 0;

	buffer->raw = (uint8_t*)calloc(sizeof (uint8_t), buffer->capacity);
}

void buffer_init_with_capacity(buffer_t* buffer, uint32_t capacity) {
	buffer->capacity = capacity;
	buffer->size = 0;

	buffer->raw = (uint8_t*)calloc(sizeof (uint8_t), buffer->capacity);
}

void buffer_free(buffer_t *buffer) {
	buffer_clean(buffer);
	free(buffer);
}

void buffer_clean(buffer_t *buffer) {
	free(buffer->raw);
}

uint32_t buffer_get_block_capacity(uint32_t capacity) {
	int block_size = BUFFER_BLOCK_SIZE;
	return ((uint32_t)((capacity + block_size - 1.0) / block_size)) * block_size;
}

int buffer_resize(buffer_t* buffer, uint32_t capacity) {
	capacity = buffer_get_block_capacity(capacity);

	if (capacity == buffer->capacity)
		return 1;

	uint32_t old_capacity = buffer->capacity;

	uint8_t* raw = realloc(buffer->raw, capacity);
	if (raw == NULL)
		return 0;

	buffer->raw = raw;
	buffer->capacity = capacity;

	if (buffer->capacity > old_capacity)
		buffer_clear(buffer, old_capacity);

	if (buffer->size > buffer->capacity)
		buffer->size = buffer->capacity;

	return 1;
}

void buffer_clear(buffer_t* buffer, uint32_t index) {
	if (index < buffer->capacity)
		memset(&buffer->raw[index], 0, buffer->capacity - index);

	// &buffer[index] vs buffer + index ??

	buffer->size = (buffer->size < index) ? buffer->size : index;
}

void buffer_write_uint8(buffer_t* buffer, uint8_t value) {
	if (buffer->capacity < buffer->size + sizeof(value))
		buffer_resize(buffer, buffer->size + sizeof(value));

	memcpy(&buffer->raw[buffer->size], (uint8_t*)&value, sizeof (value));
    buffer->size += sizeof (value);
}

void buffer_write_buffer(buffer_t *dst, buffer_t *src) {
	if (dst->capacity < dst->size + src->size)
		buffer_resize(dst, dst->size + src->size);

	memcpy(&dst->raw[dst->size], &src->raw, src->size);
	dst->size += src->size;
}

void buffer_write_raw(buffer_t *buffer, void *data, uint32_t size) {
	if (buffer->capacity < buffer->size + size)
		buffer_resize(buffer, buffer->size + size);

	memcpy(&buffer->raw[buffer->size], (uint8_t*)data, size);
	buffer->size += size;
}
