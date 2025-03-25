#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <tabulate/table.hpp>

using namespace std;
using namespace tabulate;

struct Statistik {
    int win;
    int draw;
    int loss;
    int totalPoin;
};

struct Pemain {
    string nama;
    string id;
    string ranking;
    string negara;
    Statistik statistik;
};

struct User {
    string username;
    string password;
    bool isAdmin;  
};

const int maxPemain = 100;
const int maxUsers = 10;
Pemain dataPemain[maxPemain]; 
User users[maxUsers];
int jumlahPemain = 0;
int jumlahUsers = 1; 

#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define WHITE_BG "\033[47m"    

int main() {
    // Inisialisasi user admin pertama
    users[0].username = "nabil";
    users[0].password = "046";
    users[0].isAdmin = true;  
    
    bool programRunning = true;
    
    while (programRunning) {
        string username, password;
        int percobaan = 0;
        bool loginSukses = false;
        int userIndex = -1;
        
        while (!loginSukses) {
            system("cls");
            
            // Tabel Menu Login
            Table loginTable;
            loginTable.add_row({"SISTEM MANAJEMEN PEMAIN CATUR"});
            loginTable.add_row({"1. Login"});
            loginTable.add_row({"2. Register"});
            loginTable.add_row({"3. Keluar Program"});
            
            loginTable[0].format()
                .font_align(FontAlign::center)
                .font_style({FontStyle::bold})
                .font_color(Color::yellow);
            
            for (size_t i = 1; i < loginTable.size(); ++i) {
                loginTable[i].format()
                    .font_align(FontAlign::center);
            }
            
            cout << loginTable << endl;
            
            cout << "Pilihan: ";
            
            int pilihanAuth;
            cin >> pilihanAuth;
            
            if (pilihanAuth == 1) {
                percobaan = 0;
                while (percobaan < 3 && !loginSukses) {
                    cout << "Masukkan Username: ";
                    cin >> username;
                    cout << "Masukkan Password: ";
                    
                    password = "";
                    char ch;
                    while ((ch = _getch()) != 13) { 
                        if (ch == 8) {  
                            if (!password.empty()) {
                                cout << "\b \b";  
                                password.pop_back();
                            }
                        } else {
                            cout << '*';
                            password += ch;
                        }
                    }
                    cout << endl;
                    
                    for (int i = 0; i < jumlahUsers; i++) {
                        if (username == users[i].username && password == users[i].password) {
                            loginSukses = true;
                            userIndex = i;
                            break;
                        }
                    }
                    
                    if (!loginSukses) {
                        percobaan++;
                        cout << "Login gagal! Percobaan ke-" << percobaan << "\n";
                        if (percobaan >= 3) {
                            cout << "Kesempatan habis, kembali ke menu awal.";
                            system("pause");
                            break;
                        }
                    }
                }
                
                if (loginSukses) break;  
            } 
            else if (pilihanAuth == 2) {
                if (jumlahUsers < maxUsers) {
                    string newUsername, newPassword;
                    bool usernameValid = false;
                    
                    while (!usernameValid) {
                        cout << "Masukkan Username baru: ";
                        cin >> newUsername;
                        
                        usernameValid = true;
                        for (int i = 0; i < jumlahUsers; i++) {
                            if (users[i].username == newUsername) {
                                usernameValid = false;
                                cout << "Username sudah digunakan. Coba yang lain.";
                                break;
                            }
                        }
                    }
                    
                    cout << "Masukkan Password baru: ";
                    newPassword = "";
                    char ch;
                    while ((ch = _getch()) != 13) { 
                        if (ch == 8) {  
                            if (!newPassword.empty()) {
                                cout << "\b \b";  
                                newPassword.pop_back();
                            }
                        } else {
                            cout << '*';
                            newPassword += ch;
                        }
                    }
                    cout << endl;
                    
                    users[jumlahUsers].username = newUsername;
                    users[jumlahUsers].password = newPassword;
                    users[jumlahUsers].isAdmin = false;
                    jumlahUsers++;
                    
                    cout << "Registrasi berhasil! Silahkan login.";
                    system("pause");
                } else {
                    cout << "Jumlah user maksimum telah tercapai.";
                    system("pause");
                }
            }
            else if (pilihanAuth == 3) {
                Table exitTable;
                exitTable.format().corner("*")
                .font_style({FontStyle::bold})
                .corner_color(Color::magenta)
                .border_color(Color::magenta);
            exitTable.add_row({"Terima Kasih"});
            exitTable.add_row({"Sampai Jumpa Lagi"});
            
            for (auto& row : exitTable) {
                row.format()
                    .font_color(Color::green)
                    .font_style({FontStyle::bold})
                    .font_align(FontAlign::center);
            }
            
            cout << exitTable << endl;
            return 0;
            }
            else {
                cout << "Pilihan tidak valid.";
                system("pause");
            }
        }

        int highlightArr = 0; 
        int pilihan = 0;         
        
        bool exitToLogin = false;
        
        while (!exitToLogin) {
            system("cls"); 
            
            cout << "Selamat datang, " << username << "!\n\n";
            
            Table mainMenuTable;
            
            if (users[userIndex].isAdmin) {
                mainMenuTable.add_row({"MENU ADMIN"});
                mainMenuTable.add_row({"1. Tambah Pemain"});
                mainMenuTable.add_row({"2. Tampilkan Pemain"});
                mainMenuTable.add_row({"3. Edit Pemain"});
                mainMenuTable.add_row({"4. Hapus Pemain"});
                mainMenuTable.add_row({"5. Catat Turnamen"});
                mainMenuTable.add_row({"6. Keluar"});
            } else {
                mainMenuTable.add_row({"MENU USER"});
                mainMenuTable.add_row({"1. Tampilkan Pemain"});
                mainMenuTable.add_row({"2. Keluar"});
            }
            
            mainMenuTable[0].format()
                .font_align(FontAlign::center)
                .font_style({FontStyle::bold})
                .font_color(Color::yellow);
            
            for (size_t i = 1; i < mainMenuTable.size(); ++i) {
                if (i - 1 == highlightArr) {
                    mainMenuTable[i].format()
                        .background_color(Color::white)
                        .font_color(Color::red)
                        .font_align(FontAlign::center);
                } else {
                    mainMenuTable[i].format()
                        .font_align(FontAlign::center);
                }
            }
            
            cout << mainMenuTable << endl;
            
            cout << "Gunakan panah atas/bawah dan Enter untuk memilih" << endl;
            
            int key = _getch();
            
            if (key == 224) {
                key = _getch();
                
                if (users[userIndex].isAdmin) {
                    switch (key) {
                        case 72: //up arr
                            highlightArr = (highlightArr == 0) ? 5 : highlightArr - 1;
                            break;
                        case 80: //down arr
                            highlightArr = (highlightArr == 5) ? 0 : highlightArr + 1;
                            break;
                    }
                } else {
                    switch (key) {
                        case 72: //up arr
                            highlightArr = (highlightArr == 0) ? 1 : highlightArr - 1;
                            break;
                        case 80: //down arr
                            highlightArr = (highlightArr == 1) ? 0 : highlightArr + 1;
                            break;
                    }
                }
            } else if (key == 13) { //enter
                if (users[userIndex].isAdmin) {
                    pilihan = highlightArr + 1;
                } else {
                    pilihan = (highlightArr == 0) ? 1 : 2;
                }
                
                system("cls");
                
                if (users[userIndex].isAdmin) {
                    if (pilihan == 1) { 
                        if (jumlahPemain < maxPemain) {
                            string inputNama;
                            bool namaValid = false;
                            
                            while (!namaValid) {
                                cout << "Masukkan Nama Pemain (maksimal 11 karakter): ";
                                cin >> inputNama;
                                
                                if (inputNama.length() <= 11) {
                                    namaValid = true;
                                    dataPemain[jumlahPemain].nama = inputNama;
                                } else {
                                    cout << "Error: Nama tidak boleh lebih dari 11 karakter!";
                                }
                            }
                            
                            string inputID;
                            bool idValid = false;
                            
                            while (!idValid) {
                                cout << "Masukkan ID Pemain: ";
                                cin >> inputID;
                                
                                idValid = true;
                                
                                for (int i = 0; i < jumlahPemain; i++) {
                                    if (dataPemain[i].id == inputID) {
                                        idValid = false;
                                        cout << "ID " << inputID << " sudah digunakan!";
                                        break;
                                    }
                                }
                                
                                if (idValid) {
                                    dataPemain[jumlahPemain].id = inputID;
                                }
                            }
                            
                            dataPemain[jumlahPemain].ranking = to_string(jumlahPemain + 1);
                            
                            cout << "Masukkan Negara: ";
                            cin >> dataPemain[jumlahPemain].negara;
                            
                            dataPemain[jumlahPemain].statistik.win = 0;
                            dataPemain[jumlahPemain].statistik.draw = 0;
                            dataPemain[jumlahPemain].statistik.loss = 0;
                            dataPemain[jumlahPemain].statistik.totalPoin = 0;
                            
                            jumlahPemain++;
                            cout << "Pemain berhasil ditambahkan!";
                            system("pause"); 
                        } else {
                            cout << "Database penuh!";
                            system("pause"); 
                        }
                    } 
                    else if (pilihan == 2) { 
                        Table table;
                        
                        for (int i = 0; i < jumlahPemain; i++) {
                            dataPemain[i].statistik.totalPoin = 
                                (dataPemain[i].statistik.win * 3) + 
                                (dataPemain[i].statistik.draw * 1) - 
                                (dataPemain[i].statistik.loss * 2);
                        }
                        for (int i = 0; i < jumlahPemain - 1; i++) {
                            for (int j = 0; j < jumlahPemain - i - 1; j++) {
                                if (dataPemain[j].statistik.totalPoin < dataPemain[j + 1].statistik.totalPoin) {
                                    Pemain temp = dataPemain[j];
                                    dataPemain[j] = dataPemain[j + 1];
                                    dataPemain[j + 1] = temp;
                                }
                            }
                        }
                        for (int i = 0; i < jumlahPemain; i++) {
                            dataPemain[i].ranking = to_string(i + 1);
                        }

                        table.add_row({"No", "Nama", "ID", "Ranking", "Negara", "W", "D", "L", "Poin"});
                        table[0].format()
                            .font_align(FontAlign::center)
                            .font_style({FontStyle::bold})
                            .font_color(Color::yellow);

                        for (int i = 0; i < jumlahPemain; i++) {
                            table.add_row({
                                to_string(i + 1),
                                dataPemain[i].nama,
                                dataPemain[i].id,
                                dataPemain[i].ranking,
                                dataPemain[i].negara,
                                to_string(dataPemain[i].statistik.win),
                                to_string(dataPemain[i].statistik.draw),
                                to_string(dataPemain[i].statistik.loss),
                                to_string(dataPemain[i].statistik.totalPoin)
                            });
                        }

                        for (size_t i = 1; i < table.size(); ++i) {
                            table[i][0].format().font_align(FontAlign::center).font_color(Color::cyan).font_style({FontStyle::bold});
                            table[i][2].format().font_align(FontAlign::center);
                            table[i][3].format().font_align(FontAlign::center);
                            table[i][5].format().font_align(FontAlign::center);
                            table[i][6].format().font_align(FontAlign::center);
                            table[i][7].format().font_align(FontAlign::center);
                            table[i][8].format().font_align(FontAlign::center);
                        }

                        cout << table << endl;
                        system("pause");
                    } 
                    else if (pilihan == 3) {
                        string id;
                        cout << "Masukkan ID pemain yang ingin diedit: ";
                        cin >> id;
                        cin.ignore();
                        
                        bool ditemukan = false;
                        for (int i = 0; i < jumlahPemain; i++) {
                            if (dataPemain[i].id == id) {
                                string newNama, newNegara;
                                
                                cout << "Data saat ini: " << endl;
                                cout << "Nama: " << dataPemain[i].nama << endl;
                                cout << "Ranking: " << dataPemain[i].ranking << " (otomatis diperbarui berdasarkan poin)" << endl;
                                cout << "Negara: " << dataPemain[i].negara << endl << endl;
                                
                                cout << "Masukkan Nama Baru (kosongkan untuk tetap, maks 11 karakter): ";
                                getline(cin, newNama);
                                if (!newNama.empty()) {
                                    if (newNama.length() <= 11) {
                                        dataPemain[i].nama = newNama;
                                    } else {
                                        cout << "Error: Nama tidak boleh lebih dari 11 karakter!";
                                        cout << "Nama tidak diubah.";
                                    }
                                }
                                
                                cout << "Masukkan Negara Baru (kosongkan untuk tetap): ";
                                getline(cin, newNegara);
                                if (!newNegara.empty()) {
                                    dataPemain[i].negara = newNegara;
                                }
                                
                                cout << "Data pemain berhasil diperbarui!";
                                ditemukan = true;
                                break;
                            }
                        }
                        if (!ditemukan) {
                            cout << "Pemain dengan ID tersebut tidak ditemukan.";
                        }
                        system("pause"); 
                    } 
                    else if (pilihan == 4) { 
                        string id;
                        cout << "Masukkan ID pemain yang ingin dihapus: ";
                        cin >> id;
                        bool ditemukan = false;
                        for (int i = 0; i < jumlahPemain; i++) {
                            if (dataPemain[i].id == id) {
                                for (int j = i; j < jumlahPemain - 1; j++) {
                                    dataPemain[j] = dataPemain[j + 1];
                                }
                                jumlahPemain--;
                                cout << "Pemain berhasil dihapus!";
                                ditemukan = true;
                                break;
                            }
                        }
                        if (!ditemukan) {
                            cout << "Pemain dengan ID tersebut tidak ditemukan.";
                        }
                        system("pause");
                    } 
                    else if (pilihan == 5) { 
                        string id;
                        cout << "Masukkan ID pemain: ";
                        cin >> id;
                        bool ditemukan = false;
                        for (int i = 0; i < jumlahPemain; i++) {
                            if (dataPemain[i].id == id) {
                                string inputWin;
                                bool validWin = false;
                                while (!validWin) {
                                    cout << "Masukkan jumlah kemenangan (hanya angka): ";
                                    cin >> inputWin;
                                    
                                    validWin = true;
                                    for (int j = 0; j < inputWin.length(); j++) {
                                        if (!isdigit(inputWin[j])) {
                                            validWin = false;
                                            cout << "Error: Input harus berupa angka!";
                                            break;
                                        }
                                    }
                                    
                                    if (validWin) {
                                        dataPemain[i].statistik.win = stoi(inputWin);
                                    }
                                }
                                string inputDraw;
                                bool validDraw = false;
                                while (!validDraw) {
                                    cout << "Masukkan jumlah seri (hanya angka): ";
                                    cin >> inputDraw;
                                    
                                    validDraw = true;
                                    for (int j = 0; j < inputDraw.length(); j++) {
                                        if (!isdigit(inputDraw[j])) {
                                            validDraw = false;
                                            cout << "Error: Input harus berupa angka!";
                                            break;
                                        }
                                    }
                                    
                                    if (validDraw) {
                                        dataPemain[i].statistik.draw = stoi(inputDraw);
                                    }
                                }
                                string inputLoss;
                                bool validLoss = false;
                                while (!validLoss) {
                                    cout << "Masukkan jumlah kekalahan (hanya angka): ";
                                    cin >> inputLoss;
                                    
                                    validLoss = true;
                                    for (int j = 0; j < inputLoss.length(); j++) {
                                        if (!isdigit(inputLoss[j])) {
                                            validLoss = false;
                                            cout << "Error: Input harus berupa angka!";
                                            break;
                                        }
                                    }
                                    
                                    if (validLoss) {
                                        dataPemain[i].statistik.loss = stoi(inputLoss);
                                    }
                                }
                                
                                dataPemain[i].statistik.totalPoin = (dataPemain[i].statistik.win * 3) + (dataPemain[i].statistik.draw * 1) - (dataPemain[i].statistik.loss * 2);
                                
                                cout << "Data turnamen diperbarui!\n";
                                cout << "Total poin pemain sekarang: " << dataPemain[i].statistik.totalPoin << "\n";
                                
                                for (int a = 0; a < jumlahPemain - 1; a++) {
                                    for (int b = 0; b < jumlahPemain - a - 1; b++) {
                                        if (dataPemain[b].statistik.totalPoin < dataPemain[b + 1].statistik.totalPoin) {
                                            Pemain temp = dataPemain[b];
                                            dataPemain[b] = dataPemain[b + 1];
                                            dataPemain[b + 1] = temp;
                                        }
                                    }
                                }
                                for (int c = 0; c < jumlahPemain; c++) {
                                    dataPemain[c].ranking = to_string(c + 1);
                                }
                                
                                cout << "Ranking diperbarui berdasarkan poin.";
                                ditemukan = true;
                                break;
                            }
                        }
                        if (!ditemukan) {
                            cout << "Pemain dengan ID tersebut tidak ditemukan.";
                        }
                        system("pause"); 
                    }
                    else if (pilihan == 6) { 
                        exitToLogin = true;
                    }
                } else {
                    if (pilihan == 2) { 
                        exitToLogin = true;
                    } else if (pilihan == 1) { 
                        if (jumlahPemain == 0) {
                            cout << "Belum ada pemain yang terdaftar.";
                            system("pause");
                        } else {
                            Table playerTable;
                            
                            for (int i = 0; i < jumlahPemain; i++) {
                                dataPemain[i].statistik.totalPoin = 
                                    (dataPemain[i].statistik.win * 3) + 
                                    (dataPemain[i].statistik.draw * 1) - 
                                    (dataPemain[i].statistik.loss * 2);
                            }
                            
                            for (int i = 0; i < jumlahPemain - 1; i++) {
                                for (int j = 0; j < jumlahPemain - i - 1; j++) {
                                    if (dataPemain[j].statistik.totalPoin < dataPemain[j + 1].statistik.totalPoin) {
                                        Pemain temp = dataPemain[j];
                                        dataPemain[j] = dataPemain[j + 1];
                                        dataPemain[j + 1] = temp;
                                    }
                                }
                            }
                            
                            for (int i = 0; i < jumlahPemain; i++) {
                                dataPemain[i].ranking = to_string(i + 1);
                            }
                            
                            playerTable.add_row({"No", "Nama", "ID", "Ranking", "Negara", "W", "D", "L", "Poin"});
                            playerTable[0].format()
                                .font_align(FontAlign::center)
                                .font_style({FontStyle::bold})
                                .font_color(Color::yellow);

                            for (int i = 0; i < jumlahPemain; i++) {
                                playerTable.add_row({
                                    to_string(i + 1),
                                    dataPemain[i].nama,
                                    dataPemain[i].id,
                                    dataPemain[i].ranking,
                                    dataPemain[i].negara,
                                    to_string(dataPemain[i].statistik.win),
                                    to_string(dataPemain[i].statistik.draw),
                                    to_string(dataPemain[i].statistik.loss),
                                    to_string(dataPemain[i].statistik.totalPoin)
                                });
                            }

                            for (size_t i = 1; i < playerTable.size(); ++i) {
                                playerTable[i][0].format().font_align(FontAlign::center).font_color(Color::cyan).font_style({FontStyle::bold});
                                playerTable[i][2].format().font_align(FontAlign::center);
                                playerTable[i][3].format().font_align(FontAlign::center);
                                playerTable[i][5].format().font_align(FontAlign::center);
                                playerTable[i][6].format().font_align(FontAlign::center);
                                playerTable[i][7].format().font_align(FontAlign::center);
                                playerTable[i][8].format().font_align(FontAlign::center);
                            }

                            cout << playerTable << endl;
                            system("pause");
                        }
                    }
                }
            }
        }
    }

    cout << "Terima kasih telah menggunakan program!";
    return 0;
}