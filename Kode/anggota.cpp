#include "sipus.h"
#include <iostream>
#include <iomanip>

using namespace std;

void inisialisasi(DaftarAnggota& d, int kapasitasAwal) {
    d.kapasitas = kapasitasAwal;
    d.n = 0;
    d.data = new Anggota[d.kapasitas];
}

void bebaskan(DaftarAnggota& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

static void perbesarKapasitas(DaftarAnggota& d) {
    int kapBaru = (d.kapasitas == 0) ? 2 : d.kapasitas * 2;
    Anggota* temp = new Anggota[kapBaru];
    for (int i = 0; i < d.n; i++) {
        temp[i] = d.data[i];
    }
    delete[] d.data;
    d.data = temp;
    d.kapasitas = kapBaru;
}

Anggota* cariAnggota(DaftarAnggota& d, const string& id) {
    for (int i = 0; i < d.n; i++) {
        if (d.data[i].id == id) return &d.data[i];
    }
    return nullptr;
}

bool tambahAnggota(DaftarAnggota& d, const Anggota& a) {
    if (cariAnggota(d, a.id) != nullptr) return false;
    if (d.n == d.kapasitas) {
        perbesarKapasitas(d);
    }
    d.data[d.n++] = a;
    return true;
}

bool ubahAnggota(DaftarAnggota& d, const string& id, const Anggota& dataBaru) {
    Anggota* target = cariAnggota(d, id);
    if (!target) return false;
    target->nama = dataBaru.nama;
    target->prodi = dataBaru.prodi;
    return true;
}

void tampilAnggota(const DaftarAnggota& d) {
    cout << left << setw(10) << "ID" << setw(25) << "Nama"
         << setw(20) << "Prodi" << setw(10) << "Pinjam" << endl;
    cout << string(65, '-') << endl;
    for (int i = 0; i < d.n; i++) {
        cout << left << setw(10) << d.data[i].id
             << setw(25) << d.data[i].nama
             << setw(20) << d.data[i].prodi
             << setw(10) << d.data[i].sedangPinjam << endl;
    }
}
