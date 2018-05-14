#include <unistd.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
    long int data = -100;
    int mod = 15;

    if(argc >= 2)
        data = strtol(argv[1], NULL, 10);

    if(argc >= 3)
        mod = strtoul(argv[2], NULL, 10);

    printf("sizeof(long):%d\r\n", sizeof(long int));
    printf("data:%d mod:%d,result:%d\r\n", data, mod, data%mod);

    return 0;
}
