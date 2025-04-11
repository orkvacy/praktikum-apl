#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>
#include <tabulate/table.hpp> //harus taroh file tabulate di incl dulu

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

//rekursif
int hitungTotalPoin(int win, int draw, int loss) {
    if (win == 0 && draw == 0 && loss == 0) {
        return 0;
    }
    
    if (win > 0) {
        return 3 + hitungTotalPoin(win - 1, draw, loss);
    } else if (draw > 0) {
        return 1 + hitungTotalPoin(win, draw - 1, loss);
    } else {
        return -2 + hitungTotalPoin(win, draw, loss - 1);
    }
}

//rekursif
int cariPemainRekursif(string id, int index) {
    if (index >= jumlahPemain) {
        return -1; 
    }
    
    if (dataPemain[index].id == id) {
        return index; 
    }
    
    return cariPemainRekursif(id, index + 1);
}

//overlaod
int cariPemain(string id) {
    return cariPemainRekursif(id, 0);
}

//overload
int cariPemain(string nama, bool byNama) {
    if (!byNama) {
        return cariPemain(nama); 
    }
    
    for (int i = 0; i < jumlahPemain; i++) {
        if (dataPemain[i].nama == nama) {
            return i;
        }
    }
    return -1;
}

//overload
int cariUser(string username) {
    for (int i = 0; i < jumlahUsers; i++) {
        if (users[i].username == username) {
            return i;
        }
    }
    return -1;
}

