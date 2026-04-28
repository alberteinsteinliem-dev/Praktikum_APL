#include <iostream>
#include <iomanip>
#include <stdexcept>
using namespace std;

/* ================= USER-DEFINED LIBRARY (VERSI DALAM 1 FILE) ================= */
// fungsi seperti library buatan sendiri
void lemparError(const string& pesan){
    throw runtime_error(pesan);
}

void validasiInputAngka(){
    if(cin.fail()){
        cin.clear();
        cin.ignore(1000,'\n');
        throw invalid_argument("Harus angka Bro bukan huruf");
    }
}
/* ============================================================================ */

struct Event{
    int id;
    string nama,lokasi,hadiah,tanggal;
};

struct User{
    string nama,nim,role;
};

User daftarUser[100];
Event daftarEvent[100];

string daftarPesertaEvent[100][100], daftarEventUser[100][100];
int jumlahPesertaEvent[100]={0}, jumlahEventUser[100]={0};

int totalUser=0, totalEvent=0, UserLogin;
string roleLogin;

void tampil(string teks){
    cout<<teks<<endl;
}

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

void sortTanggalAsc(Event data[], int totalEvent){
    for(int i=0; i<totalEvent-1; i++){
        for(int j=0; j<totalEvent-i-1; j++){
            if(data[j].tanggal > data[j+1].tanggal){
                swap(data[j], data[j+1]);
            }
        }
    }
}

int linearSearchNama(Event *data, int totalEvent, string cari){
    for(int i=0;i<totalEvent;i++){
        if(data[i].nama == cari){
            return i;
        }
    }
    return -1;
}

