#include <iostream>
using namespace std;

struct Address{
    string kota;
    string provinsi;
    string negara;
};

int ubahNilai(int &a, int b){
    return a = b;
    }

int main(){

        int a,b;
        a = 5;
        b = 20;
        ubahNilai(a, b);
        cout << a << endl;
    // Address *address2 = &address1;

    // address1.kota = "Samarinda";
    // address1.provinsi = "Kalimantan Timur";
    // address1.negara = "Indonesia";
    

    // address2->kota = "tenggarong";
    // cout<< address1.kota <<endl;

    // cout<< address2->kota <<endl;
    // int a =5 ;
    // int b = 5 ;
    // b= 10;
    // cout << "nilai a : " << a <<endl;
    // cout << "alamat a : " << &a <<endl;
    // cout << "nilai b : " << b <<endl;
}