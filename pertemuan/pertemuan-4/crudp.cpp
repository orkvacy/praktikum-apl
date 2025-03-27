#include <iostream>
#include <iomanip>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

struct Alamat {
    string jalan;
    string kota;
};

struct Mahasiswa {
    string nama; 
    string nim;
    float ipk;
    Alamat alamat;
};

#define MAX_MAHASISWA 5
Mahasiswa mhs[MAX_MAHASISWA];
int panjang = 0;

void tampilkanData() {
    if (panjang == 0) {
        cout << "Belum ada data" << endl;
    } else {
        Table table;
        table.add_row({"No", "Nama", "NIM", "IPK", "Jalan", "Kota"});
        
        for (int i = 0; i < panjang; i++) {
            table.add_row({to_string(i + 1), mhs[i].nama, mhs[i].nim, to_string(mhs[i].ipk), mhs[i].alamat.jalan, mhs[i].alamat.kota});
        }
        
        table.format()
            .font_style({FontStyle::bold})
            .border_color(Color::yellow);
        
        cout << table << endl;
    }
}

void tambahData() {
    if (panjang < MAX_MAHASISWA) {
        cout << "Masukkan Nama: ";
        getline(cin, mhs[panjang].nama);
        cout << "Masukkan NIM: ";
        getline(cin, mhs[panjang].nim);
        cout << "Masukkan IPK: ";
        cin >> mhs[panjang].ipk;
        cin.ignore();
        cout << "Masukkan Jalan: ";
        getline(cin, mhs[panjang].alamat.jalan);
        cout << "Masukkan Kota: ";
        getline(cin, mhs[panjang].alamat.kota);
        panjang++;
        cout << "Data berhasil ditambahkan!\n";
    } else {
        cout << "Data penuh!\n";
    }
}

void ubahData() {
    if (panjang == 0) {
        cout << "Tidak ada data untuk diubah" << endl;
    } else {
        int index;
        cout << "Index data yang ingin diubah (1 - " << panjang << "): ";
        cin >> index;
        cin.ignore();

        if (index > 0 && index <= panjang) {
            index--;
            cout << "Masukkan Nama Baru: ";
            getline(cin, mhs[index].nama);
            cout << "Masukkan NIM Baru: ";
            getline(cin, mhs[index].nim);
            cout << "Masukkan IPK Baru: ";
            cin >> mhs[index].ipk;
            cin.ignore();
            cout << "Masukkan Jalan Baru: ";
            getline(cin, mhs[index].alamat.jalan);
            cout << "Masukkan Kota Baru: ";
            getline(cin, mhs[index].alamat.kota);
            cout << "Data berhasil diubah\n";
        } else {
            cout << "Index tidak valid" << endl;
        }
    }
}

void hapusData() {
    if (panjang == 0) {
        cout << "Tidak ada data yang dihapus." << endl;
    } else {
        int index;
        cout << "Index data yang ingin dihapus (1 - " << panjang << "): ";
        cin >> index;
        cin.ignore();

        if (index > 0 && index <= panjang) {
            index--;
            for (int i = index; i < panjang - 1; i++) {
                mhs[i] = mhs[i + 1];
            }
            panjang--;
            cout << "Data berhasil dihapus!\n";
        } else {
            cout << "Index tidak valid" << endl;
        }
    }
}

void (clear){
    system("pause");
    system("cls");
}

int main() {
    int pilihan;
    do {
        cout << "\nMenu Program" << endl;
        cout << "1. Tampilkan Data" << endl;
        cout << "2. Tambah Data" << endl;
        cout << "3. Ubah Data" << endl;
        cout << "4. Hapus Data" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
        case 1:
            tampilkanData();
            system("pause");
            system("cls");
            break;
        case 2:
            tambahData();
            system("pause");
            system("cls");
            break;
        case 3:
            ubahData();
            system("pause");
            system("cls");
            break;
        case 4:
            hapusData();
            system("pause");
            system("cls");
            break;
        case 5:
            cout << "Program selesai" << endl;
            break;
        default:
            cout << "Pilihan tidak valid" << endl;
            break;
        }
    } while (pilihan != 5);
    return 0;
}