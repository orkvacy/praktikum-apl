#include <iostream>
using namespace std;

int main() 
{
string PIN = "6046"

float saldo = 100;

int percobaan = 0;
const int maxPercobaan = 3;

string pin;
bool loginSuc = false;

while (percobaan < maxPercobaan){
    cout << "Masukkan PIN";
    cin >> inputPIN;

    if(inputPIN == PIN) {
        cout <<"Login Berhasil!" << endl;
        loginSuc = true;
        break;
    } else {
        percobaan++;
        cout <<"PIN salah! Sisa percobaan" << percobaan << "/" << maxPercobaan << endl;

    }
}

if (!loginSuc){
    cout << "Akun anda terblokir! Silahkan hubungi call center" << endl;

}
int pilihan;


}