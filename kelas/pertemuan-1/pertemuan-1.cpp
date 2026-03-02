// #include <iostream>
// using namespace std;
// int main() {
// bool hujan = true;
// string pesan = hujan ? "Bawa payung" : "Tidak perlu payung";
// cout << pesan;
// }

// #include <iostream>
// using namespace std;
// int main() {
// int z = 1;
// cout << "Sebelum increment " << z << endl;
// cout << "Increment di depan " << ++z << ", sudah bertambah" <<
// endl;
// cout << "Increment di belakang " << z++ << ", belum bertambah" <<
// endl;
// cout << "Hasil akhir " << z << endl;
// return 0;
// }

// #include <iostream>
// using namespace std;
// int main() {
// bool malas = false;
// bool mengantuk = true;
// if (malas) {
// if (mengantuk) {
// cout << "Saya tidur";
// }
// } else {
// cout << "Gak ngapa-ngapain";
// }
// }

#include <iostream>
using namespace std;

int main() {
int arr[] = {1, 2, 3, 4, 5};
for (int x : arr) {
cout << x << endl;
}
return 0;
}