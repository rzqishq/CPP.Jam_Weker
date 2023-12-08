#include <iostream>
#include <iomanip>
#include <chrono>
#include <thread>
#include <fstream>
#include <cstdlib>
#include <ctime>

using namespace std;

const string DAFTAR_TUGAS_FILE = "daftar_tugas.txt";


enum OpsiMenu {
    TAMPILKAN_WAKTU = 1,
    ATUR_ALARM,
    JALANKAN_STOPWATCH,
    TAMBAHKAN_TUGAS,
    TAMPILKAN_TUGAS,
    HAPUS_TUGAS,
    BERIKAN_MOTIVASI,
    KELUAR
};

struct Waktu {
    int jam;
    int menit;
};

bool tunda(int detik) {
    this_thread::sleep_for(chrono::seconds(detik));
    return true;
};

void tampilkanWaktuSaatIni() {
    auto waktuSaatIni = chrono::system_clock::to_time_t(chrono::system_clock::now());
    tm* localTime = localtime(&waktuSaatIni);
    cout << "+---------------------------------------------------------------------+" << endl;
    cout << "|Hari ini tanggal: " << put_time(localTime, "%d-%m-%Y") << " || Pukul: " << put_time(localTime, "%H:%M:%S") << "                      |"<< endl;
    cout << "+---------------------------------------------------------------------+" << endl;
}

bool aturAlarm(Waktu* waktu, int jumlahAlarm) {
    for (int i = 0; i < jumlahAlarm; ++i) {
        cout << "Masukkan jam alarm ke-" << i + 1 << " (format 24 jam): ";
        cin >> waktu[i].jam;

        cout << "Masukkan menit alarm ke-" << i + 1 << ": ";
        cin >> waktu[i].menit;

        if (waktu[i].jam < 0 || waktu[i].jam > 23 || waktu[i].menit < 0 || waktu[i].menit > 59) {
            cout << "Input waktu tidak valid." << endl;
            return false; // Gagal
        }
    }
    return true;
}

int mulaiStopwatch(int* detik) {
    int durasi = 0;
    while (true) {
        cout << "Waktu stopwatch: " << *detik << " detik" << endl;
        tunda(1);
        (*detik)++;
        durasi++;
    }
    return durasi;
}

void tampilkanDaftarTugas() {
    ifstream fileTugas(DAFTAR_TUGAS_FILE);
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

bool tambahKeDaftarTugas() {
    ofstream fileTugas(DAFTAR_TUGAS_FILE, ios::app);
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
        return true; // Berhasil
    } else {
        cerr << "Gagal membuka file daftar to-do." << endl;
        return false; // Gagal
    }
}

