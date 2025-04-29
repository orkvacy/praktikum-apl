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

//rekursif dengan pointer
int hitungTotalPoin(int* win, int* draw, int* loss) {
    if (*win == 0 && *draw == 0 && *loss == 0) {
        return 0;
    }
    
    if (*win > 0) {
        (*win)--;
        int total = 3 + hitungTotalPoin(win, draw, loss);
        (*win)++;
        return total;
    } else if (*draw > 0) {
        (*draw)--;
        int total = 1 + hitungTotalPoin(win, draw, loss);
        (*draw)++;
        return total;
    } else {
        (*loss)--;
        int total = -2 + hitungTotalPoin(win, draw, loss);
        (*loss)++;
        return total;
    }
}

void calculateTotalPoin(Pemain &pemain) {
    int w = pemain.statistik.win;
    int d = pemain.statistik.draw;
    int l = pemain.statistik.loss;
    
    pemain.statistik.totalPoin = hitungTotalPoin(&w, &d, &l);
}

//rekursif dengan pointer
int cariPemainRekursif(string* id, int* index) {
    if (*index >= jumlahPemain) {
        return -1; 
    }
    
    if (dataPemain[*index].id == *id) {
        return *index; 
    }
    
    (*index)++;
    return cariPemainRekursif(id, index);
}

//overlaod dengan pointer
int cariPemain(string* id) {
    int index = 0;
    return cariPemainRekursif(id, &index);
}

//overload dengan pointer
int cariPemain(string* nama, bool* byNama) {
    if (!(*byNama)) {
        return cariPemain(nama); 
    }
    
    for (int i = 0; i < jumlahPemain; i++) {
        if (dataPemain[i].nama == *nama) {
            return i;
        }
    }
    return -1;
}

int cariUser(string* username) {
    for (int i = 0; i < jumlahUsers; i++) {
        if (users[i].username == *username) {
            return i;
        }
    }
    return -1;
}

//merge
void merge(Pemain* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    Pemain* L = new Pemain[n1];
    Pemain* R = new Pemain[n2];
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        //descending
        if (L[i].nama >= R[j].nama) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
    
    delete[] L;
    delete[] R;
}

