#include <iostream>
using namespace std;

struct Event{
    string namaEvent;
    string lokasi;
    string hadiah;
    string tanggal;
};
struct User{
    string nama;
    string nim;
    string role;
};
User user[100];
Event event[100];
string peserta[100][100];
int jumlahPeserta[100];
string ikutEvent[100][100];
int jumlahIkutevent[100];
int jumlahUser = 0;
int jumlahEvent = 0;
string Login;
int idxLogin;

void registerUser(){
    cout << "\nREGISTER\n";
    cout << "Nama : ";
    cin >> user[jumlahUser].nama;
    cout << "NIM  : ";
    cin >> user[jumlahUser].nim;
    user[jumlahUser].role = "user";
    jumlahUser++;

    cout << "Register berhasil\n";
}

bool login(){

    string nama,nim;

    cout << "\nLOGIN\n";
    cout << "Nama : ";
    cin >> nama;

    cout << "NIM  : ";
    cin >> nim;

    for(int i=0;i<jumlahUser;i++)
    {
        if(user[i].nama==nama && user[i].nim==nim)
        {
            Login=user[i].role;
            idxLogin=i;

            cout<<"Login berhasil\n";
            return true;
        }
    }

    cout<<"Login gagal\n";
    return false;
}

void lihatEvent(){

    cout << "\n==================================================================\n";
    cout << "No | Nama Event       | Lokasi           | Hadiah   | Tanggal\n";
    cout << "==================================================================\n";

    for(int i=0;i<jumlahEvent;i++)
    {
        cout << i+1 << "  | "
             << event[i].namaEvent << "      | "
             << event[i].lokasi << "         | "
             << event[i].hadiah << "   | "
             << event[i].tanggal << endl;
    }

    cout << "==================================================================\n";
}

void tambahEvent(){

    cout << "\nTAMBAH EVENT\n";

    cin.ignore();

    cout << "Nama Event : ";
    getline(cin,event[jumlahEvent].namaEvent);
    cout << "Lokasi : ";
    getline(cin,event[jumlahEvent].lokasi);
    cout << "Hadiah : ";
    getline(cin,event[jumlahEvent].hadiah);
    cout << "Tanggal (dd/mm/yyyy) : ";
    getline(cin,event[jumlahEvent].tanggal);
    jumlahEvent++;
    cout << "Event berhasil ditambahkan\n";
}

void editEvent(){

    lihatEvent();

    int nomor;
    cout<<"Pilih event yang ingin diedit : ";
    cin>>nomor;

    if(nomor<1 || nomor>jumlahEvent){
        cout<<"Belum ada event\n";
        return;
    }

    int i = nomor-1;

    cin.ignore();
    cout<<"Nama Event Baru : ";
    getline(cin,event[i].namaEvent);
    cout<<"Lokasi Baru : ";
    getline(cin,event[i].lokasi);
    cout<<"Hadiah Baru : ";
    getline(cin,event[i].hadiah);
    cout<<"Tanggal Baru : ";
    getline(cin,event[i].tanggal);
    cout<<"Event berhasil diupdate\n";
}

void hapusEvent(){

    lihatEvent();

    int nomor;
    cout<<"Pilih event yang ingin dihapus : ";
    cin>>nomor;
    if(nomor<1 || nomor>jumlahEvent){
        cout<<"Belum ada event\n";
        return;
    }

    for(int i=nomor-1;i<jumlahEvent-1;i++)
        event[i]=event[i+1];

    jumlahEvent--;

    cout<<"Event dihapus\n";
}

void daftarEvent(){

    lihatEvent();

    int nomor;
    cout<<"Pilih event yang ingin diikuti : ";
    cin>>nomor;

    if(nomor<1 || nomor>jumlahEvent){
        cout<<"Belum ada event\n";
        return;
    }

    int i = nomor-1;

    peserta[i][jumlahPeserta[i]] = user[idxLogin].nama;
    jumlahPeserta[i]++;

    ikutEvent[idxLogin][jumlahIkutevent[idxLogin]] = event[i].namaEvent;
    jumlahIkutevent[idxLogin]++;

    cout<<"Berhasil mendaftar event\n";
}

