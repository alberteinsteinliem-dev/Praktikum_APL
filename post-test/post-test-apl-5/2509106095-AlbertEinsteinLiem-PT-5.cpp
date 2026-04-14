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

// ================= TAMPIL =================
void tampil(string teks){
    cout<<teks<<endl;
}

// ================= SORTING =================

// INSERTION SORT (ASCENDING - NAMA)
void sortNamaEventAsc(Event data[], int totalEvent){
    for(int i=1; i<totalEvent; i++){
        Event key = data[i];
        int j = i-1;

        while(j>=0 && data[j].nama > key.nama){
            data[j+1] = data[j];
            j--;
        }
        data[j+1] = key;
    }
}

// SELECTION SORT (DESCENDING - JUMLAH PESERTA)
void sortPesertaDesc(Event data[], int totalEvent, int jumlahPeserta[]){
    for(int i=0; i<totalEvent-1; i++){
        int maxIdx = i;

        for(int j=i+1; j<totalEvent; j++){
            if(jumlahPeserta[j] > jumlahPeserta[maxIdx]){
                maxIdx = j;
            }
        }

        swap(data[i], data[maxIdx]);
        swap(jumlahPeserta[i], jumlahPeserta[maxIdx]);
    }
}

// BUBBLE SORT (ASCENDING - TANGGAL)
void sortTanggalAsc(Event data[], int totalEvent){
    for(int i=0; i<totalEvent-1; i++){
        for(int j=0; j<totalEvent-i-1; j++){
            if(data[j].tanggal > data[j+1].tanggal){
                swap(data[j], data[j+1]);
            }
        }
    }
}

// ================= TAMPIL PESERTA =================
void tampilPesertaPerEvent(int indexEvent){
    cout<<"Peserta : ";
    if(jumlahPesertaEvent[indexEvent]==0){
        cout<<"Belum ada";
    }else{
        for(int i=0;i<jumlahPesertaEvent[indexEvent];i++){
            cout<<daftarPesertaEvent[indexEvent][i];
            if(i != jumlahPesertaEvent[indexEvent]-1) cout<<", ";
        }
    }
    cout<<endl;
}

// ================= TAMPIL EVENT =================
void tampilEvent(Event *data,int totalEvent,int Tampil){
    if(Tampil==totalEvent) return;

    cout<<left<<setw(4)<<Tampil+1
        <<setw(20)<<data[Tampil].nama
        <<setw(15)<<data[Tampil].lokasi
        <<setw(12)<<data[Tampil].hadiah
        <<setw(12)<<data[Tampil].tanggal
        <<setw(10)<<jumlahPesertaEvent[Tampil]<<endl;

    tampilPesertaPerEvent(Tampil);
    cout<<string(60,'-')<<endl;

    tampilEvent(data,totalEvent,Tampil+1);
}

void lihatEvent(Event *data,int totalEvent){
    cout<<"\n"<<string(70,'=')<<endl;

    cout<<left
        <<setw(4)<<"No"
        <<setw(20)<<"Nama Event"
        <<setw(15)<<"Lokasi"
        <<setw(12)<<"Hadiah"
        <<setw(12)<<"Tanggal"
        <<setw(10)<<"Peserta"<<endl;

    cout<<string(70,'=')<<endl;

    tampilEvent(data,totalEvent,0);

    cout<<string(70,'=')<<endl;
}

// ================= LOGIN =================
bool login(User *dataUser,int totalUser,string &roleLogin,int &indexLogin){

    string inputNama,inputNIM;

    cout<<"\nLOGIN\n";
    cout<<"Nama : "; cin>>inputNama;
    cout<<"NIM  : "; cin>>inputNIM;

    for(int i=0;i<totalUser;i++){
        if(dataUser[i].nama==inputNama && dataUser[i].nim==inputNIM){
            roleLogin=dataUser[i].role;
            indexLogin=i;
            cout<<"Login berhasil\n";
            return true;
        }
    }
    return false;
}

// ================= REGISTER =================
void registerUser(User *dataUser,int *totalUser){

    cout<<"\nREGISTER\n";
    cout<<"Nama : "; cin>>dataUser[*totalUser].nama;
    cout<<"NIM  : "; cin>>dataUser[*totalUser].nim;

    dataUser[*totalUser].role="user";
    (*totalUser)++;

    cout<<"Register berhasil\n";
}

// ================= EVENT =================
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

    for(int i=pilihanEvent-1;i<*totalEvent-1;i++)
        data[i]=data[i+1];

    (*totalEvent)--;

    cout<<"Event berhasil dihapus\n";
}

// ================= DAFTAR EVENT =================
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

// ================= EVENT DIIKUTI =================
void eventDiikuti(int User,string dataEventUser[][100],int jumlahEventUser[]){
    cout<<"\nEVENT YANG KAMU IKUTI\n";

    if(jumlahEventUser[User]==0)
        cout<<"Belum ikut event\n";
    else
        for(int i=0;i<jumlahEventUser[User];i++)
            tampil(dataEventUser[User][i]);
}

// ================= MENU ADMIN =================
void menuAdmin(){

    int pilihanMenu;

    do{
        cout<<"\nMENU ADMIN\n";
        cout<<"1.Tambah Event\n";
        cout<<"2.Lihat Event\n";
        cout<<"3.Edit Event\n";
        cout<<"4.Hapus Event\n";
        cout<<"5.Sort Nama (A-Z)\n";
        cout<<"6.Sort Peserta (Terbanyak)\n";
        cout<<"7.Sort Tanggal\n";
        cout<<"8.Logout\n";

        cout<<"Pilihan : ";
        cin>>pilihanMenu;

        if(pilihanMenu==1) tambahEvent(daftarEvent,&totalEvent);
        else if(pilihanMenu==2) lihatEvent(daftarEvent,totalEvent);
        else if(pilihanMenu==3) editEvent(daftarEvent,totalEvent);
        else if(pilihanMenu==4) hapusEvent(daftarEvent,&totalEvent);

        else if(pilihanMenu==5){
            sortNamaEventAsc(daftarEvent,totalEvent);
            cout<<"\nHasil Sorting Nama (A-Z)\n";
            lihatEvent(daftarEvent,totalEvent);
        }

        else if(pilihanMenu==6){
            sortPesertaDesc(daftarEvent,totalEvent,jumlahPesertaEvent);
            cout<<"\nHasil Sorting Peserta\n";
            lihatEvent(daftarEvent,totalEvent);
        }

        else if(pilihanMenu==7){
            sortTanggalAsc(daftarEvent,totalEvent);
            cout<<"\nHasil Sorting Tanggal\n";
            lihatEvent(daftarEvent,totalEvent);
        }

    }while(pilihanMenu!=8);
}

// ================= MENU USER =================
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

// ================= MAIN =================
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

            for(int i=1;i<=3;i++){
                if(login(daftarUser,totalUser,roleLogin,UserLogin)){
                    loginBerhasil=true;
                    break;
                }
                cout<<"Login gagal ("<<i<<"/3)\n";
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