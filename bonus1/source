#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    /*
    if (atoi(argv[1]) <= 9)
        goto jmp1;

    return 1;

    jmp1: 

    */

   int res;

   if (res = atoi(argv[1]) > 9)
       return 1;

    /*


        mov ecx, res*4;

        mov edx, argv[2]       

    */

   char buf[24]; // idk the actual size

   
   memcpy(buf, argv[2], res*4);

    if (res != 0x574f4c46)
        return 0;

    // same as ["/bin/sh", "sh", NULL], just easier to use execl with arguments rather than creating an array
    execl("/bin/sh", "sh", NULL);
}