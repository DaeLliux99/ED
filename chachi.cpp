#include <stdio.h>

void sumar(int** pa, int* pb) {
    printf("%p\n", (*pa));
    (*pa) = pb;
    printf("%p\n", (pb));
    printf("%p\n", (*pa));
    printf("%p\n", (pa));
}

void sumar2(int* pa) {
    (*pa) = 16;
    printf("%d\n", (*pa));
}

int main() {
    int  a = 32, b = 99;
    int *pa = &a;
    int *pb = &b;
    printf("%d\n", (*pa));
    sumar(&pa, pb);
    printf("%d\n", (*pa));
}