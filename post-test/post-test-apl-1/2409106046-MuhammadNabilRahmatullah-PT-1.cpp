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

void tampilkanGaris(int panjang) {
    for (int i = 0; i < panjang; i++) {
        cout << "=";
    }
    cout << endl;
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
        tampilkanGaris(50);
        cout << "            MENU PILIHAN TRANSAKSI          " << endl;
        tampilkanGaris(50);
        cout << endl;
        cout << "  [ 1 ]  |  Setor Tunai                     " << endl;
        cout << "  [ 2 ]  |  Cek Saldo                       " << endl;
        cout << "  [ 3 ]  |  Tarik Tunai                     " << endl;
        cout << "  [ 4 ]  |  Keluar                          " << endl;
        tampilkanGaris(50);
        cout << endl;
        cout << "Silahkan Pilih Menu (1-4): ";
        
        if (!(cin >> pilihan)){
            cout << "Input tidak valid! Silahkan Masukkan angka" << endl;
            clearInput();
            system("pause");
            
            continue;
        }
        clearTerminal();

        if (pilihan == 1){ //setor tunai
            tampilkanGaris(50);
            cout << "                 SETOR TUNAI               " << endl;
            tampilkanGaris(50);
            cout << endl;
            
            float setor;
            cout << "Masukkan Jumlah yang ingin anda setor (IDR): ";
            cin >> setor;
            if (cin.fail() || cin.peek() != '\n'){
                cout << "Input tidak Valid! Silahkan input angka." << endl;
                clearInput();
                system("pause");
                continue;
            }

            else if (setor > 0) {
                saldo += setor;
                cout << endl;
                tampilkanGaris(50);
                cout << "            TRANSAKSI BERHASIL            " << endl;
                cout << "    Saldo Anda Sekarang: Rp " << saldo << endl;
                tampilkanGaris(50);
            } else {
                cout << endl;
                tampilkanGaris(50);
                cout << "  Jumlah yang disetor harus lebih dari Rp 0  " << endl;
                tampilkanGaris(50);
            }

        } else if (pilihan == 2){ // cek saldo
            tampilkanGaris(50);
            cout << "                CEK SALDO                  " << endl;
            tampilkanGaris(50);
            cout << endl;
            cout << "       Saldo Anda Saat Ini: Rp " << saldo << endl;
            cout << endl;
            tampilkanGaris(50);

        } else if (pilihan == 3){ // tarik tunai
            tampilkanGaris(50);
            cout << "               TARIK TUNAI                 " << endl;
            tampilkanGaris(50);
            cout << endl;
            
            float tarik;
            cout << "Masukkan Nominal Uang (Rp): ";
            cin >> tarik;
            if(cin.fail() || cin.peek() != '\n'){
                cout << "Input tidak valid! Silahkan input angka" << endl;
                clearInput();
                system("pause");
                continue;
            }

            if (tarik > 0 && tarik <= saldo) {
                saldo -= tarik;
                cout << endl;
                tampilkanGaris(50);
                cout << "            TRANSAKSI BERHASIL            " << endl;
                cout << "    Saldo Anda Sekarang: Rp " << saldo << endl;
                tampilkanGaris(50);
            } else if (tarik > saldo){
                cout << endl;
                tampilkanGaris(50);
                cout << "          SALDO ANDA TIDAK CUKUP          " << endl;
                tampilkanGaris(50);
            } else {
                cout << endl;
                tampilkanGaris(50);
                cout << "  Jumlah yang ditarik harus lebih dari Rp 0  " << endl;
                tampilkanGaris(50);
            }

        } else if (pilihan == 4){
            tampilkanGaris(50);
            cout << "              TERIMA KASIH                " << endl;
            cout << "      Telah menggunakan layanan kami      " << endl;
            tampilkanGaris(50);
            break;
        } else {
            cout << "Pilihan Tidak Valid!" << endl;
        }
        system("pause");

    } while (pilihan != 4);
    return 0;
}