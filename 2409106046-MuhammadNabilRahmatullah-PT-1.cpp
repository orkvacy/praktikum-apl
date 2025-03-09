#include <iostream>
using namespace std;

int main() {
    string PIN = "6046";

    float saldo = 100;

    int percobaan = 0;
    const int maxPercobaan = 3;

    string inputPIN;
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
        return 0;
    }
    int pilihan;

    do{
        cout << "Pilih Transaksi yang Anda Inginkan" << endl;
        cout << "1. Setor Tunai" << endl;
        cout << "2. Cek Saldo" << endl;
        cout << "3. Tarik Tunai" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Menu (1-4)" << endl;
        cin >> pilihan;

        if (pilihan == 1){ //setor tunai
            float setor;
            cout << "Masukkan Jumlah yang ingin anda setor (IDR)";
            cin >> setor;

            if (setor > 0) {
                saldo += setor;
                cout << "Transaksi Anda berhasil! Saldo Sekarang " << saldo << endl;
            } else {
                cout << "Jumlah yang disetor harus lebih dari Rp 0" << endl;
            }

        } else if (pilihan == 2){ // cek saldo
            cout << "Saldo Anda Saat Ini : Rp " << saldo << endl;

        } else if (pilihan == 3){ // tarik tunai
            float tarik;
            cout << "Masukkan Nominal Uang (Rp)";
            cin >> tarik;

            if (tarik > 0 && tarik <= saldo) {
                saldo -= tarik;
                cout << "Transaksi berhasil! Saldo anda sekarang : Rp " << saldo << endl;

            } else if (tarik > saldo){
                cout << "Saldo Anda Tidak Cukup!" << endl;
            } else {
                cout << "Jumlah yang ditarik harus lebih dari Rp 0" << endl;
            }

        } else if (pilihan == 4){
            cout << "Terimakasih sudah memakai layanan kami!" << endl;
        } else {
            cout << "Pilihan Tidak Valid!" << endl;
        }

    } while (pilihan != 4);
    return 0;
}