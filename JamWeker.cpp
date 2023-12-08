#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Waktu {
    int jam;
    int menit;
};

void tunda(int detik) {
    this_thread::sleep_for(chrono::seconds(detik));
}

void tampilkanWaktuSaatIni() {
    auto waktuSaatIni = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm* localTime = localtime(&waktuSaatIni);
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "|Hari ini tanggal: " << put_time(localTime, "%d-%m-%Y") << " || Pukul: " << put_time(localTime, "%H:%M:%S") << "     |"<< endl;
    cout << "+---------------------------------------------------------------------+" << endl;
}

void aturAlarm(Waktu* waktu, int jumlahAlarm) {
    for (int i = 0; i < jumlahAlarm; ++i) {
        cout << "Masukkan jam alarm ke-" << i + 1 << " (format 24 jam): ";
        cin >> waktu[i].jam;

        cout << "Masukkan menit alarm ke-" << i + 1 << ": ";
        cin >> waktu[i].menit;

        if (waktu[i].jam < 0 || waktu[i].jam > 23 || waktu[i].menit < 0 || waktu[i].menit > 59) {
            cout << "Input waktu tidak valid." << endl;
            --i;
        }
    }
}

void mulaiStopwatch(int* detik) {
    while (true) {
        cout << "Waktu stopwatch: " << *detik << " detik" << endl;
        tunda(1);
        (*detik)++;
    }
}

void tampilkanDaftarTugas(string namaFile) {
    ifstream fileTugas(namaFile);
    if (fileTugas.is_open()) {
        string baris;
        cout << "+----------------------------------------------------------+" << endl;
        cout << "|             Daftar To-Do List                              |" << endl;
        cout << "+----------------------------------------------------------+" << endl;
        cout << "| No. | Tugas                 | Batas Waktu                |" << endl;
        cout << "+----------------------------------------------------------+" << endl;

        int nomor = 1;
        while (getline(fileTugas, baris)) {
            cout << "| " << setw(3) << nomor++ << " | " << setw(30) << baris << " |" << endl;
        }

        cout << "+----------------------------------------------------------+" << endl;
        fileTugas.close();
    } else {
        cerr << "Gagal membuka file daftar to-do." << endl;
    }
}

void tambahKeDaftarTugas(string namaFile) {
    ofstream fileTugas(namaFile, ios::app);
    if (fileTugas.is_open()) {
        string tugas;
        string batasWaktu;

        cout << "Masukkan tugas untuk daftar to-do: ";
        cin.ignore();
        getline(cin, tugas);

        cout << "Masukkan tanggal batas waktu (format DD-MM-YYYY): ";
        getline(cin, batasWaktu);

        fileTugas << "- Tugas: " << tugas << " (Batas Waktu: " << batasWaktu << ")" << endl;
        cout << "Tugas berhasil ditambahkan ke daftar to-do." << endl;
        
        fileTugas.close();
    } else {
        cerr << "Gagal membuka file daftar to-do." << endl;
    }
}

void hapusTugasDariDaftar(string namaFile) {
    ifstream fileTugasInput(namaFile);
    ofstream fileTugasOutput("temp_file.txt");

    if (!fileTugasInput.is_open() || !fileTugasOutput.is_open()) {
        cerr << "Gagal membuka file daftar to-do." << endl;
        return;
    }

    string baris;
    int nomor = 1;

    cout << "+--------------------------------------------------+" << endl;
    cout << "|          Daftar To-Do List                         |" << endl;
    cout << "+--------------------------------------------------+" << endl;
    cout << "| No. | Tugas           | Batas Waktu              |" << endl;
    cout << "+--------------------------------------------------+" << endl;

    while (getline(fileTugasInput, baris)) {
        cout << "| " << setw(3) << nomor++ << " | " << setw(30) << baris << " |" << endl;
    }

    cout << "+--------------------------------------------------+" << endl;

    int nomorHapus;
    cout << "Masukkan nomor tugas yang ingin dihapus (0 untuk batal): ";
    cin >> nomorHapus;

    if (nomorHapus == 0) {
        fileTugasInput.close();
        fileTugasOutput.close();
        remove("temp_file.txt");
        cout << "Penghapusan tugas dibatalkan." << endl;
        return;
    }

    nomor = 1;
    fileTugasInput.clear();
    fileTugasInput.seekg(0, ios::beg);

    while (getline(fileTugasInput, baris)) {
        if (nomor != nomorHapus) {
            fileTugasOutput << baris << endl;
        }
        nomor++;
    }

    fileTugasInput.close();
    fileTugasOutput.close();

    remove(namaFile.c_str());
    rename("temp_file.txt", namaFile.c_str());

    cout << "Tugas berhasil dihapus." << endl;
}

void motivasiHariIni(){
    srand(time(0));

    int random;
    random = rand() % 10 + 1;

    switch (random)
    {
    case 1:
        cout << "Hiduplah seolah-olah kamu akan mati besok. Belajarlah seolah-olah kamu hidup selamanya";
        break;

    case 2:
        cout << "Tidak ada batasan dalam belajar. Semakin rajin belajar, semakin banyak pengetahuan yang akan kamu miliki";
        break;

    case 3:
        cout << "Ketika rasa malas menghampiri, ingatlah bahwa disiplin adalah kunci menuju prestasi yang luar biasa";
        break;

    case 4:
        cout << "Jangan pernah berhenti belajar karena hidup tidak pernah berhenti mengajarkan hal-hal baru";
        break;

    case 5:
        cout << "Pembelajaran itu adalah proses tanpa akhir. Semakin kamu belajar, semakin kamu sadar betapa sedikit yang kamu ketahui";
        break;

    case 6:
        cout << "Malas adalah musuh terbesar dari kemajuan. Bangkitlah, lampaui rasa malas, dan perjuangkan masa depan yang kamu inginkan";
        break;

    case 7:
        cout << "Pendidikan adalah kunci untuk membuka pintu kesuksesan";
        break;

    case 8:
        cout << "Tak pernah ada kata terlambat untuk belajar";
        break;

    case 9:
        cout << "Teruslah mencari ilmu, jangan puas dengan pengetahuan terbatas";
        break;

    case 10:
        cout << "Bermalas-malasan hanya akan menghancurkan masa depanmu";
        break;
    }
}

