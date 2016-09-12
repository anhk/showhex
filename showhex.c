
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

static void show_line(const uint8_t *data, size_t len)
{
    size_t i;
    for (i = 0; i < len; i ++) {
        printf(" %02X", data[i]);
    }
    for (; i < 16; i ++) {
        printf("   ");
    }
    printf("\t");

    for (i = 0; i < len; i ++) {
        if (data[i] >= ' ' && data[i] < 128) {
            printf("%c", data[i]);
        } else {
            printf(".");
        }
    }
    printf("\n");
}

static void show_hex(const void *data, size_t len)
{
    const uint8_t *t = (uint8_t*)data;
    while (len > 16) {
        show_line(t, 16);
        t += 16;
        len -= 16;
    }
    show_line(t, len);
}

int main(int argc, char **argv)
{
    if (argc < 2) {
        printf("Bad Argument.\n");
        return -1;
    }

    //printf("%s\n", argv[1]);

    char buff[BUFSIZ];
    int ret;

    int fd = open(argv[1], O_RDONLY);
    if (fd < 0) {
        perror("open:");
        return -1;
    }
    while ((ret = read(fd, buff, BUFSIZ)) > 0) {
        show_hex(buff, ret);
    }

    close(fd);


    return 0;
}


