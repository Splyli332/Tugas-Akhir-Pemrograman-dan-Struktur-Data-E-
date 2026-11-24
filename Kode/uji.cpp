#include <iostream>
#include "sipus.h"

using namespace std;

int lulus = 0, gagal = 0;
void cek(bool kondisi, const string& nama) {
    cout << (kondisi ? "[LULUS] " : "[GAGAL] ") << nama << endl;
    kondisi ? lulus++ : gagal++;
}
int main() {
     DaftarBuku db;
    inisialisasi(db, 2);

    // Uji dari Patricia: Tambah buku & pembesaran kapasitas
    tambahBuku(db, {"BK-001", "Algoritma", "Budi", 0, 2023, 2, 0});
    tambahBuku(db, {"BK-002", "Struktur Data", "Wati", 0, 2024, 3, 0});
    tambahBuku(db, {"BK-003", "Basis Data", "Sari", 1, 2022, 1, 0});
    cek(db.n == 3 && db.kapasitas == 4, "Uji 1: Array dinamis buku membesar otomatis");

    // Uji dari Patricia: Tolak kode buku ganda
    cek(!tambahBuku(db, {"BK-001", "Duplikat", "X", 0, 2020, 1, 0}), "Uji 2: Kode buku ganda ditolak");

    // Uji dari Patricia: Hapus buku
    cek(hapusBuku(db, "BK-002") && db.n == 2, "Uji 3: Hapus buku berhasil");

    // Uji dari Suin : Tambah anggota & pembesaran kapasitas
    DaftarAnggota da;
    inisialisasi(da, 2);
    tambahAnggota(da, {"AG-001", "Suindri", "TI", 0});
    tambahAnggota(da, {"AG-002", "Lanlang", "TI", 0});
    tambahAnggota(da, {"AG-003", "Nicholas", "TI", 0});
    cek(da.n == 3 && da.kapasitas == 4, "Uji 4: Array dinamis anggota membesar otomatis");

    // Uji dari Suin : Bebaskan memori
    bebaskan(db);
    bebaskan(da);
    cek(db.data == nullptr && da.data == nullptr, "Uji 5: Memori dibebaskan bersih");

    cout << "\nTotal M2: " << lulus << " lulus, " << gagal << " gagal\n";
    return 0;
}