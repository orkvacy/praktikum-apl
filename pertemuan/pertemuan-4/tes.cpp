#include <iostream>
using namespace std;

// int kali(int a,int b);
// double kali(double a, double b);

int faktorial(int n) {
int hasil = 1;
for (int i = 1; i <= n; i++) {
hasil *= i;
}
return hasil;
}

int main()
{
    // cout << kali(3.2,2.2)  <<endl;
    // cout << kali(3,2)  <<endl;
    cout << "5! = " << faktorial(5) << endl;
    return 0;
}

// int kali(int a, int b)
// {
//     return a*b;
// }

// double kali(double a, double b)
// {
//     return a*b;
// }