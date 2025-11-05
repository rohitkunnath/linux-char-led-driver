#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, char **argv) {
    const char *dev = "/dev/virt_led";
    int fd = open(dev, O_RDWR);
    if (fd < 0) { perror("open"); return 1; }
    if (argc == 1) {
        char buf[16];
        int r = read(fd, buf, sizeof(buf)-1);
        if (r>0) { buf[r]=0; printf("LED state: %s", buf); }
    } else {
        write(fd, argv[1], strlen(argv[1]));
        printf("Wrote %s to %s\n", argv[1], dev);
    }
    close(fd);
    return 0;
}
