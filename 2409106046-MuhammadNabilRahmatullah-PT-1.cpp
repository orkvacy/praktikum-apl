#include <iostream>
#include <limits>
#include <cstdlib> //buat clear
#include <conio.h> //ubah tampilan input jadi *
using namespace std;

void clearTerminal(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void clearInput(){
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    string PIN = "6046";

    float saldo = 100;

    int percobaan = 0;
    const int maxPercobaan = 3;

    string inputPIN;
    char ch;
    bool loginSuc = false;

    while (percobaan < maxPercobaan){
        inputPIN = "";
        cout << "Masukkan PIN : ";
        
        while (true) {
            ch = getch();
            if (ch == 13){
                cout << endl;
                break;
            } else if (ch == 8 && inputPIN.length() > 0) {
                inputPIN.pop_back();
                cout << "\b \b";

            } else if (ch >= '0' && ch <= '9' && inputPIN.length() < 4){
                inputPIN.push_back(ch);
                cout << "*";
            }
        }

        if (inputPIN == PIN){
            cout << "Login Berhasil!" << endl;
            loginSuc = true;
            break;
            
        } else {
            percobaan++;
            cout << "Pin Salah! Sisa percobaan " << percobaan << "/" << maxPercobaan << endl;
        }
    }
    if (!loginSuc){
        cout<<"Akun Anda terblokir, silahkan hubungin call center!" << endl;
        return 0;
    }

    int pilihan;

    do{
        clearTerminal();
        cout << "Pilih Transaksi yang Anda Inginkan" << endl;
        cout << "1. Setor Tunai" << endl;
        cout << "2. Cek Saldo" << endl;
        cout << "3. Tarik Tunai" << endl;
        cout << "4. Keluar" << endl;
        cout << "Pilihan Menu (1-4)" << endl;
        if (!(cin >> pilihan)){
            cout << "Input tidak valid! Silahkan Masukkan angka" << endl;
            clearInput();
            system("pause");
            
            continue;
        }
        clearTerminal();

        if (pilihan == 1){ //setor tunai
            float setor;
            cout << "Masukkan Jumlah yang ingin anda setor (IDR)";
            cin >> setor;
            if (cin.fail() || cin.peek() != '\n'){

            
                cout << "Input tidak Valid! Silahkan input angka." << endl;
                clearInput();
                system("pause");
                continue;
            }

            else if (setor > 0) {
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
            if(cin.fail() || cin.peek() != '\n'){
                cout << "Input tidak valid! Silahkan input angka" << endl;
                clearInput();
                system("pause");
                continue;
            }

            if (tarik > 0 && tarik <= saldo) {
                saldo -= tarik;
                cout << "Transaksi berhasil! Saldo anda sekarang : Rp " << saldo << endl;

            } else if (tarik > saldo){
                cout << "Saldo Anda Tidak Cukup!" << endl;
            } else {
                cout << "Jumlah yang ditarik harus lebih dari Rp 0" << endl;
            }

        } else if (pilihan == 4){
            cout << "Terimakasih telah memakai layanan kami!" << endl;
            break;
        } else {
            cout << "Pilihan Tidak Valid!" << endl;
        }
        system("pause");



    } while (pilihan != 4);
    return 0;
}