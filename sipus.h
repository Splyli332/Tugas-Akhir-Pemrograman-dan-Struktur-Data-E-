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

// ---- Modul Anggota (Patricia) ----
void inisialisasi(DaftarAnggota& d, int kapasitasAwal);
void bebaskan(DaftarAnggota& d);
bool tambahAnggota(DaftarAnggota& d, const Anggota& a);
bool ubahAnggota(DaftarAnggota& d, const string& id, const Anggota& dataBaru);
void tampilAnggota(const DaftarAnggota& d);
Anggota* cariAnggota(DaftarAnggota& d, const string& id);

// ---- Modul Transaksi & Laporan (Patricia) ----
void inisialisasi(DaftarTransaksi& d, int kapasitasAwal);
void bebaskan(DaftarTransaksi& d);
bool pinjamBuku(DaftarTransaksi& t, DaftarBuku& b, DaftarAnggota& a,
                const string& idAg, const string& kodeBk, const Tanggal& tgl);
bool kembalikanBuku(DaftarTransaksi& t, DaftarBuku& b, DaftarAnggota& a,
                    int nomor, const Tanggal& tgl);
int  selisihHari(const Tanggal& awal, const Tanggal& akhir);
int  totalDendaRekursif(const Transaksi arr[], int n);
void riwayatAnggotaRekursif(const Transaksi arr[], int n, const string& idAg);
void isiRekap(const DaftarTransaksi& t, const DaftarBuku& b, int rekap[][JML_BULAN]);
void tampilRekap(const int rekap[][JML_BULAN], const string namaKategori[]);

#endif
