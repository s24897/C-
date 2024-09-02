#include <iostream>

int gcRec(int a, int b){
    if (b!=0) {
        return gcRec(b, a % b);
    }
    else{return a;}
}
int sumDigits(int n){
    if (n==0) {
        return 0;
    }
    return (n % 10 + sumDigits(n / 10));
}
int numDigits(int n){
    if (n/10==0) {
        return 1;
    }
    return 1 + numDigits(n / 10);
}
void printOddEven(int n){
    if(n<1){return;}

    if (n % 2==0) {
        std::cout << n << " ";
        printOddEven(n - 2);
    }
    else if(n%2==1){
        std::cout << n << " ";
        printOddEven(n - 2);
    }
}
void hailstone(int n){
    std::cout << n << " ";
    if(n==1){return;}
    if(n%2==0){
        hailstone(n/2);
    }
    else if(n%2==1){
        hailstone((n*3)+1);
    }
}


int main() {
    int a = gcRec(12,42);
    std::cout << a << '\n';
    a = gcRec(12,25);
    std::cout << a << '\n';

    a = sumDigits(123);
    std::cout << a << '\n';
    a = sumDigits(971);
    std::cout << a << '\n';

    a = numDigits(12345);
    std::cout << a << '\n';
    a = numDigits(971);
    std::cout << a << '\n';

    printOddEven(15);
    std::cout << '\n';

    printOddEven(14);
    std::cout << '\n';

    hailstone(13);
    std::cout << '\n';
}
