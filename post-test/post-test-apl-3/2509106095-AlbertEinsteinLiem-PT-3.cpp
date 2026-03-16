#include <iostream>
#include <iomanip>
using namespace std;

struct Event{string nama,lokasi,hadiah,tanggal;};
struct User{string nama,nim,role;};

User user[100];
Event event[100];

string peserta[100][100],ikutEvent[100][100];
int jumlahPeserta[100],jumlahIkutEvent[100];

int jumlahUser=0,jumlahEvent=0,idxLogin;
string Login;

void tampil(string x){cout<<x<<endl;}
void tampil(Event data){
    cout<<left<<setw(4)<<" "
        <<setw(20)<<data.nama
        <<setw(15)<<data.lokasi
        <<setw(12)<<data.hadiah
        <<setw(12)<<data.tanggal<<endl;
}
void tampilEvent(Event data[],int n,int i){

    if(i==n) return;

    cout<<left<<setw(4)<<i+1
        <<setw(20)<<data[i].nama
        <<setw(15)<<data[i].lokasi
        <<setw(12)<<data[i].hadiah
        <<setw(12)<<data[i].tanggal<<endl;

    tampilEvent(data,n,i+1);
}
void lihatEvent(Event data[],int n){

    cout<<"\n==============================================================\n";

    cout<<left
        <<setw(4)<<"No"
        <<setw(20)<<"Nama Event"
        <<setw(15)<<"Lokasi"
        <<setw(12)<<"Hadiah"
        <<setw(12)<<"Tanggal"<<endl;

    cout<<"==============================================================\n";

    tampilEvent(data,n,0);

    cout<<"==============================================================\n";
}
bool login(User u[],int n,string &Login,int &idx){

    string nama,nim;

    cout<<"\nLOGIN\n";
    cout<<"Nama : ";
     cin>>nama;
    cout<<"NIM  : ";
     cin>>nim;

    for(int i=0;i<n;i++){

        if(u[i].nama==nama && u[i].nim==nim){

            Login=u[i].role;
            idx=i;

            cout<<"Login berhasil\n";
            return true;
        }
    }

    return false;
}
void registerUser(User u[],int &n){

    cout<<"\nREGISTER\n";
    cout<<"Nama : ";
    cin>>u[n].nama;
    cout<<"NIM  : ";
    cin>>u[n].nim;
    u[n].role="user";
    n++;

    cout<<"Register berhasil\n";
}
void tambahEvent(Event data[],int &n){

    cin.ignore();

    cout<<"\nTAMBAH EVENT\n";
    cout<<"Nama Event : ";
    getline(cin,data[n].nama);
    cout<<"Lokasi     : ";
    getline(cin,data[n].lokasi);
    cout<<"Hadiah     : ";
    getline(cin,data[n].hadiah);
    cout<<"Tanggal    : ";
    getline(cin,data[n].tanggal);

    n++;
}
void editEvent(Event data[],int n){

    lihatEvent(data,n);

    int x;
    cout<<"Pilih event yang ingin diedit : ";
    cin>>x;

    if(x<1 || x>n) return;

    cin.ignore();
    cout<<"Nama : ";
    getline(cin,data[x-1].nama);
    cout<<"Lokasi : ";
    getline(cin,data[x-1].lokasi);
    cout<<"Hadiah : ";
    getline(cin,data[x-1].hadiah);
    cout<<"Tanggal : ";
    getline(cin,data[x-1].tanggal);
}
void hapusEvent(Event data[],int &n){

    lihatEvent(data,n);

    int x;
    cout<<"Pilih event : ";
    cin>>x;

    if(x<1 || x>n) return;

    for(int i=x-1;i<n-1;i++)
        data[i]=data[i+1];

    n--;
    
    cout<<"Event dihapus\n";
}
void daftarEvent(Event data[],int n,User u[],int idx,
                 string peserta[][100],int JumlahPeserta[],
                 string ikut[][100],int JumlahIkutEvent[]){

    lihatEvent(data,n);

    int x;
    cout<<"Pilih event : ";
    cin>>x;

    if(x<1 || x>n) return;

    peserta[x-1][JumlahPeserta[x-1]++]=u[idx].nama;
    ikut[idx][JumlahIkutEvent[idx]++]=data[x-1].nama;

    cout<<"Berhasil mendaftar event\n";
}
void lihatPeserta(Event data[],int n,string p[][100],int JumlahPeserta[]){

    lihatEvent(data,n);

    int x;
    cout<<"Pilih event : ";
    cin>>x;

    if(x<1 || x>n) return;

    cout<<"\nPeserta "<<data[x-1].nama<<endl;

    if(JumlahPeserta[x-1]==0)
        cout<<"Belum ada peserta\n";
    else
        for(int i=0;i<JumlahPeserta[x-1];i++)
            tampil(p[x-1][i]);
}
void eventDiikuti(int idx,string ikut[][100],int JumlahIkutEvent[]){

    cout<<"\nEVENT YANG KAMU IKUTI\n";

    if(JumlahIkutEvent[idx]==0)
        cout<<"Belum ikuti event\n";
    else
        for(int i=0;i<JumlahIkutEvent[idx];i++)
            tampil(ikut[idx][i]);
}
void menuAdmin(){

    int Pilih;

    do{

        cout<<"\nMENU ADMIN\n";
        cout<<"1.Tambah Event\n";
        cout<<"2.Lihat Event\n";
        cout<<"3.Edit Event\n";
        cout<<"4.Hapus Event\n";
        cout<<"5.Lihat Peserta\n";
        cout<<"6.Logout\n";

        cout<<"Pilihan : ";
        cin>>Pilih;

        if(Pilih==1) tambahEvent(event,jumlahEvent);
        else if(Pilih==2) lihatEvent(event,jumlahEvent);
        else if(Pilih==3) editEvent(event,jumlahEvent);
        else if(Pilih==4) hapusEvent(event,jumlahEvent);
        else if(Pilih==5) lihatPeserta(event,jumlahEvent,peserta,jumlahPeserta);

    }while(Pilih!=6);
}
void menuUser(){

    int Pilih;

    do{

        cout<<"\nMENU USER\n";
        cout<<"1.Lihat Event\n";
        cout<<"2.Daftar Event\n";
        cout<<"3.Event Yang Diikuti\n";
        cout<<"4.Logout\n";

        cout<<"Pilihan : ";
        cin>>Pilih;

        if(Pilih==1) lihatEvent(event,jumlahEvent);

        else if(Pilih==2)
            daftarEvent(event,jumlahEvent,user,idxLogin,
                        peserta,jumlahPeserta,
                        ikutEvent,jumlahIkutEvent);

        else if(Pilih==3)
            eventDiikuti(idxLogin,ikutEvent,jumlahIkutEvent);

    }while(Pilih!=4);
}
int main(){

    user[jumlahUser++]={"Albert","95","admin"};

    event[jumlahEvent++]={"Lomba Lari","Lapangan","1 Juta","10/06/2026"};

    int pilih;

    do{

        cout<<"\nPENDAFTARAN EVENT\n";
        cout<<"1.Register\n";
        cout<<"2.Login\n";
        cout<<"3.Keluar\n";

        cout<<"Pilihan : ";
        cin>>pilih;

        if(pilih==1)
            registerUser(user,jumlahUser);

        else if(pilih==2){

            bool berhasil=false;

            for(int i=1;i<=3;i++){

                if(login(user,jumlahUser,Login,idxLogin)){
                    berhasil=true;
                    break;
                }

                cout<<"Login gagal ("<<i<<"/3)\n";
            }

            if(!berhasil){
                cout<<"Login gagal 3 kali. Program berhenti\n";
                return 0;
            }

            if(Login=="admin")
                menuAdmin();
            else
                menuUser();
        }

    }while(pilih!=3);

    cout<<"Program selesai\n";

    return 0;
}