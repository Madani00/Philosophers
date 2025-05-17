#include <stdio.h> // printf
#include <stdlib.h> //malloc
#include <pthread.h>
#include <unistd.h>

void    exit_on_error(int *num, int exit_code)
{
    free(num);
    exit(exit_code);
}

void    *routine_2(void  *arg)
{
    int *num;
    int i;

    num = (int *)arg;
    i = 0;
    while (i < 100000) // data races when we make it bigger nmb 100000
    {
        (*num)++;
        i++;
    }
    return (NULL);
}

void    example_3()
{
    int *num;
    pthread_t   t1;
    pthread_t   t2;

    num = malloc(sizeof(int));
    if (num == NULL)
        exit(1);
    *num = 0;
    if (pthread_create(&t1, NULL, routine_2, num))
        exit_on_error(num, 2);
    if (pthread_create(&t2, NULL, routine_2, num))
        exit_on_error(num, 2);
    if (pthread_join(t1, NULL))
        exit_on_error(num, 3);
    if (pthread_join(t2, NULL))
        exit_on_error(num, 3);
    printf("Num: %d\n", *num);
}

void    *print_hello(void   *arg)
{
    int i;

    i = 0;
    while (i < 100)
    {
        printf("Hello\n");
        i++;
        usleep(10000);
    }
    return (NULL);
}

void    *print_world(void   *arg)
{
    int i;

    i = 0;
    while (i < 100)
    {
        printf("\t\tWorld\n");
        i++;
        usleep(10000);
    }
    return (NULL);
}

void    example_2()
{
    pthread_t   t1;
    pthread_t   t2;

    if (pthread_create(&t1, NULL, print_hello, NULL))
        exit(1);
    if (pthread_create(&t2, NULL, print_world, NULL))
        exit(1);
    if (pthread_join(t1, NULL))
        exit(1);
    if (pthread_join(t2, NULL))
        exit(1);

}

void    example_1()
{
    print_hello(NULL);
    print_world(NULL);
}

void *hi()
{
    printf("hi first im here\n");
    sleep(2);
    printf("last resort\n");
    return (NULL);
}

char buffer[100];

void *write_a() {
    for (int i = 0; i < 50; i++) {
        buffer[i] = 'A';
        //usleep(1000);
    }
    return NULL;
}

void *write_b() {
    for (int i = 0; i < 50; i++) {
        buffer[i] = 'B';
        //usleep(1000);
    }
    return NULL;
}
void same_buffer()
{
    pthread_t thr1;
    pthread_t thr2;

    pthread_create(&thr1, NULL, write_a, NULL);
    pthread_create(&thr2, NULL, write_b, NULL);
    pthread_join(thr1, NULL);
    pthread_join(thr2, NULL);
    printf("%s\n", buffer);

}

int main()
{
    same_buffer();

    return (0);
}
