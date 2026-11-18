// sipus.h - definisi tipe data dan prototipe fungsi
#ifndef SIPUS_H
#define SIPUS_H

#include <string>
using namespace std;

const int JML_KATEGORI = 5;      // Ukuran baris rekap
const int JML_BULAN    = 12;     // Ukuran kolom rekap
const int MAKS_PINJAM  = 3;      // Batas buku/anggota
const int DENDA_HARIAN = 1000;   // Rupiah per hari

struct Tanggal {
    int hari, bulan, tahun;
};

struct Buku {
    string kode;          // Format "BK-001"
    string judul;
    string penulis;
    int    kategori;      // 0..JML_KATEGORI-1
    int    tahun;
    int    stok;          // Eksemplar tersedia
    int    totalDipinjam; // Untuk statistik
};

struct Anggota {
    string id;            // Format "AG-001"
    string nama;
    string prodi;
    int    sedangPinjam;  // Maksimum MAKS_PINJAM
};

struct Transaksi {
    int     nomor;
    string  idAnggota;
    string  kodeBuku;
    Tanggal tglPinjam;
    Tanggal tglKembali;   // Diisi saat buku kembali
    bool    selesai;
    int     denda;
};

// Pembungkus array dinamis: alamat, isi, kapasitas
struct DaftarBuku {
    Buku* data;
    int n, kapasitas;
};

struct DaftarAnggota {
    Anggota* data;
    int n, kapasitas;
};

struct DaftarTransaksi {
    Transaksi* data;
    int n, kapasitas;
};

// ---- Modul Buku (Suindri) ----
void inisialisasi(DaftarBuku& d, int kapasitasAwal);
void bebaskan(DaftarBuku& d);
bool tambahBuku(DaftarBuku& d, const Buku& b);
bool ubahBuku(DaftarBuku& d, const string& kode, const Buku& dataBaru);
bool hapusBuku(DaftarBuku& d, const string& kode);
void tampilBuku(const DaftarBuku& d);
Buku* cariKode(DaftarBuku& d, const string& kode);
void cariJudul(const DaftarBuku& d, const string& kata);
void urutkanKode(DaftarBuku& d);
void urutkanJudul(DaftarBuku& d);
void urutkanPopuler(DaftarBuku& d);
int  binarySearchKode(const Buku arr[], int kiri, int kanan, const string& kode);
