#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
        char buf[409600];
        int fd = open("shortfile", O_WRONLY|O_CREAT, 0644);
        ssize_t r;

	printf("writing first 3 bytes of 10k file\n");
        r = write(fd, "foo", 3);
        r = ftruncate(fd, 10000);
        fsync(fd);
        close(fd);

	printf("reading O_DIRECT\n");
        fd = open("shortfile", O_RDONLY|O_DIRECT);
        r = read(fd, buf, sizeof(buf));
        close(fd);

        printf("got %d\n", (int)r);
	if (r != 10000)
		return 1;
        return 0;
}