int binarySearchID(Event *data, int totalEvent, int cariID){
    int low = 0, high = totalEvent - 1;
    while(low <= high){
        int mid = (low + high) / 2;
        if(data[mid].id == cariID) return mid;
        else if(data[mid].id < cariID) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

void menuSearching(Event *data, int totalEvent){
    int pilih;

    try{
        cout<<"\nMENU SEARCHING\n";
        cout<<"1. Cari event berdasarkan ID\n";
        cout<<"2. Cari event berdasarkan Nama\n";
        cout<<"Pilihan : ";
        cin>>pilih;
        validasiInputAngka();
    }catch(const exception &e){
        cout<<"Error: "<<e.what()<<endl;
        return;
    }

    if(pilih==1){
        int id;
        try{
            cout<<"Masukkan ID : ";
            cin>>id;
            validasiInputAngka();
        }catch(const exception &e){
            cout<<"Error: "<<e.what()<<endl;
            return;
        }

        int index = binarySearchID(data,totalEvent,id);

        if(index != -1){
            cout<<"Event ditemukan:\n";
            cout<<data[index].nama<<" - "<<data[index].lokasi<<endl;
        }else{
            cout<<"Event tidak ditemukan\n";
        }
    }
    else if(pilih==2){
        string nama;
        cin.ignore();
        cout<<"Masukkan Nama Event : ";
        getline(cin,nama);

        int index = linearSearchNama(data,totalEvent,nama);

        if(index != -1){
            cout<<"Event ditemukan:\n";
            cout<<data[index].nama<<" - "<<data[index].lokasi<<endl;
        }else{
            cout<<"Event tidak ditemukan\n";
        }
    }
}

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

void tampilEvent(Event *data,int totalEvent,int Tampil){
    if(Tampil==totalEvent) return;

    cout<<left
        <<setw(5)<<data[Tampil].id
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
        <<setw(5)<<"ID"
        <<setw(20)<<"Nama Event"
        <<setw(15)<<"Lokasi"
        <<setw(12)<<"Hadiah"
        <<setw(12)<<"Tanggal"
        <<setw(10)<<"Peserta"<<endl;

    cout<<string(70,'=')<<endl;

    tampilEvent(data,totalEvent,0);

    cout<<string(70,'=')<<endl;
}

bool login(User *dataUser,int totalUser,string &roleLogin,int &indexLogin){

    string inputNama,inputNIM;

    try{
        cout<<"\nLOGIN\n";
        cout<<"Nama : "; cin>>inputNama;
        cout<<"NIM  : "; cin>>inputNIM;

        if(cin.fail()){
            throw invalid_argument("Input login tidak valid");
        }
    }catch(const exception &e){
        cout<<"Error: "<<e.what()<<endl;
        return false;
    }

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

    data[*totalEvent].id = *totalEvent + 1;

    cout<<"\nTAMBAH EVENT\n";
    cout<<"Nama Event : ";
    getline(cin,data[*totalEvent].nama);
    cout<<"Lokasi     : ";
    getline(cin,data[*totalEvent].lokasi);
    cout<<"Hadiah     : ";
    getline(cin,data[*totalEvent].hadiah);
    cout<<"Tanggal    : ";
    getline(cin,data[*totalEvent].tanggal);

    try{
        if(data[*totalEvent].nama.empty()){
            lemparError("Nama event harus ada");
        }
    }catch(const exception &e){
        cout<<"Error: "<<e.what()<<endl;
        return;
    }

    (*totalEvent)++;
}

void daftarEventUserFunc(Event *data,int totalEvent,
                        User *dataUser,int UserLogin,
                        string dataPeserta[][100],int *jumlahPeserta,
                        string dataEventUser[][100],int *jumlahEventUser){

    lihatEvent(data,totalEvent);

    int pilihanEvent;

    try{
        cout<<"Pilih event : ";
        cin>>pilihanEvent;
        validasiInputAngka();

        if(pilihanEvent<1 || pilihanEvent>totalEvent){
            throw out_of_range("Pilihan event tidak tersedia!");
        }
    }catch(const exception &e){
        cout<<"Error: "<<e.what()<<endl;
        return;
    }

    dataPeserta[pilihanEvent-1][jumlahPeserta[pilihanEvent-1]++] =
        dataUser[UserLogin].nama;

    dataEventUser[UserLogin][jumlahEventUser[UserLogin]++] =
        data[pilihanEvent-1].nama;

    cout<<"Berhasil daftar event\n";
}

void menuAdmin(){
    int pilihanMenu;

    do{
        cout<<"\nMENU ADMIN\n";
        cout<<"1.Tambah Event\n";
        cout<<"2.Lihat Event\n";
        cout<<"3.Sort Nama\n";
        cout<<"4.Sort Peserta\n";
        cout<<"5.Sort Tanggal\n";
        cout<<"6.Search\n";
        cout<<"7.Logout\n";

        try{
            cout<<"Pilihan : ";
            cin>>pilihanMenu;
            validasiInputAngka();
        }catch(const exception &e){
            cout<<"Error: "<<e.what()<<endl;
            continue;
        }

        if(pilihanMenu==1) tambahEvent(daftarEvent,&totalEvent);
        else if(pilihanMenu==2) lihatEvent(daftarEvent,totalEvent);
        else if(pilihanMenu==3) sortNamaEventAsc(daftarEvent,totalEvent);
        else if(pilihanMenu==4) sortPesertaDesc(daftarEvent,totalEvent,jumlahPesertaEvent);
        else if(pilihanMenu==5) sortTanggalAsc(daftarEvent,totalEvent);
        else if(pilihanMenu==6) menuSearching(daftarEvent,totalEvent);

    }while(pilihanMenu!=7);
}

void menuUser(){
    int pilihanMenu;

    do{
        cout<<"\nMENU USER\n";
        cout<<"1.Lihat Event\n";
        cout<<"2.Daftar Event\n";
        cout<<"3.Search\n";
        cout<<"4.Logout\n";

        try{
            cout<<"Pilihan : ";
            cin>>pilihanMenu;
            validasiInputAngka();
        }catch(const exception &e){
            cout<<"Error: "<<e.what()<<endl;
            continue;
        }

        if(pilihanMenu==1) lihatEvent(daftarEvent,totalEvent);
        else if(pilihanMenu==2)
            daftarEventUserFunc(daftarEvent,totalEvent,
                                daftarUser,UserLogin,
                                daftarPesertaEvent,jumlahPesertaEvent,
                                daftarEventUser,jumlahEventUser);
        else if(pilihanMenu==3)
            menuSearching(daftarEvent,totalEvent);

    }while(pilihanMenu!=4);
}

int main(){

    daftarUser[totalUser++]={"Albert","95","admin"};
    daftarEvent[totalEvent++]={1,"Lomba Lari","Lapangan","1 Juta","10/06/2026"};

    int pilihanMenu;

    do{
        cout<<"\nPENDAFTARAN EVENT\n";
        cout<<"1.Register\n";
        cout<<"2.Login\n";
        cout<<"3.Keluar\n";

        try{
            cout<<"Pilihan : ";
            cin>>pilihanMenu;
            validasiInputAngka();
        }catch(const exception &e){
            cout<<"Error: "<<e.what()<<endl;
            continue;
        }

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