bool hapusTugasDariDaftar() {
    ifstream fileTugasInput(DAFTAR_TUGAS_FILE);
    ofstream fileTugasOutput("temp_file.txt");

    if (!fileTugasInput.is_open() || !fileTugasOutput.is_open()) {
        cerr << "Gagal membuka file daftar to-do." << endl;
        return false;
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
        return false;
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

    remove(DAFTAR_TUGAS_FILE.c_str());  
    rename("temp_file.txt", DAFTAR_TUGAS_FILE.c_str());  

    cout << "Tugas berhasil dihapus." << endl;

    return true;
}

string motivasiHariIni() {
    srand(time(0));

    int random;
    random = rand() % 10 + 1;

    string motivasi;
    switch (random) {
    case 1:
        motivasi = "Hiduplah seolah-olah kamu akan mati besok. Belajarlah seolah-olah kamu hidup selamanya";
        break;

    case 2:
        motivasi = "Tidak ada batasan dalam belajar. Semakin rajin belajar, semakin banyak pengetahuan yang akan kamu miliki";
        break;

    case 3:
        motivasi = "Ketika rasa malas menghampiri, ingatlah bahwa disiplin adalah kunci menuju prestasi yang luar biasa";
        break;

    case 4:
        motivasi = "Jangan pernah berhenti belajar karena hidup tidak pernah berhenti mengajarkan hal-hal baru";
        break;

    case 5:
        motivasi = "Pembelajaran itu adalah proses tanpa akhir. Semakin kamu belajar, semakin kamu sadar betapa sedikit yang kamu ketahui";
        break;

    case 6:
        motivasi = "Malas adalah musuh terbesar dari kemajuan. Bangkitlah, lampaui rasa malas, dan perjuangkan masa depan yang kamu inginkan";
        break;

    case 7:
        motivasi = "Pendidikan adalah kunci untuk membuka pintu kesuksesan";
        break;

    case 8:
        motivasi = "Tak pernah ada kata terlambat untuk belajar";
        break;

    case 9:
        motivasi = "Teruslah mencari ilmu, jangan puas dengan pengetahuan terbatas";
        break;

    case 10:
        motivasi = "Bermalas-malasan hanya akan menghancurkan masa depanmu";
        break;
    }

    cout << "Motivasi: " <<  motivasi <<endl;
    return motivasi;
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

        switch (static_cast<OpsiMenu>(pilihan)) {
            case TAMPILKAN_WAKTU:
                tampilkanWaktuSaatIni();
                cout << "+========================================================+" << endl;
                cout << "|1.| Kembali ke menu utama                               |" << endl;
                cout << "|2.| Keluar program                                      |" << endl;
                cout << "+========================================================+" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihan;

                switch(pilihan){
                    case 1:
                        opsiLanjut = 'y';
                        break;
                    case 2:
                        cout << "\nProgram selesai." << endl;
                        exit(0);
                }
                
                break;
            case ATUR_ALARM:
                aturAlarm(waktuAlarm, jumlahAlarm);
                cout << "+========================================================+" << endl;
                cout << "|1.| Kembali ke menu utama                               |" << endl;
                cout << "|2.| Keluar program                                      |" << endl;
                cout << "+========================================================+" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihan;

                switch (pilihan){
                    case 1:
                        opsiLanjut = 'y';
                        break;
                    case 2:
                        cout << "\nProgram selesai." << endl;
                        exit(0);
                }
                break;
            case JALANKAN_STOPWATCH:
                mulaiStopwatch(&detikStopwatch);
                break;
            case TAMBAHKAN_TUGAS:
                tambahKeDaftarTugas();
                cout << "+====================================================+" << endl;
                cout << "|1.| Kembali ke menu utama                           |" << endl;
                cout << "|2.| Input to-do list lagi                           |" << endl;
                cout << "|3.| Keluar program                                  |" << endl;
                cout << "+====================================================+" << endl;
                cout << "Masukkan pilihan (1-3): ";
                cin >> pilihan;

                switch (pilihan) {
                    case '1':
                        opsiLanjut = 'y';
                    case '2':
                        break;
                    case '3':
                        cout << "\nProgram selesai." << endl;
                        exit(0);
                }

                break;
            case TAMPILKAN_TUGAS:
                tampilkanDaftarTugas();
                cout << "+========================================================+" << endl;
                cout << "|1.| Kembali ke menu utama                               |" << endl;
                cout << "|2.| Keluar program                                      |" << endl;
                cout << "+========================================================+" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihan;

                switch(pilihan){
                    case 1:
                        opsiLanjut = 'y';
                        break;
                    case 2:
                        cout << "\nProgram selesai." << endl;
                        exit(0);
                }
                break; 
            case HAPUS_TUGAS:
                do {
                    hapusTugasDariDaftar();
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
                        cout << "\nProgram selesai";
                        exit(0);
                    } else {
                        cout << "Pilihan tidak valid. Program keluar." << endl;
                        exit(0);
                    }
                } while (pilihan == 1);
                break;
            case BERIKAN_MOTIVASI:
                do {
                motivasiHariIni();
                cout << "+====================================================+" << endl;
                cout << "|1.| Berikan motivasi lagi                           |" << endl;
                cout << "|2.| Kembali ke menu utama                           |" << endl;
                cout << "|3.| Keluar program                                  |" << endl;
                cout << "+====================================================+" << endl;
                cout << "Pilih opsi: ";
                cin >> pilihan;
                   
                if(pilihan == 1) {
                }else if(pilihan == 2){
                    break;
                }else if(pilihan == 3){
                    cout << "\nProgram selesai";
                    exit(0);                    }
                }while (pilihan == 1);
                break;
            case KELUAR:
                cout << "\nProgram selesai." << endl;
                break;
            default:
                cout << "Opsi tidak valid. Silakan pilih lagi." << endl;
        }

    } while (pilihan != 0 && (opsiLanjut == 'y' || opsiLanjut == 'Y'));

    return 0;
}