int main() {
    int pilihan;
    int detikStopwatch = 0;
    const int jumlahAlarm = 1;
    Waktu waktuAlarm[jumlahAlarm];

    char opsiLanjut = 'y';
    do {
        cout << endl;
        cout << "+-----------------------------------------------------------------------+" << endl;
        cout << "|    PROGRAM PEMANTAUAN WAKTU DAN PRODUKTIVITAS: ALARM DAN TO-DO-LIST   |" << endl;
        cout << "+-----------------------------------------------------------------------+" << endl;
        cout << endl;
        cout << "+=======================================================================+" << endl;
        cout << "| 1.| Tampilkan Waktu                                                   |" << endl;
        cout << "| 2.| Atur Alarm                                                        |" << endl;
        cout << "| 3.| Jalankan Stopwatch                                                |" << endl;
        cout << "| 4.| Tambahkan Tugas To-Do-List                                        |" << endl;
        cout << "| 5.| Tampilkan To-Do List                                              |" << endl;
        cout << "| 6.| Hapus Tugas Dari Daftar To-Do                                     |" << endl;
        cout << "| 7.| Berikan Motivasi                                                  |" << endl;
        cout << "| 0.| Keluar                                                            |" << endl;
        cout << "+=======================================================================+" << endl;
        cout << "Pilih opsi (0-6): ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilkanWaktuSaatIni();
                cout << "1. Kembali ke menu utama" << endl;
                cout << "2. Keluar" << endl;
                cin >> pilihan;

                switch(pilihan){
                    case 1:
                        opsiLanjut = 'y';
                        break;
                    case 2:
                        break;
                }
                
                break;
            case 2:
                aturAlarm(waktuAlarm, jumlahAlarm);
                cout << "+=======================================================================+" << endl;
                cout << "1. Kembali ke menu utama" << endl;
                cout << "2. Keluar program" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihan;
                cout << "+=======================================================================+" << endl;

                switch (pilihan){
                    case 1:
                        opsiLanjut = 'y';
                        break;
                    case 2:
                        break;
                }
                break;
            case 3:
                mulaiStopwatch(&detikStopwatch);
                break;
            case 4:
                tambahKeDaftarTugas("daftar_tugas.txt");
                char opsi;
                cout << "Pilih opsi untuk daftar to-do:" << endl;
                cout << "1. Kembali ke menu utama" << endl;
                cout << "2. Input to-do list lagi" << endl;
                cout << "3. Keluar program" << endl;
                cout << "Masukkan pilihan (1-3): ";
                cin >> opsi;

                switch (pilihan) {
                    case '1':
                        opsiLanjut = 'y';
                    case '2':
                        break;
                    case '3':
                        cout << "Program selesai." << endl;
                        exit(0);
                }

                break;
            case 5:
                tampilkanDaftarTugas("daftar_tugas.txt");
                cout << "1. Kembali ke menu utama" << endl;
                cout << "2. Keluar" << endl;
                cin >> pilihan;

                switch(pilihan){
                    case 1:
                        opsiLanjut = 'y';
                        break;
                    case 2:
                        break;
                }
                break; 
            case 6:
                do {
                    hapusTugasDariDaftar("daftar_tugas.txt");
                    cout << "+====================================================+" << endl;
                    cout << "|1.| Hapus tugas lagi                                |" << endl;
                    cout << "|2.| Kembali ke menu utama                           |" << endl;
                    cout << "|3.| Keluar program                                  |" << endl;
                    cout << "+====================================================+" << endl;
                    cout << "Pilih opsi: ";
                    cin >> pilihan;

                    if (pilihan == 1) {
                    } else if (pilihan == 2) {
                        break;
                    } else if (pilihan == 3) {
                        exit(0);
                    } else {
                        cout << "Pilihan tidak valid. Program keluar." << endl;
                        exit(0);
                    }
                } while (pilihan == 1);
                break;
            case 7:
                do{
                    cout << "Motivasi hari ini: ";
                    motivasiHariIni();
                    cout << endl;
                    cout << "1. Berikan Motivasi Lagi" << endl;
                    cout << "2. Kembali ke menu " << endl;
                    cout << "3. Keluar program" << endl;
                    cout << "Pilih opsi: ";
                    cin >> pilihan;
                    if(pilihan == 1) {
                    }else if(pilihan == 2){
                        break;
                    }else if(pilihan == 3){
                        exit(0);
                    }
                }while (pilihan == 1);
                break;
            case 0:
                cout << "\nProgram selesai." << endl;
                break;
            default:
                cout << "Opsi tidak valid. Silakan pilih lagi." << endl;
        }

    } while (pilihan != 0 && (opsiLanjut == 'y' || opsiLanjut == 'Y'));

    return 0;
}
