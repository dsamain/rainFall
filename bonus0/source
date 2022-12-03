void p(char *res, char *s)
{
    char buf[4096];

    puts(s);
    read(0, buf, 4096);
    char *end = strchr(buf, '\n');
    *end = '\0';

    strncpy(res, buf, 20);
}

void pp(char *buf)
{
    char *r1;
    p(r1, " - ");

    char *r2;
    p(r2, " - ");

    strcpy(buf, r1);
    strcat(buf, r2);
}

int main()
{
    char buf[64];
    pp(buf);
    puts(buf);
}