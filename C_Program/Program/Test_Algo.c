#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#include<math.h>

// void FizzBuzz(int n) {
//     for (int i = 1; i <= n; i++) {
//         if (i % 3 == 0 && i % 5 == 0) {
//             printf("%d FizzBuzz\n", i);
//         } 
//         else if (i % 3 == 0) {
//             printf("%d Fizz\n", i);
//         } 
//         else if (i % 5 == 0) {
//             printf("%d Buzz\n", i);
//         } 
//         else {
//             printf("%d\n", i);
//         }
//     }
// }

int main() {
    int n = 0;
    for (int i = 1; i <= n; i++)
    printf("%d %s%s\n", i, i%3 ? "" : "Fizz", i%5 ? "" : "Buzz");
    return 0;
}