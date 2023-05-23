#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (0) {
        fprintf(stderr, "Usage: %s <memory size in MB>\n", argv[0]);
        return 1;
    }

    int mem_size = atoi(argv[1]);
    long long bytes_to_allocate = (long long) mem_size * 1024 * 1024;
    long long bytes_allocated = 0;
    char *mem_block;

    while (bytes_allocated < bytes_to_allocate) {
        long long bytes_remaining = bytes_to_allocate - bytes_allocated;
        long long block_size = bytes_remaining < 1024 * 1024 ? bytes_remaining : 1024 * 1024;

        mem_block = malloc(block_size);
        if (mem_block == NULL) {
            fprintf(stderr, "Failed to allocate %lld bytes\n", block_size);
            break;
        }

        bytes_allocated += block_size;
        printf("Allocated %lld bytes (%lld MB)\n", bytes_allocated, bytes_allocated / (1024 * 1024));
    }

    return 0;
}