//prosedur
void sortPemainByPoin() {
    for (int i = 0; i < jumlahPemain; i++) {
        dataPemain[i].statistik.totalPoin = hitungTotalPoin(
            dataPemain[i].statistik.win,
            dataPemain[i].statistik.draw,
            dataPemain[i].statistik.loss
        );
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
}

//fungsi parameter
bool validasiInputAngka(string input) {
    for (int i = 0; i < input.length(); i++) {
        if (!isdigit(input[i])) {
            return false;
        }
    }
    return true;
}

//prosedur
void tampilkanTabelPemain() {
    sortPemainByPoin();
    
    Table table;
    
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
}

//prosedur parameter
void tambahPemain(string nama, string id, string negara) {
    if (jumlahPemain < maxPemain) {
        dataPemain[jumlahPemain].nama = nama;
        dataPemain[jumlahPemain].id = id;
        dataPemain[jumlahPemain].ranking = to_string(jumlahPemain + 1);
        dataPemain[jumlahPemain].negara = negara;
        
        dataPemain[jumlahPemain].statistik.win = 0;
        dataPemain[jumlahPemain].statistik.draw = 0;
        dataPemain[jumlahPemain].statistik.loss = 0;
        dataPemain[jumlahPemain].statistik.totalPoin = 0;
        
        jumlahPemain++;
        cout << "Pemain berhasil ditambahkan!" << endl;
    } else {
        cout << "Database penuh!" << endl;
    }
}

//prosedur
void editPemain(string id, string newNama, string newNegara) {
    int index = cariPemain(id);
    
    if (index != -1) {
        if (!newNama.empty() && newNama.length() <= 11) {
            dataPemain[index].nama = newNama;
        }
        
        if (!newNegara.empty()) {
            dataPemain[index].negara = newNegara;
        }
        
        cout << "Data pemain berhasil diperbarui!" << endl;
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
}

//prosedur
void hapusPemain(string id) {
    int index = cariPemain(id);
    
    if (index != -1) {
        for (int j = index; j < jumlahPemain - 1; j++) {
            dataPemain[j] = dataPemain[j + 1];
        }
        jumlahPemain--;
        cout << "Pemain berhasil dihapus!" << endl;
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
}

//prosedur
void catatTurnamen(string id, int win, int draw, int loss) {
    int index = cariPemain(id);
    
    if (index != -1) {
        dataPemain[index].statistik.win = win;
        dataPemain[index].statistik.draw = draw;
        dataPemain[index].statistik.loss = loss;
        
        dataPemain[index].statistik.totalPoin = hitungTotalPoin(win, draw, loss);
        
        cout << "Data turnamen diperbarui!" << endl;
        cout << "Total poin pemain sekarang: " << dataPemain[index].statistik.totalPoin << endl;
        
        sortPemainByPoin();
        
        cout << "Ranking diperbarui berdasarkan poin." << endl;
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
}

//Fungsi Parameter
bool login(string username, string password, int &userIndex) {
    for (int i = 0; i < jumlahUsers; i++) {
        if (username == users[i].username && password == users[i].password) {
            userIndex = i;
            return true;
        }
    }
    return false;
}

//prosedur
bool registrasi(string username, string password) {
    if (jumlahUsers < maxUsers) {
        for (int i = 0; i < jumlahUsers; i++) {
            if (users[i].username == username) {
                return false;
            }
        }
        
        users[jumlahUsers].username = username;
        users[jumlahUsers].password = password;
        users[jumlahUsers].isAdmin = false;
        jumlahUsers++;
        
        return true;
    }
    return false;
}

//prosedur
void tampilkanMenuAdmin(Table &menuTable) {
    menuTable.add_row({"MENU ADMIN"});
    menuTable.add_row({"1. Tambah Pemain"});
    menuTable.add_row({"2. Tampilkan Pemain"});
    menuTable.add_row({"3. Edit Pemain"});
    menuTable.add_row({"4. Hapus Pemain"});
    menuTable.add_row({"5. Catat Turnamen"});
    menuTable.add_row({"6. Keluar"});
    
    menuTable[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);
}

//prosedur
void tampilkanMenuUser(Table &menuTable) {
    menuTable.add_row({"MENU USER"});
    menuTable.add_row({"1. Tampilkan Pemain"});
    menuTable.add_row({"2. Keluar"});
    
    menuTable[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);
}

//prosedur
void tampilkanMenuLogin(Table &loginTable) {
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
}

//prosedur
void tampilkanTabelExit(Table &exitTable) {
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
}

void prosesMenuTambahPemain() {
    if (jumlahPemain < maxPemain) {
        string inputNama;
        bool namaValid = false;
        
        while (!namaValid) {
            cout << "Masukkan Nama Pemain (maksimal 11 karakter): ";
            cin >> inputNama;
            
            if (inputNama.length() <= 11) {
                namaValid = true;
            } else {
                cout << "Error: Nama tidak boleh lebih dari 11 karakter!" << endl;
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
                    cout << "ID " << inputID << " sudah digunakan!" << endl;
                    break;
                }
            }
        }
        
        string inputNegara;
        cout << "Masukkan Negara: ";
        cin >> inputNegara;
        
        tambahPemain(inputNama, inputID, inputNegara);
    } else {
        cout << "Database penuh!" << endl;
    }
    system("pause");
}

void prosesMenuEditPemain() {
    string id;
    cout << "Masukkan ID pemain yang ingin diedit: ";
    cin >> id;
    cin.ignore();
    
    int index = cariPemain(id);
    
    if (index != -1) {
        string newNama, newNegara;
        
        cout << "Data saat ini: " << endl;
        cout << "Nama: " << dataPemain[index].nama << endl;
        cout << "Ranking: " << dataPemain[index].ranking << " (otomatis diperbarui berdasarkan poin)" << endl;
        cout << "Negara: " << dataPemain[index].negara << endl << endl;
        
        cout << "Masukkan Nama Baru (kosongkan untuk tetap, maks 11 karakter): ";
        getline(cin, newNama);
        
        cout << "Masukkan Negara Baru (kosongkan untuk tetap): ";
        getline(cin, newNegara);
        
        editPemain(id, newNama, newNegara);
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
    system("pause");
}

void prosesMenuHapusPemain() {
    string id;
    cout << "Masukkan ID pemain yang ingin dihapus: ";
    cin >> id;
    
    hapusPemain(id);
    system("pause");
}

void prosesMenuCatatTurnamen() {
    string id;
    cout << "Masukkan ID pemain: ";
    cin >> id;
    
    int indexPemain = cariPemain(id);
    
    if (indexPemain != -1) {
        string inputWin;
        bool validWin = false;
        int win = 0;
        
        while (!validWin) {
            cout << "Masukkan jumlah kemenangan (hanya angka): ";
            cin >> inputWin;
            
            validWin = validasiInputAngka(inputWin);
            
            if (validWin) {
                win = stoi(inputWin);
            } else {
                cout << "Error: Input harus berupa angka!" << endl;
            }
        }
        
        string inputDraw;
        bool validDraw = false;
        int draw = 0;
        
        while (!validDraw) {
            cout << "Masukkan jumlah seri (hanya angka): ";
            cin >> inputDraw;
            
            validDraw = validasiInputAngka(inputDraw);
            
            if (validDraw) {
                draw = stoi(inputDraw);
            } else {
                cout << "Error: Input harus berupa angka!" << endl;
            }
        }
        
        string inputLoss;
        bool validLoss = false;
        int loss = 0;
        
        while (!validLoss) {
            cout << "Masukkan jumlah kekalahan (hanya angka): ";
            cin >> inputLoss;
            
            validLoss = validasiInputAngka(inputLoss);
            
            if (validLoss) {
                loss = stoi(inputLoss);
            } else {
                cout << "Error: Input harus berupa angka!" << endl;
            }
        }
        
        catatTurnamen(id, win, draw, loss);
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
    system("pause");
}

int main() {
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
            Table loginTable;
            tampilkanMenuLogin(loginTable);
            
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
                    
                    loginSukses = login(username, password, userIndex);
                    
                    if (!loginSukses) {
                        percobaan++;
                        cout << "Login gagal! Percobaan ke-" << percobaan << "\n";
                        if (percobaan >= 3) {
                            cout << "Kesempatan habis.";
                            abort();
                        }
                    }
                }
                
                if (loginSukses) break;  
            } 
            else if (pilihanAuth == 2) {
                string newUsername, newPassword;
                bool usernameValid = false;
                
                while (!usernameValid) {
                    cout << "Masukkan Username baru: ";
                    cin >> newUsername;
                    
                    usernameValid = true;
                    for (int i = 0; i < jumlahUsers; i++) {
                        if (users[i].username == newUsername) {
                            usernameValid = false;
                            cout << "Username sudah digunakan. Coba yang lain.\n";
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
                
                bool registerSuccess = registrasi(newUsername, newPassword);
                
                if (registerSuccess) {
                    cout << "Registrasi berhasil! Silahkan login." << endl;
                } else {
                    cout << "Registrasi gagal. Jumlah user maksimum telah tercapai." << endl;
                }
                system("pause");
            }
            else if (pilihanAuth == 3) {
                Table exitTable;
                tampilkanTabelExit(exitTable);
                cout << exitTable << endl;
                return 0;
            }
            else {
                cout << "Pilihan tidak valid." << endl;
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
                tampilkanMenuAdmin(mainMenuTable);
            } else {
                tampilkanMenuUser(mainMenuTable);
            }
            
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
                    switch (pilihan) {
                        case 1: 
                            prosesMenuTambahPemain();
                            break;
                        case 2: 
                            tampilkanTabelPemain();
                            system("pause");
                            break;
                        case 3: 
                            prosesMenuEditPemain();
                            break;
                        case 4: 
                            prosesMenuHapusPemain();
                            break;
                        case 5: 
                            prosesMenuCatatTurnamen();
                            break;
                        case 6: 
                            exitToLogin = true;
                            break;
                    }
                } else {
                    if (pilihan == 1) { 
                        if (jumlahPemain == 0) {
                            cout << "Belum ada pemain yang terdaftar." << endl;
                            system("pause");
                        } else {
                            tampilkanTabelPemain();
                            system("pause");
                        }
                    } else if (pilihan == 2) {
                        exitToLogin = true;
                    }
                }
            }
        }
    }

    cout << "Terima kasih telah menggunakan program!" << endl;
    return 0;
}