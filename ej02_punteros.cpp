#include <stdio.h>

int main () {
    int a = 2, b = 3;
    int *pa = &a, *pb = &b;
    //Imprimiendo
    printf("%d\n", (*pa));
    printf("%d\n", (*pb));
    //Direcciones de memoria
    printf("%p\n", pa);
    printf("%p\n", pb);
  
    (*pa) = (*pb);
    //Imprimiendo
    printf("%d\n", (*pa));
    printf("%d\n", (*pb));

    (*pb) = (*pb)*(*pa);
    printf("%d\n", (*pb));
    return 0;
}