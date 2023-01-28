#include<stdlib.h> // malloc()
#include<stdio.h> // printf()
static int g_grand_total;
static int more(int input) {
     static int accum = 1;
     return input + accum++; }

     int main() {

        int first_val = 10;
        int second_val = 22;
        g_grand_total += first_val;
        { // this is a block

        int third_val = 1;
        g_grand_total += (second_val + third_val);
        }

        int* finals = NULL;
        finals = (int*)malloc(sizeof(int) * 3);  // equivalent to “int[3] finals;” – except that user-allocated memory!

        finals[0] = first_val;
        finals[1] = second_val;
        finals[2] = g_grand_total;

        printf("more(2) = %d\n", more(2));
        printf("more(3) = %d\n", more(3));
        printf("finals = %p\n", finals);
        printf("&finals[0] = %p\n", &finals[0]);
        printf("&finals[1] = %p\n", &finals[1]);
        printf("&finals[2] = %p\n", &finals[2]);
        printf("*finals = %d\n", *finals);
        printf("finals[2] = %d\n", finals[2]);

        free(finals);
        return 0; }