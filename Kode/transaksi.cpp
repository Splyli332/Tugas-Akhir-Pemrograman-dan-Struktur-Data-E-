#include "sipus.h"
#include <iostream>
#include <iomanip>

using namespace std;

void inisialisasi(DaftarTransaksi& d, int kapasitasAwal) {
    d.kapasitas = kapasitasAwal;
    d.n = 0;
    d.data = new Transaksi[d.kapasitas];
}

void bebaskan(DaftarTransaksi& d) {
    delete[] d.data;
    d.data = nullptr;
    d.n = 0;
    d.kapasitas = 0;
}

static void perbesarKapasitas(DaftarTransaksi& d) {
    int kapBaru = (d.kapasitas == 0) ? 2 : d.kapasitas * 2;
    Transaksi* temp = new Transaksi[kapBaru];
    for (int i = 0; i < d.n; i++) {
        temp[i] = d.data[i];
    }
    delete[] d.data;
    d.data = temp;
    d.kapasitas = kapBaru;
}

// Konversi tanggal sederhana ke jumlah hari absolut (asumsi 1 bulan = 30 hari, 1 tahun = 365 hari untuk simulasi standar)
static long toHari(const Tanggal& t) {
    return t.tahun * 365L + t.bulan * 30L + t.hari;
}

int selisihHari(const Tanggal& awal, const Tanggal& akhir) {
    long diff = toHari(akhir) - toHari(awal);
    return (diff > 0) ? static_cast<int>(diff) : 0;
}

bool pinjamBuku(DaftarTransaksi& t, DaftarBuku& b, DaftarAnggota& a,
                const string& idAg, const string& kodeBk, const Tanggal& tgl) {
    Anggota* ag = cariAnggota(a, idAg);
    Buku* bk = cariKode(b, kodeBk);

    if (!ag || !bk) return false;                    // Anggota/buku tidak ada
    if (bk->stok <= 0) return false;                 // Stok habis
    if (ag->sedangPinjam >= MAKS_PINJAM) return false; // Batas maks 3 buku

    if (t.n == t.kapasitas) {
        perbesarKapasitas(t);
    }

    Transaksi tr;
    tr.nomor = t.n + 1;
    tr.idAnggota = idAg;
    tr.kodeBuku = kodeBk;
    tr.tglPinjam = tgl;
    tr.tglKembali = {0, 0, 0};
    tr.selesai = false;
    tr.denda = 0;

    t.data[t.n++] = tr;
    bk->stok--;
    bk->totalDipinjam++;
    ag->sedangPinjam++;

    return true;
}

bool kembalikanBuku(DaftarTransaksi& t, DaftarBuku& b, DaftarAnggota& a,
                    int nomor, const Tanggal& tgl) {
    for (int i = 0; i < t.n; i++) {
        if (t.data[i].nomor == nomor && !t.data[i].selesai) {
            t.data[i].tglKembali = tgl;
            t.data[i].selesai = true;

            int lama = selisihHari(t.data[i].tglPinjam, tgl);
            int telat = (lama > 7) ? (lama - 7) : 0;
            t.data[i].denda = telat * DENDA_HARIAN;

            Buku* bk = cariKode(b, t.data[i].kodeBuku);
            Anggota* ag = cariAnggota(a, t.data[i].idAnggota);
            if (bk) bk->stok++;
            if (ag && ag->sedangPinjam > 0) ag->sedangPinjam--;

            return true;
        }
    }
    return false;
}

// Fungsi rekursif menghitung total denda seluruh transaksi (F8)
int totalDendaRekursif(const Transaksi arr[], int n) {
    if (n <= 0) return 0;
    return arr[n - 1].denda + totalDendaRekursif(arr, n - 1);
}

// Fungsi rekursif menampilkan riwayat transaksi anggota tertentu (F8)
void riwayatAnggotaRekursif(const Transaksi arr[], int n, const string& idAg) {
    if (n <= 0) return;
    riwayatAnggotaRekursif(arr, n - 1, idAg);
    if (arr[n - 1].idAnggota == idAg) {
        cout << "No: " << arr[n - 1].nomor << " | Buku: " << arr[n - 1].kodeBuku
             << " | Status: " << (arr[n - 1].selesai ? "Kembali" : "Dipinjam")
             << " | Denda: Rp" << arr[n - 1].denda << endl;
    }
}

// Laporan rekap peminjaman per kategori x bulan (F7)
void isiRekap(const DaftarTransaksi& t, const DaftarBuku& b, int rekap[][JML_BULAN]) {
    for (int i = 0; i < JML_KATEGORI; i++)
        for (int j = 0; j < JML_BULAN; j++)
            rekap[i][j] = 0;

    for (int i = 0; i < t.n; i++) {
        int bulanIdx = t.data[i].tglPinjam.bulan - 1;
        if (bulanIdx >= 0 && bulanIdx < JML_BULAN) {
            // Cari kategori buku
            int kat = -1;
            for (int k = 0; k < b.n; k++) {
                if (b.data[k].kode == t.data[i].kodeBuku) {
                    kat = b.data[k].kategori;
                    break;
                }
            }
            if (kat >= 0 && kat < JML_KATEGORI) {
                rekap[kat][bulanIdx]++;
            }
        }
    }
}

void tampilRekap(const int rekap[][JML_BULAN], const string namaKategori[]) {
    const char* namaBulan[12] = {"Jan","Feb","Mar","Apr","Mei","Jun","Jul","Agu","Sep","Okt","Nov","Des"};
    cout << left << setw(15) << "Kategori";
    for (int j = 0; j < JML_BULAN; j++) cout << setw(4) << namaBulan[j];
    cout << setw(6) << "Total" << endl;

    int totalKolom[JML_BULAN] = {0};
    int grandTotal = 0, maxKatIdx = 0, maxKatVal = -1;

    for (int i = 0; i < JML_KATEGORI; i++) {
        int totalBaris = 0;
        cout << left << setw(15) << namaKategori[i];
        for (int j = 0; j < JML_BULAN; j++) {
            cout << setw(4) << rekap[i][j];
            totalBaris += rekap[i][j];
            totalKolom[j] += rekap[i][j];
        }
        cout << setw(6) << totalBaris << endl;
        grandTotal += totalBaris;
        if (totalBaris > maxKatVal) {
            maxKatVal = totalBaris;
            maxKatIdx = i;
        }
    }

    cout << left << setw(15) << "Total";
    for (int j = 0; j < JML_BULAN; j++) cout << setw(4) << totalKolom[j];
    cout << setw(6) << grandTotal << endl;
    cout << ">> Kategori terpopuler: " << namaKategori[maxKatIdx] << endl;
}
