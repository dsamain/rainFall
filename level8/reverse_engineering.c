#include <stdlib.h>

int main()
{
    // ecx = " auth\n"
    // edx = "service\n"
    // eax = "%p, %p\n";

    char *auth = NULL;
    char *service = NULL;

    // [+17 , +50[
    printf("%p, %p", service, auth);
}

/*
    auth service
    service
    service
    login

    thanks do dsamain lmao divine intervention
*/