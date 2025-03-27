#include <iostream>
using namespace std;

struct Alamat {
    string jalan;
    string kota;
};

struct Mahasiswa {
    string nama; 
    string nim;
    string prodi;
    float ipk;
    int angkatan;
    Alamat alamat;
};

#define MAX_MAHASISWA 5

int main()
{
    Mahasiswa  mhs[MAX_MAHASISWA];
    int pilihan;
    int panjang = 0;

    do
    {
        cout << "\nMenu Program" << endl;
        cout << "1. Tampilkan Data" << endl;
        cout << "2. Tambah Data" << endl;
        cout << "3. Ubah Data" << endl;
        cout << "4. Hapus Data" << endl;
        cout << "5. Keluar" << endl;
        cout << "Pilihan: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            if (panjang == 0) 
                cout << "Belum ada data" << endl;
            else {
                cout << "\nData Mahasiswa:\n";
                for (int i = 0; i < panjang; i++) {
                    cout << "Index   : " << i + 1 << endl;
                    cout << "Nama    : " << mhs[i].nama << endl;
                    cout << "NIM     : " << mhs[i].nim << endl;
                    cout << "IPK     : " << mhs[i].ipk << endl;
                    cout << "Jalan   : " << mhs[i].alamat.jalan << endl;
                    cout << "Kota    : " << mhs[i].alamat.kota << endl;
                    cout << "------------------------" << endl;
                }
            }
            break;

        case 2:
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
            break;

        case 3:
            if (panjang == 0) {
                cout << "Tidak ada data untuk diubah" << endl;
            } else {
                int index;
                cout << "index data yang ingin diubah (1 - " << panjang << "): ";
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
            break;

        case 4:
            if (panjang == 0) {
                cout << "tidak ada data yang dihapus." << endl;
            } else {
                int index;
                cout << "index data yang ingin dihapus (1 - " << panjang << "): ";
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
