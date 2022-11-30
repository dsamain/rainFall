#include <stdlib.h>

int main(int argc, char **argv)
{
    char buf[33] = { 0 };

    void *file = fopen("/home/user/end/.pass", "r");

    if (file == NULL)
        return 1;

    int ret = atoi(argv[1]);
    buf[ret] = 0;

    fread(ret + 66, 1, 65, file);

    strcmp(buf, argv[1]);
}