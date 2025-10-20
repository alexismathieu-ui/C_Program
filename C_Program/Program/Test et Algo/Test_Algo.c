#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

//TEST FIZZBUZZ

int main() {
    for (int i = 1; i <= 100; i++) {

         if (i % 3 == 0) {
             printf("%d Fizz\n", i);
         } 
         else if (i % 5 == 0) {
             printf("%d Buzz\n", i);
         } 
         
        printf("%d\n", i);
         
     }
    return 0;
}