void mergeSortNama(Pemain* arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortNama(arr, left, mid);
        mergeSortNama(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

//quick
int partition(Pemain* arr, int low, int high) {
    int pivot = arr[high].statistik.win;
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        if (arr[j].statistik.win > pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSortWin(Pemain* arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortWin(arr, low, pi - 1);
        quickSortWin(arr, pi + 1, high);
    }
}

//prosedur dengan pointer
void sortPemainByPoin() {
    for (int i = 0; i < jumlahPemain; i++) {
        Pemain* pemainPtr = &dataPemain[i];
        calculateTotalPoin(*pemainPtr);
    }
    
    for (int i = 0; i < jumlahPemain - 1; i++) {
        for (int j = 0; j < jumlahPemain - i - 1; j++) {
            Pemain* pemainCurrent = &dataPemain[j];
            Pemain* pemainNext = &dataPemain[j + 1];
            
            if (pemainCurrent->statistik.totalPoin < pemainNext->statistik.totalPoin) {
                Pemain temp = *pemainCurrent;
                *pemainCurrent = *pemainNext;
                *pemainNext = temp;
            }
        }
    }
    
    for (int i = 0; i < jumlahPemain; i++) {
        Pemain* pemainPtr = &dataPemain[i];
        pemainPtr->ranking = to_string(i + 1);
    }
}

void sortPemainByNamaDesc() {
    if (jumlahPemain > 1) {
        mergeSortNama(dataPemain, 0, jumlahPemain - 1);
        cout << "Pemain berhasil diurutkan berdasarkan nama secara descending!" << endl;
    } else {
        cout << "Tidak cukup pemain untuk diurutkan." << endl;
    }
}

void sortPemainByWinDesc() {
    if (jumlahPemain > 1) {
        quickSortWin(dataPemain, 0, jumlahPemain - 1);
        cout << "Pemain berhasil diurutkan berdasarkan jumlah kemenangan!" << endl;
    } else {
        cout << "Tidak cukup pemain untuk diurutkan." << endl;
    }
}

//fungsi parameter dengan pointer
bool validasiInputAngka(string* input) {
    for (int i = 0; i < input->length(); i++) {
        if (!isdigit((*input)[i])) {
            return false;
        }
    }
    return true;
}

//prosedur
void tampilkanTabelPemain(bool updateRanking = false) {
    // Hanya sort by poin jika diminta update ranking
    if (updateRanking) {
        sortPemainByPoin();
    }
    
    Table table;
    
    table.add_row({"No", "Nama", "ID", "Ranking", "Negara", "W", "D", "L", "Poin"});
    table[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);

    for (int i = 0; i < jumlahPemain; i++) {
        Pemain* pemainPtr = &dataPemain[i];
        table.add_row({
            to_string(i + 1),
            pemainPtr->nama,
            pemainPtr->id,
            pemainPtr->ranking,
            pemainPtr->negara,
            to_string(pemainPtr->statistik.win),
            to_string(pemainPtr->statistik.draw),
            to_string(pemainPtr->statistik.loss),
            to_string(pemainPtr->statistik.totalPoin)
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

void tambahPemain(string* nama, string* id, string* negara) {
    if (jumlahPemain < maxPemain) {
        Pemain* newPemainPtr = &dataPemain[jumlahPemain];
        
        newPemainPtr->nama = *nama;
        newPemainPtr->id = *id;
        newPemainPtr->ranking = to_string(jumlahPemain + 1);
        newPemainPtr->negara = *negara;
        
        newPemainPtr->statistik.win = 0;
        newPemainPtr->statistik.draw = 0;
        newPemainPtr->statistik.loss = 0;
        newPemainPtr->statistik.totalPoin = 0;
        
        jumlahPemain++;
        cout << "Pemain berhasil ditambahkan!" << endl;
    } else {
        cout << "Database penuh!" << endl;
    }
}

void editPemain(string* id, string* newNama, string* newNegara) {
    int index = cariPemain(id);
    
    if (index != -1) {
        Pemain* pemainPtr = &dataPemain[index];
        
        if (!newNama->empty() && newNama->length() <= 11) {
            pemainPtr->nama = *newNama;
        }
        
        if (!newNegara->empty()) {
            pemainPtr->negara = *newNegara;
        }
        
        cout << "Data pemain berhasil diperbarui!" << endl;
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
}

void hapusPemain(string &id) {
    string* idPtr = &id;
    int index = cariPemain(idPtr);
    
    if (index != -1) {
        for (int j = index; j < jumlahPemain - 1; j++) {
            Pemain* currentPtr = &dataPemain[j];
            Pemain* nextPtr = &dataPemain[j + 1];
            
            *currentPtr = *nextPtr;
        }
        jumlahPemain--;
        cout << "Pemain berhasil dihapus!" << endl;
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
}

void catatTurnamen(string* id, int* win, int* draw, int* loss) {
    int index = cariPemain(id);
    
    if (index != -1) {
        Pemain* pemainPtr = &dataPemain[index];
        
        pemainPtr->statistik.win = *win;
        pemainPtr->statistik.draw = *draw;
        pemainPtr->statistik.loss = *loss;
        
        calculateTotalPoin(*pemainPtr);
        
        cout << "Data turnamen diperbarui!" << endl;
        cout << "Total poin pemain sekarang: " << pemainPtr->statistik.totalPoin << endl;
        
        sortPemainByPoin();
        
        cout << "Ranking diperbarui berdasarkan poin." << endl;
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
}

bool login(string* username, string* password, int &userIndex) {
    for (int i = 0; i < jumlahUsers; i++) {
        User* userPtr = &users[i];
        if (*username == userPtr->username && *password == userPtr->password) {
            userIndex = i;
            return true;
        }
    }
    return false;
}

bool registrasi(string &username, string &password) {
    if (jumlahUsers < maxUsers) {
        for (int i = 0; i < jumlahUsers; i++) {
            User* userPtr = &users[i];
            if (userPtr->username == username) {
                return false;
            }
        }
        
        User* newUserPtr = &users[jumlahUsers];
        newUserPtr->username = username;
        newUserPtr->password = password;
        newUserPtr->isAdmin = false;
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

void tampilkanSubMenuSort(Table &menuTable) {
    menuTable.add_row({"MENU SORT"});
    menuTable.add_row({"1. Sort By Poin"});
    menuTable.add_row({"2. Sort Nama (Descending)"});
    menuTable.add_row({"3. Sort Win (Ascending)"});
    menuTable.add_row({"4. Kembali ke Menu Utama"});
    
    menuTable[0].format()
        .font_align(FontAlign::center)
        .font_style({FontStyle::bold})
        .font_color(Color::yellow);
}

void prosesSubMenuSort(bool isAdmin) {
    int highlightArr = 0;
    int pilihan = 0;
    bool kembaliKeMenuUtama = false;
    
    while (!kembaliKeMenuUtama) {
        system("cls");
        
        Table subMenuTable;
        tampilkanSubMenuSort(subMenuTable);
        
        for (size_t i = 1; i < subMenuTable.size(); ++i) {
            if (i - 1 == highlightArr) {
                subMenuTable[i].format()
                    .background_color(Color::white)
                    .font_color(Color::red)
                    .font_align(FontAlign::center);
            } else {
                subMenuTable[i].format()
                    .font_align(FontAlign::center);
            }
        }
        
        cout << subMenuTable << endl;
        cout << "Gunakan panah atas/bawah dan Enter untuk memilih" << endl;
        
        int key = _getch();
        
        if (key == 224) {
            key = _getch();
            
            switch (key) {
                case 72: // up arrow
                    highlightArr = (highlightArr == 0) ? 3 : highlightArr - 1;
                    break;
                case 80: // down arrow
                    highlightArr = (highlightArr == 3) ? 0 : highlightArr + 1;
                    break;
            }
        } else if (key == 13) { // enter
            pilihan = highlightArr + 1;
            
            system("cls");
            
            switch (pilihan) {
                case 1: 
                    sortPemainByPoin();
                    tampilkanTabelPemain(false); 
                    system("pause");
                    break;
                case 2: 
                    sortPemainByNamaDesc();
                    tampilkanTabelPemain(false); 
                    system("pause");
                    break;
                case 3: 
                    sortPemainByWinDesc();
                    tampilkanTabelPemain(false); 
                    system("pause");
                    break;
                case 4: 
                    kembaliKeMenuUtama = true;
                    break;
            }
        }
    }
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
        
        tambahPemain(&inputNama, &inputID, &inputNegara);
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
    
    string* idPtr = &id;
    int index = cariPemain(idPtr);
    
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
        
        editPemain(&id, &newNama, &newNegara);
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
    
    string* idPtr = &id;
    int indexPemain = cariPemain(idPtr);
    
    if (indexPemain != -1) {
        string inputWin;
        bool validWin = false;
        int win = 0;
        
        while (!validWin) {
            cout << "Masukkan jumlah kemenangan (hanya angka): ";
            cin >> inputWin;
            
            string* inputWinPtr = &inputWin;
            validWin = validasiInputAngka(inputWinPtr);
            
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
            
            string* inputDrawPtr = &inputDraw;
            validDraw = validasiInputAngka(inputDrawPtr);
            
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
            
            string* inputLossPtr = &inputLoss;
            validLoss = validasiInputAngka(inputLossPtr);
            
            if (validLoss) {
                loss = stoi(inputLoss);
            } else {
                cout << "Error: Input harus berupa angka!" << endl;
            }
        }
        
        catatTurnamen(&id, &win, &draw, &loss);
    } else {
        cout << "Pemain dengan ID tersebut tidak ditemukan." << endl;
    }
    system("pause");
}

int main() {
    User* adminPtr = &users[0];
    adminPtr->username = "nabil";
    adminPtr->password = "046";
    adminPtr->isAdmin = true;  
    
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
                    
                    string* usernamePtr = &username;
                    string* passwordPtr = &password;
                    loginSukses = login(usernamePtr, passwordPtr, userIndex);
                    
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
            
            User* currentUserPtr = &users[userIndex];
            cout << "Selamat datang, " << currentUserPtr->username << "!\n\n";
            
            Table mainMenuTable;
            
            if (currentUserPtr->isAdmin) {
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
                
                if (currentUserPtr->isAdmin) {
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
                if (currentUserPtr->isAdmin) {
                    pilihan = highlightArr + 1;
                } else {
                    pilihan = highlightArr + 1;
                }
                
                system("cls");
                
                if (currentUserPtr->isAdmin) {
                    switch (pilihan) {
                        case 1: 
                            prosesMenuTambahPemain();
                            break;
                        case 2: 
                            prosesSubMenuSort(true);
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
                    switch (pilihan) {
                        case 1: 
                            prosesSubMenuSort(false);
                            system("pause");
                            break;
                        case 2: 
                            exitToLogin = true;
                            break;
                    }
                }
            }
        }
    }
    
    Table exitTable;
    tampilkanTabelExit(exitTable);
    cout << exitTable << endl;
    
    return 0;
}