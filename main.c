#include <stdio.h>

#include "buffer.h"

int main() {
	buffer_t buffer;
	buffer_new(&buffer);

	buffer_t buffer2;
	buffer_new_with_capacity(&buffer2, 4096 * 2);

	buffer_resize(&buffer2, 4095);
	printf("%d\n", buffer2.capacity);

	return 0;
}
