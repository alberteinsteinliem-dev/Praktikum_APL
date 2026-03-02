#include <iostream>
using namespace std;

int main() {

    string username, password;
    string user_benar = "Albert";
    string pw_benar = "095";
    int percobaan = 0;
    bool login = false;

    while (percobaan < 3) {
        cout << "==============================\n";
        cout << "        LOGIN AKUN ANDA         \n";
        cout << "==============================\n";
        cout << "Nama     : ";
        cin >> username;
        cout << "Password : ";
        cin >> password;

        if (username == user_benar && password == pw_benar) {
            login = true;
            cout << "\nLogin Berhasil!\n";
            break;
        } else {
            percobaan++;
            cout << "\nLogin Salah! Percobaan ke-" << percobaan << endl;
        }
    }

    if (!login) {
        cout << "\nAnda gagal login 3 kali. Program berhenti.\n";
        return 0;
    }

    int pilihan;
    do {
        cout << "\n====================================\n";
        cout << "         MENU KONVERSI WAKTU        \n";
        cout << "====================================\n";
        cout << "1. Konversi Jam   -> Menit & Detik\n";
        cout << "2. Konversi Menit -> Jam & Detik\n";
        cout << "3. Konversi Detik -> Jam & Menit\n";
        cout << "4. Keluar\n";
        cout << "====================================\n";
        cout << "Pilih Menu (1-4): ";
        cin >> pilihan;

        switch (pilihan) {

            case 1: {
                int jam;
                cout << "\nMasukkan jumlah Jam: ";
                cin >> jam;

                int menit = jam * 60;
                int detik = jam * 3600;

                cout << "\nHasil Konversi:\n";
                cout << jam << " Jam = " << menit << " Menit\n";
                cout << jam << " Jam = " << detik << " Detik\n";
                break;
            }

            case 2: {
                int menit;
                cout << "\nMasukkan jumlah Menit: ";
                cin >> menit;

                int jam = menit / 60;
                int detik = menit * 60;

                cout << "\nHasil Konversi:\n";
                cout << menit << " Menit = " << jam << " Jam\n";
                cout << menit << " Menit = " << detik << " Detik\n";
                break;
            }

            case 3: {
                int detik;
                cout << "\nMasukkan jumlah Detik: ";
                cin >> detik;

                int jam = detik / 3600;
                int menit = detik / 60;

                cout << "\nHasil Konversi:\n";
                cout << detik << " Detik = " << jam << " Jam\n";
                cout << detik << " Detik = " << menit << " Menit\n";
                break;
            }

            case 4:
                cout << "\nTerima anda telah menggunakan program kami\n";
                break;

            default:
                cout << "\nPilihan ini tersedia!\n";
        }

    } while (pilihan != 4);

    return 0;
}