int main() {
     DaftarBuku db;
    inisialisasi(db, 2);

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