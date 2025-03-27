#include <iostream>


using namespace std;

struct Mahasiswa{
    string nama; 
    string nim;
    string prodi;
    float ipk;
    int angkatan;
};


int main() {
    Mahasiswa mhs1;

    mhs1.nama = "Dimas";
    mhs1.nim = "2460";
    mhs1.prodi = "informatika";
    mhs1.ipk = 4.1;
    mhs1.angkatan = 2024;

    // mhs2.nama = "Harahap";
    // mhs2.nim = "2465";
    // mhs2.prodi = "SI";
    // mhs2.ipk = 4.2;
    // mhs2.angkatan = 2024;


    cout << "Nama\t:" << mhs1.nama << endl;
    cout << "NIM\t:" << mhs1.nim << endl;
    cout << "Prodi\t:" << mhs1.prodi << endl;
    cout << "IPK\t:" << mhs1.ipk << endl;
    cout << "Angkatan:" << mhs1.angkatan << endl;

    // cout << "Nama\t:" << mhs2.nama << endl;
    // cout << "NIM\t:" << mhs2.nim << endl;
    // cout << "Prodi\t:" << mhs2.prodi << endl;
    // cout << "IPK\t:" << mhs2.ipk << endl;
    // cout << "Angkatan:" << mhs2.angkatan << endl;

    return 0;
}