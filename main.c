#include <stdio.h>

#include "buffer.h"

int main() {
	buffer_t buffer;
	buffer_init(&buffer);

	buffer_t buffer2;
	buffer_init_with_capacity(&buffer2, 4096 * 2);

	buffer_resize(&buffer2, 4095);
	printf("%d\n", buffer2.capacity);

	return 0;
}