void lihatPeserta(){

    lihatEvent();

    int nomor;
    cout<<"Pilih event : ";
    cin>>nomor;

    if(nomor<1 || nomor>jumlahEvent){
        cout<<"Belum ada event\n";
        return;
    }

    int i = nomor-1;

    cout << "\nPeserta Event : " << event[i].namaEvent << endl;
    if(jumlahPeserta[i]==0)
        cout<<"Belum ada peserta\n";
    else
    {
        for(int j=0;j<jumlahPeserta[i];j++)
            cout<<j+1<<". "<<peserta[i][j]<<endl;
    }
}

void eventDiikuti(){

    cout<<"\nEVENT YANG KAMU IKUTI\n";
    if(jumlahIkutevent[idxLogin]==0)
        cout<<"Belum mengikuti event\n";
    else
    {
        for(int i=0;i<jumlahIkutevent[idxLogin];i++)
            cout<<i+1<<". "<<ikutEvent[idxLogin][i]<<endl;
    }
}

void menuAdmin(){

    int pilih;

    do{
        cout<<"\nMENU ADMIN\n";
        cout<<"1. Tambah Event\n";
        cout<<"2. Lihat Event\n";
        cout<<"3. Edit Event\n";
        cout<<"4. Hapus Event\n";
        cout<<"5. Lihat Peserta\n";
        cout<<"6. Logout\n";

        cout<<"Pilihan : ";
        cin>>pilih;

        switch(pilih){
            case 1: tambahEvent(); break;
            case 2: lihatEvent(); break;
            case 3: editEvent(); break;
            case 4: hapusEvent(); break;
            case 5: lihatPeserta(); break;
        }

    }while(pilih!=6);
}

void menuUser(){

    int pilih;

    do{
        cout<<"\nMENU USER\n";
        cout<<"1. Lihat Event\n";
        cout<<"2. Daftar Event\n";
        cout<<"3. Event Yang Diikuti\n";
        cout<<"4. Logout\n";

        cout<<"Pilihan : ";
        cin>>pilih;

        switch(pilih){
            case 1: lihatEvent(); break;
            case 2: daftarEvent(); break;
            case 3: eventDiikuti(); break;
        }

    }while(pilih!=4);
}

int main(){

    user[jumlahUser].nama="A";
    user[jumlahUser].nim="95";
    user[jumlahUser].role="admin";
    jumlahUser++;

    event[jumlahEvent].namaEvent="Lomba Makan";
    event[jumlahEvent].lokasi="Lapangan";
    event[jumlahEvent].hadiah="1 Juta";
    event[jumlahEvent].tanggal="10/06/2026";
    jumlahEvent++;

    int pilihan;
    int percobaanLogin = 0;

    do{
        cout<<"\nPENDAFTARAN EVENT\n";
        cout<<"1. Register\n";
        cout<<"2. Login\n";
        cout<<"3. Keluar\n";

        cout<<"Pilihan : ";
        cin>>pilihan;

        switch(pilihan){

            case 1:
                registerUser();
                break;

            case 2:
            {
                bool berhasil = false;

                for(int i=1;i<=3;i++){

                    if(login()){
                        berhasil = true;
                        break;
                    }

                    cout<<"Login gagal ("<<i<<"/3)\n";
                }

                if(berhasil){

                    if(Login=="admin")
                        menuAdmin();
                    else
                        menuUser();
                }
                else{
                    cout<<"Login gagal 3 kali. Program berhenti\n";
                    return 0;
                }

                break;
            }
        }

    }
    while(pilihan!=3);

    cout<<"Program selesai\n";
}