#include <iostream>
#include <iomanip>
using namespace std;

struct Event{string nama,lokasi,hadiah,tanggal;};
struct User{string nama,nim,role;};

User daftarUser[100];
Event daftarEvent[100];

string daftarPesertaEvent[100][100], daftarEventUser[100][100];
int jumlahPesertaEvent[100]={0}, jumlahEventUser[100]={0};

int totalUser=0, totalEvent=0, UserLogin;
string roleLogin;

void tampil(string teks){
    cout<<teks<<endl;
}

void tampilEvent(Event *data,int totalEvent,int Tampil){
    if(Tampil==totalEvent) return;

    cout<<left<<setw(4)<<Tampil+1
        <<setw(20)<<data[Tampil].nama
        <<setw(15)<<data[Tampil].lokasi
        <<setw(12)<<data[Tampil].hadiah
        <<setw(12)<<data[Tampil].tanggal<<endl;

    tampilEvent(data,totalEvent,Tampil+1);
}

void lihatEvent(Event *data,int totalEvent){
    cout<<"\n"<<string(60,'=')<<endl;

    cout<<left
        <<setw(4)<<"No"
        <<setw(20)<<"Nama Event"
        <<setw(15)<<"Lokasi"
        <<setw(12)<<"Hadiah"
        <<setw(12)<<"Tanggal"<<endl;

    cout<<string(60,'=')<<endl;

    tampilEvent(data,totalEvent,0);

    cout<<string(60,'=')<<endl;
}

bool login(User *dataUser,int totalUser,string &roleLogin,int &indexLogin){

    string inputNama,inputNIM;

    cout<<"\nLOGIN\n";
    cout<<"Nama : "; cin>>inputNama;
    cout<<"NIM  : "; cin>>inputNIM;

    for(int User=0;User<totalUser;User++){
        if(dataUser[User].nama==inputNama && dataUser[User].nim==inputNIM){
            roleLogin = dataUser[User].role;
            indexLogin = User;
            cout<<"Login berhasil\n";
            return true;
        }
    }
    return false;
}

void registerUser(User *dataUser,int *totalUser){

    cout<<"\nREGISTER\n";
    cout<<"Nama : "; cin>>dataUser[*totalUser].nama;
    cout<<"NIM  : "; cin>>dataUser[*totalUser].nim;

    dataUser[*totalUser].role="user";
    (*totalUser)++;

    cout<<"Register berhasil\n";
}

void tambahEvent(Event *data,int *totalEvent){

    cin.ignore();

    cout<<"\nTAMBAH EVENT\n";
    cout<<"Nama Event : ";
    getline(cin,data[*totalEvent].nama);
    cout<<"Lokasi     : ";
    getline(cin,data[*totalEvent].lokasi);
    cout<<"Hadiah     : ";
    getline(cin,data[*totalEvent].hadiah);
    cout<<"Tanggal    : ";
    getline(cin,data[*totalEvent].tanggal);

    (*totalEvent)++;
}

void editEvent(Event *data,int totalEvent){

    lihatEvent(data,totalEvent);

    int pilihanEvent;
    cout<<"Pilih event : ";
    cin>>pilihanEvent;

    if(pilihanEvent<1 || pilihanEvent>totalEvent) return;

    cin.ignore();

    Event *pointerEvent = &data[pilihanEvent-1];

    cout<<"Nama : ";
    getline(cin,pointerEvent->nama);
    cout<<"Lokasi : ";
    getline(cin,pointerEvent->lokasi);
    cout<<"Hadiah : ";
    getline(cin,pointerEvent->hadiah);
    cout<<"Tanggal : ";
    getline(cin,pointerEvent->tanggal);
}

void hapusEvent(Event *data,int *totalEvent){

    lihatEvent(data,*totalEvent);

    int pilihanEvent;
    cout<<"Pilih event : ";
    cin>>pilihanEvent;

    if(pilihanEvent<1 || pilihanEvent>*totalEvent) return;

    for(int indexGeser=pilihanEvent-1; indexGeser<*totalEvent-1; indexGeser++)
        data[indexGeser]=data[indexGeser+1];

    (*totalEvent)--;

    cout<<"Event berhasil dihapus\n";
}

