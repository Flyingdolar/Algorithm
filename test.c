#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char b[20];
    int c;

    c = getchar();
    char* a = fgets(b, 10, stdin);
    printf("%d\n",c);
    printf("%s",b);
    printf("%s",a);
    return 0;
}
