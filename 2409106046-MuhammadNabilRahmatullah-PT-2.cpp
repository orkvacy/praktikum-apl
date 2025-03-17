#include <iostream>
#include <iomanip>
#include <string>
#include <conio.h>  //masking password + arrow keys

using namespace std;

const int maxPemain = 100;
string pemain[maxPemain][4]; 
int turnamen[maxPemain][3];   
int totalPoin[maxPemain];     
int jumlahPemain = 0;


#define RESET   "\033[0m"
#define BLUE    "\033[34m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define RED     "\033[31m"
#define WHITE_BG "\033[47m"    

int main() {
    string username, password;
    int percobaan = 0;
    bool loginSukses = false;

    while (percobaan < 3) {
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
        
        if (username == "nabil" && password == "046") {
            loginSukses = true;
            break;
        } else {
            percobaan++;
            cout << "Login gagal! Percobaan ke-" << percobaan << "\n";
        }
    }

    if (!loginSukses) {
        cout << "Kesempatan habis, coba lagi nanti.\n";
        return 0;
    }

    int highlightArr = 0; 
    int pilihan = 0;         
    
    bool exitProgram = false;
    
    while (!exitProgram) {
        
        system("cls"); 
        
        const char* menuI[] = {
            "1. Tambah Pemain",
            "2. Tampilkan Pemain",
            "3. Edit Pemain",
            "4. Hapus Pemain",
            "5. Catat Turnamen",
            "6. Keluar"
        };
        
        for (int i = 0; i < 6; i++) {
            if (i == highlightArr) {
                cout << WHITE_BG << RED << menuI[i] << RESET << endl;
            } else {
                cout << menuI[i] << endl;
            }
        }
        
        cout << "Gunakan panah atas/bawah dan Enter untuk memilih" << endl;
        
        //arrow
        int key = _getch();
        
        if (key == 224) {
            key = _getch();
            
            switch (key) {
                case 72:
                    highlightArr = (highlightArr == 0) ? 5 : highlightArr - 1;
                    break;
                case 80:
                    highlightArr = (highlightArr == 5) ? 0 : highlightArr + 1;
                    break;
            }
        } else if (key == 13) {
            pilihan = highlightArr + 1; 
            
            system("cls");
            
            if (pilihan == 1) {
                if (jumlahPemain < maxPemain) {
                    string inputNama;
                    bool namaValid = false;
                    
                    while (!namaValid) {
                        cout << "Masukkan Nama Pemain (maksimal 11 karakter): ";
                        cin >> inputNama;
                        
                        if (inputNama.length() <= 11) {
                            namaValid = true;
                            pemain[jumlahPemain][0] = inputNama;
                        } else {
                            cout << "Error: Nama tidak boleh lebih dari 11 karakter!\n";
                        }
                    }
                    
                    string inputID;
                    bool idValid = false;
                    
                    while (!idValid) {
                        cout << "Masukkan ID Pemain: ";
                        cin >> inputID;
                        
                        idValid = true;
                        
                        for (int i = 0; i < jumlahPemain; i++) {
                            if (pemain[i][1] == inputID) {
                                idValid = false;
                                cout << "ID " << inputID << " sudah digunakan!\n";
                                break;
                            }
                        }
                        
                        if (idValid) {
                            pemain[jumlahPemain][1] = inputID;
                        }
                    }
                    
                    
                    pemain[jumlahPemain][2] = to_string(jumlahPemain + 1);
                    
                    cout << "Masukkan Negara: ";
                    cin >> pemain[jumlahPemain][3];
                    turnamen[jumlahPemain][0] = 0;
                    turnamen[jumlahPemain][1] = 0;
                    turnamen[jumlahPemain][2] = 0;
                    totalPoin[jumlahPemain] = 0; 
                    jumlahPemain++;
                    cout << "Pemain berhasil ditambahkan!\n";
                    system("pause"); 
                } else {
                    cout << "Database penuh!\n";
                    system("pause"); 
                }
            } 
            else if (pilihan == 2) {
                if (jumlahPemain == 0) {
                    cout << "Belum ada pemain yang terdaftar.\n";
                } else {
                    
                    for (int i = 0; i < jumlahPemain; i++) {
                        totalPoin[i] = (turnamen[i][0] * 3) + (turnamen[i][1] * 1) - (turnamen[i][2]*2);
                    }
                    
                    
                    for (int i = 0; i < jumlahPemain - 1; i++) {
                        for (int j = 0; j < jumlahPemain - i - 1; j++) {
                            if (totalPoin[j] < totalPoin[j + 1]) {
                                
                                int tempPoin = totalPoin[j];
                                totalPoin[j] = totalPoin[j + 1];
                                totalPoin[j + 1] = tempPoin;
                                
                                
                                string tempNama = pemain[j][0];
                                string tempID = pemain[j][1];
                                string tempRanking = pemain[j][2];
                                string tempNegara = pemain[j][3];
                                
                                pemain[j][0] = pemain[j + 1][0];
                                pemain[j][1] = pemain[j + 1][1];
                                pemain[j][2] = pemain[j + 1][2];
                                pemain[j][3] = pemain[j + 1][3];
                                
                                pemain[j + 1][0] = tempNama;
                                pemain[j + 1][1] = tempID;
                                pemain[j + 1][2] = tempRanking;
                                pemain[j + 1][3] = tempNegara;
                                
                                
                                int tempWin = turnamen[j][0];
                                int tempDraw = turnamen[j][1];
                                int tempLoss = turnamen[j][2];
                                
                                turnamen[j][0] = turnamen[j + 1][0];
                                turnamen[j][1] = turnamen[j + 1][1];
                                turnamen[j][2] = turnamen[j + 1][2];
                                
                                turnamen[j + 1][0] = tempWin;
                                turnamen[j + 1][1] = tempDraw;
                                turnamen[j + 1][2] = tempLoss;
                            }
                        }
                    }
                    
                    
                    for (int i = 0; i < jumlahPemain; i++) {
                        pemain[i][2] = to_string(i + 1);
                    }
                    
                    
                    cout << "\nDaftar Pemain Catur:\n";
                    cout << BLUE << "+-----+------------+------+--------+---------+-----+-----+-----+-------+\n";
                    cout << "| No  | Nama       | ID   | Ranking| Negara  |  W  |  D  |  L  | Poin  |\n";
                    cout << "+-----+------------+------+--------+---------+-----+-----+-----+-------+" << RESET << endl;
                    
                    for (int i = 0; i < jumlahPemain; i++) {
                        cout << "| " << setw(3) << i + 1 << " | "
                            << GREEN << setw(10) << left << pemain[i][0] << RESET <<" | "
                            << YELLOW << setw(4) << pemain[i][1] << RESET << " | "
                            << setw(6) << right << pemain[i][2] << " | "
                            << setw(7) << left << pemain[i][3] << " | "
                            << RED << setw(3) << right << turnamen[i][0] << RESET << " | "
                            << RED << setw(3) << turnamen[i][1] << RESET << " | "
                            << RED << setw(3) << turnamen[i][2] << RESET << " | "
                            << YELLOW << setw(5) << totalPoin[i] << RESET << " |\n";
                    }
                    cout << BLUE << "+-----+------------+------+--------+---------+-----+-----+-----+-------+" << RESET << endl;
                }
                system("pause");
            } 
            else if (pilihan == 3) {
                string id;
                cout << "Masukkan ID pemain yang ingin diedit: ";
                cin >> id;
                cin.ignore(); 
                
                bool ditemukan = false;
                for (int i = 0; i < jumlahPemain; i++) {
                    if (pemain[i][1] == id) {
                        string newNama, newNegara;
                        
                        cout << "Data saat ini: " << endl;
                        cout << "Nama: " << pemain[i][0] << endl;
                        cout << "Ranking: " << pemain[i][2] << " (otomatis diperbarui berdasarkan poin)" << endl;
                        cout << "Negara: " << pemain[i][3] << endl << endl;
                        
                        cout << "Masukkan Nama Baru (kosongkan untuk tetap, maks 11 karakter): ";
                        getline(cin, newNama);
                        if (!newNama.empty()) {
                            if (newNama.length() <= 11) {
                                pemain[i][0] = newNama;
                            } else {
                                cout << "Error: Nama tidak boleh lebih dari 11 karakter!\n";
                                cout << "Nama tidak diubah.\n";
                            }
                        }
                        
                        cout << "Masukkan Negara Baru (kosongkan untuk tetap): ";
                        getline(cin, newNegara);
                        if (!newNegara.empty()) {
                            pemain[i][3] = newNegara;
                        }
                        
                        cout << "Data pemain berhasil diperbarui!\n";
                        ditemukan = true;
                        break;
                    }
                }
                if (!ditemukan) {
                    cout << "Pemain dengan ID tersebut tidak ditemukan.\n";
                }
                system("pause"); 
            } 
            else if (pilihan == 4) {
                string id;
                cout << "Masukkan ID pemain yang ingin dihapus: ";
                cin >> id;
                bool ditemukan = false;
                for (int i = 0; i < jumlahPemain; i++) {
                    if (pemain[i][1] == id) {
                        for (int j = i; j < jumlahPemain - 1; j++) {
                            pemain[j][0] = pemain[j + 1][0];
                            pemain[j][1] = pemain[j + 1][1];
                            pemain[j][2] = pemain[j + 1][2];
                            pemain[j][3] = pemain[j + 1][3];
                            turnamen[j][0] = turnamen[j + 1][0];
                            turnamen[j][1] = turnamen[j + 1][1];
                            turnamen[j][2] = turnamen[j + 1][2];
                            totalPoin[j] = totalPoin[j + 1];  
                        }
                        jumlahPemain--;
                        cout << "Pemain berhasil dihapus!\n";
                        ditemukan = true;
                        break;
                    }
                }
                if (!ditemukan) {
                    cout << "Pemain dengan ID tersebut tidak ditemukan.\n";
                }
                system("pause");
            } 
            else if (pilihan == 5) {
                string id;
                cout << "Masukkan ID pemain: ";
                cin >> id;
                bool ditemukan = false;
                for (int i = 0; i < jumlahPemain; i++) {
                    if (pemain[i][1] == id) {
                        
                        string inputWin;
                        bool validWin = false;
                        while (!validWin) {
                            cout << "Masukkan jumlah kemenangan (hanya angka): ";
                            cin >> inputWin;
                            
                            validWin = true;
                            for (int j = 0; j < inputWin.length(); j++) {
                                if (!isdigit(inputWin[j])) {
                                    validWin = false;
                                    cout << "Error: Input harus berupa angka!\n";
                                    break;
                                }
                            }
                            
                            if (validWin) {
                                turnamen[i][0] = stoi(inputWin);
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
                                    cout << "Error: Input harus berupa angka!\n";
                                    break;
                                }
                            }
                            
                            if (validDraw) {
                                turnamen[i][1] = stoi(inputDraw);
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
                                    cout << "Error: Input harus berupa angka!\n";
                                    break;
                                }
                            }
                            
                            if (validLoss) {
                                turnamen[i][2] = stoi(inputLoss);
                            }
                        }
                        
                        totalPoin[i] = (turnamen[i][0] * 3) + (turnamen[i][1] * 1) - (turnamen[i][2] * 2);
                        
                        cout << "Data turnamen diperbarui!\n";
                        cout << "Total poin pemain sekarang: " << totalPoin[i] << "\n";
                        
                        
                        for (int a = 0; a < jumlahPemain - 1; a++) {
                            for (int b = 0; b < jumlahPemain - a - 1; b++) {
                                if (totalPoin[b] < totalPoin[b + 1]) {
                                    //swap total poin
                                    int tempPoin = totalPoin[b];
                                    totalPoin[b] = totalPoin[b + 1];
                                    totalPoin[b + 1] = tempPoin;
                                    
                                    //tukar pemain
                                    string tempNama = pemain[b][0];
                                    string tempID = pemain[b][1];
                                    string tempRanking = pemain[b][2];
                                    string tempNegara = pemain[b][3];
                                    
                                    pemain[b][0] = pemain[b + 1][0];
                                    pemain[b][1] = pemain[b + 1][1];
                                    pemain[b][2] = pemain[b + 1][2];
                                    pemain[b][3] = pemain[b + 1][3];
                                    
                                    pemain[b + 1][0] = tempNama;
                                    pemain[b + 1][1] = tempID;
                                    pemain[b + 1][2] = tempRanking;
                                    pemain[b + 1][3] = tempNegara;
                                    
                                    
                                    int tempWin = turnamen[b][0];
                                    int tempDraw = turnamen[b][1];
                                    int tempLoss = turnamen[b][2];
                                    
                                    turnamen[b][0] = turnamen[b + 1][0];
                                    turnamen[b][1] = turnamen[b + 1][1];
                                    turnamen[b][2] = turnamen[b + 1][2];
                                    
                                    turnamen[b + 1][0] = tempWin;
                                    turnamen[b + 1][1] = tempDraw;
                                    turnamen[b + 1][2] = tempLoss;
                                }
                            }
                        }
                        
                        //sorting
                        for (int c = 0; c < jumlahPemain; c++) {
                            pemain[c][2] = to_string(c + 1);
                        }
                        
                        cout << "Ranking diperbarui berdasarkan poin.\n";
                        ditemukan = true;
                        break;
                    }
                }
                if (!ditemukan) {
                    cout << "Pemain dengan ID tersebut tidak ditemukan.\n";
                }
                system("pause"); 
            }
            else if (pilihan == 6) {
                exitProgram = true;
            }
        }
    }

    cout << "Keluar dari program.\n";
    system("pause"); 
    return 0;
}