void daftarEventUserFunc(Event *data,int totalEvent,
                        User *dataUser,int UserLogin,
                        string dataPeserta[][100],int *jumlahPeserta,
                        string dataEventUser[][100],int *jumlahEventUser){

    lihatEvent(data,totalEvent);

    int pilihanEvent;
    cout<<"Pilih event : ";
    cin>>pilihanEvent;

    if(pilihanEvent<1 || pilihanEvent>totalEvent) return;

    dataPeserta[pilihanEvent-1][jumlahPeserta[pilihanEvent-1]++] =
        dataUser[UserLogin].nama;

    dataEventUser[UserLogin][jumlahEventUser[UserLogin]++] =
        data[pilihanEvent-1].nama;

    cout<<"Berhasil daftar event\n";
}

// EVENT YANG DIIKUTI
void eventDiikuti(int User,string dataEventUser[][100],int jumlahEventUser[]){
    cout<<"\nEVENT YANG KAMU IKUTI\n";

    if(jumlahEventUser[User]==0)
        cout<<"Belum ikut event\n";
    else
        for(int indexEvent=0; indexEvent<jumlahEventUser[User]; indexEvent++)
            tampil(dataEventUser[User][indexEvent]);
}

void menuAdmin(){

    int pilihanMenu;

    do{
        cout<<"\nMENU ADMIN\n";
        cout<<"1.Tambah Event\n";
        cout<<"2.Lihat Event\n";
        cout<<"3.Edit Event\n";
        cout<<"4.Hapus Event\n";
        cout<<"5.Logout\n";

        cout<<"Pilihan : ";
        cin>>pilihanMenu;

        if(pilihanMenu==1) tambahEvent(daftarEvent,&totalEvent);
        else if(pilihanMenu==2) lihatEvent(daftarEvent,totalEvent);
        else if(pilihanMenu==3) editEvent(daftarEvent,totalEvent);
        else if(pilihanMenu==4) hapusEvent(daftarEvent,&totalEvent);

    }while(pilihanMenu!=5);
}

void menuUser(){

    int pilihanMenu;

    do{
        cout<<"\nMENU USER\n";
        cout<<"1.Lihat Event\n";
        cout<<"2.Daftar Event\n";
        cout<<"3.Event Yang Diikuti\n";
        cout<<"4.Logout\n";
        cout<<"Pilihan : ";
        cin>>pilihanMenu;

        if(pilihanMenu==1) lihatEvent(daftarEvent,totalEvent);

        else if(pilihanMenu==2)
            daftarEventUserFunc(daftarEvent,totalEvent,
                                daftarUser,UserLogin,
                                daftarPesertaEvent,jumlahPesertaEvent,
                                daftarEventUser,jumlahEventUser);

        else if(pilihanMenu==3)
            eventDiikuti(UserLogin,
                         daftarEventUser,jumlahEventUser);

    }while(pilihanMenu!=4);
}

int main(){

    daftarUser[totalUser++]={"Albert","95","admin"};
    daftarEvent[totalEvent++]={"Lomba Lari","Lapangan","1 Juta","10/06/2026"};

    int pilihanMenu;

    do{
        cout<<"\nPENDAFTARAN EVENT\n";
        cout<<"1.Register\n";
        cout<<"2.Login\n";
        cout<<"3.Keluar\n";
        cout<<"Pilihan : ";
        cin>>pilihanMenu;

        if(pilihanMenu==1)
            registerUser(daftarUser,&totalUser);

        else if(pilihanMenu==2){

            bool loginBerhasil=false;

            for(int percobaan=1; percobaan<=3; percobaan++){
                if(login(daftarUser,totalUser,roleLogin,UserLogin)){
                    loginBerhasil=true;
                    break;
                }
                cout<<"Login gagal ("<<percobaan<<"/3)\n";
            }

            if(!loginBerhasil){
                cout<<"Login gagal 3 kali\n";
                return 0;
            }

            if(roleLogin=="admin")
                menuAdmin();
            else
                menuUser();
        }

    }while(pilihanMenu!=3);

    cout<<"Program selesai\n";
    return 0;
}