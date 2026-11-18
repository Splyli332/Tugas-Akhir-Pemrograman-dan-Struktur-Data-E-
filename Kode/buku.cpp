#include "sipus.h"
#include <iostream>
#include <iomanip>

using namespace std;

void inisialisasi(DaftarBuku& d, int kapasitasAwal) {
    d.kapasitas = kapasitasAwal;
    d.n = 0;
    d.data = new Buku[d.kapasitas];
}

void bebaskan(DaftarBuku& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

static void perbesarKapasitas(DaftarBuku& d) {
    int kapBaru = (d.kapasitas == 0) ? 2 : d.kapasitas * 2;
    Buku* temp = new Buku[kapBaru];
    for (int i = 0; i < d.n; i++) {
        temp[i] = d.data[i];
    }
    delete[] d.data;
    d.data = temp;
    d.kapasitas = kapBaru;
}

Buku* cariKode(DaftarBuku& d, const string& kode) {
    for (int i = 0; i < d.n; i++) {
        if (d.data[i].kode == kode) return &d.data[i];
    }
    return nullptr;
}

bool tambahBuku(DaftarBuku& d, const Buku& b) {
    if (cariKode(d, b.kode) != nullptr) return false; // Tolak kode ganda
    if (d.n == d.kapasitas) {
        perbesarKapasitas(d);
    }
    d.data[d.n++] = b;
    return true;
}

bool ubahBuku(DaftarBuku& d, const string& kode, const Buku& dataBaru) {
    Buku* target = cariKode(d, kode);
    if (!target) return false;
    target->judul = dataBaru.judul;
    target->penulis = dataBaru.penulis;
    target->kategori = dataBaru.kategori;
    target->tahun = dataBaru.tahun;
    target->stok = dataBaru.stok;
    return true;
}

bool hapusBuku(DaftarBuku& d, const string& kode) {
    int idx = -1;
    for (int i = 0; i < d.n; i++) {
        if (d.data[i].kode == kode) {
            idx = i;
            break;
        }
    }
    if (idx == -1) return false;
    for (int i = idx; i < d.n - 1; i++) {
        d.data[i] = d.data[i + 1];
    }
    d.n--;
    return true;
}

void tampilBuku(const DaftarBuku& d) {
    cout << left << setw(10) << "Kode" << setw(25) << "Judul"
         << setw(18) << "Penulis" << setw(6) << "Thn" << setw(6) << "Stok" << endl;
    cout << string(65, '-') << endl;
    for (int i = 0; i < d.n; i++) {
        cout << left << setw(10) << d.data[i].kode
             << setw(25) << d.data[i].judul
             << setw(18) << d.data[i].penulis
             << setw(6) << d.data[i].tahun
             << setw(6) << d.data[i].stok << endl;
    }
}
