#include <stdio.h>
#include <unistd.h>
#include <errno.h>

#define __NR_memcpy 448
#define ARR_LEN 10

int main()
{
    int ret, i;

    int a[] = {1, 2, 3, 777, '5', 'a', 0x0800, -15500, 42, 1337};
    int b[ARR_LEN];

    ret = syscall(__NR_memcpy, a, b, ARR_LEN * sizeof(int)); 
    if (ret == -1)
        printf("error: %d\n", errno);

    for (i = 0; i < ARR_LEN; i++) {
        if (a[i] != b[i])
            printf("error, value %d is different\n", i);
    }

    return 0;
}