#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "buffer.h"

void buffer_new(buffer_t* buffer) {
	buffer->capacity = BLOCK_SIZE;
	buffer->size = 0;

	buffer->raw = (uint8_t*)calloc(sizeof (uint8_t), buffer->capacity);
}

void buffer_new_with_capacity(buffer_t* buffer, uint32_t capacity) {
	buffer->capacity = capacity;
	buffer->size = 0;

	buffer->raw = (uint8_t*)calloc(sizeof (uint8_t), buffer->capacity);
}

uint32_t buffer_get_block_capacity(uint32_t capacity) {
	return ((uint32_t)((capacity + BLOCK_SIZE - 1.0) / BLOCK_SIZE)) * BLOCK_SIZE;
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
		memset(&buffer[index], 0, buffer->capacity - index);

	// &buffer[index] vs buffer + index ??

	buffer->size = (buffer->size < index) ? buffer->size : index;
}

void buffer_write_uint8(buffer_t* buffer, uint8_t value) {
	if (buffer->capacity < buffer->size + sizeof(value))
		buffer_resize(buffer, buffer->size + sizeof(value));

	memcpy(&buffer->raw[buffer->size], (uint8_t*)&value, sizeof (value));
    buffer->size += sizeof (value);
}
