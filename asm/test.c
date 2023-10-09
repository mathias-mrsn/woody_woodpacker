#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define N 256   // 2^8

void swap(unsigned char *a, unsigned char *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int KSA(char *key, unsigned char *S) {

    int len = strlen(key);
    int j = 0;

    for(int i = 0; i < N; i++)
        S[i] = i;

    for(int i = 0; i < N; i++) {
        j = (j + S[i] + key[i % len]) % N;

        swap(&S[i], &S[j]);
    }

    return 0;
}

int main ()
{
    unsigned char S[N];

    KSA("This is a password", S);

    for (int i =0; i < N; i++)
        printf("%x - ", S[i]);

    return (0);
}

