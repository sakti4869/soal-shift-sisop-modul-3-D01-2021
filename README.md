# soal-shift-sisop-modul-3-D01-2021

##  Daftar Isi ##
   - [Anggota Kelompok](https://github.com/sakti4869/soal-shift-sisop-modul-3-D01-2021/blob/main/README.md#anggota-kelompok)
   - [Soal 1](https://github.com/sakti4869/soal-shift-sisop-modul-3-D01-2021/blob/main/README.md#soal-1)
      - [1a]
      - [1b]
      - [1c]
      - [1d]
      - [1e]
      - [1f]
      - [1g]
      - [1h]
   - [Soal 2](https://github.com/sakti4869/soal-shift-sisop-modul-3-D01-2021/blob/main/README.md#soal-2)
      - [2a]
      - [2b]
      - [2c]
   - [Soal 3](https://github.com/sakti4869/soal-shift-sisop-modul-3-D01-2021/blob/main/README.md#soal-3)
      - [3a]
      - [3b]
      - [3c]
      - [3d]
      - [3e]

## Anggota Kelompok ##

Khaela Fortunela 05111940000057

M Haikal Aria Sakti 05111940000088

David Ralphwaldo M 05111940000190

## Soal 1 ##
a. Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. Koneksi terhitung ketika aplikasi client tersambung dengan server. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Keverk menginginkan lokasi penyimpanan id dan password pada file bernama akun.txt dengan format :

akun.txt
``
id:password
id2:password2
``

b. Sistem memiliki sebuah database yang bernama files.tsv. Isi dari files.tsv ini adalah path file saat berada di server, publisher, dan tahun publikasi. Setiap penambahan dan penghapusan file pada folder file yang bernama  FILES pada server akan memengaruhi isi dari files.tsv. Folder FILES otomatis dibuat saat server dijalankan.

c. Tidak hanya itu, Keverk juga diminta membuat fitur agar client dapat menambah file baru ke dalam server. Direktori FILES memiliki struktur direktori di bawah ini : 

Direktori FILES 
``
File1.ekstensi
File2.ekstensi
`` 
Pertama client mengirimkan input ke server dengan struktur sebagai berikut :

Contoh Command Client :
``add``

Output Client Console:
``
Publisher:
Tahun Publikasi:
Filepath:
``
Kemudian, dari aplikasi client akan dimasukan data buku tersebut (perlu diingat bahwa Filepath ini merupakan path file yang akan dikirim ke server). Lalu client nanti akan melakukan pengiriman file ke aplikasi server dengan menggunakan socket. Ketika file diterima di server, maka row dari files.tsv akan bertambah sesuai dengan data terbaru yang ditambahkan.

d. Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client di folder client tersebut. 

Contoh Command client
``download TEMPfile.pdf``

e. Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti namanya menjadi ‘old-NamaFile.ekstensi’. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.

Contoh Command Client:
``delete TEMPfile.pdf``

f.Client dapat melihat semua isi files.tsv dengan memanggil suatu perintah yang bernama see. Output dari perintah tersebut keluar dengan format. 

Contoh Command Client :
``see``

Contoh Format Output pada Client:
``
Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 
``
``
Nama:
Publisher:
Tahun publishing:
Ekstensi File : 
Filepath : 
``

g. Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti format output f.

Contoh Client Command:
``find TEMP``

h. Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama running.log. Contoh isi dari log ini adalah

running.log
``
Tambah : File1.ektensi (id:pass)
Hapus : File2.ektensi (id:pass)
``

## Soal 2 ##

Crypto (kamu) adalah teman Loba. Suatu pagi, Crypto melihat Loba yang sedang kewalahan mengerjakan tugas dari bosnya. Karena Crypto adalah orang yang sangat menyukai tantangan, dia ingin membantu Loba mengerjakan tugasnya. Detil dari tugas tersebut adalah:

**a.** Membuat program perkalian matrix (4x3 dengan 3x6) dan menampilkan hasilnya. Matriks nantinya akan berisi angka 1-20 (tidak perlu dibuat filter angka).

Pertama, kita perlu menuliskan kode untuk menerima input array 4x3 dan 3x6 dari pengguna. Hal ini bisa dilakukan dengan menggunakan loop dan scanf.
```
   int arr1[4][3];
   int arr2[3][6];
   
	printf("Matrix 4x3:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<3; j++){
			scanf("%d", &arr1[i][j]);
		}
	}
   
	printf("\nMatrix 3x6:\n");
	for(int i=0; i<3; i++){
		for(int j=0; j<6; j++){
			scanf("%d", &arr2[i][j]);
		}
	}
```

Selanjutnya, kita perlu menampilkan hasil perkalian matrix 4x3 dan 3x6 yang diinputkan user ke monitor.
```
   printf("\nResulting Matrix 4x6:\n");
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			arr3[i][j]=0;
			for(int k=0; k<3; k++){ 
				arr3[i][j] += arr1[i][k] * arr2[k][j];
			}
			printf("%d ", arr3[i][j]);
		}
		printf("\n");
	}
```

Karena nantinya kita memerlukan matrix hasil program ```soal2a.c``` untuk pengerjaan ```soal2b.c```, maka kita gunakan shared memory. Pertama, kita buat key untuk mengakses shared memory tersebut.
```
key_t key = ftok(".", 'b');
```

Selanjutnya, key disimpan di sebuah file ```key.txt``` agar bisa diakses program ```soal2b.c```.
```
FILE *keyid = fopen("key.txt", "w");
fprintf(keyid, "%d", key);
fclose(keyid);
```

Kemudian, kita buat space untuk shared memory dengan key yang kita buat sebelumnya. KIta lakukan juga attach shared memory, agar isi arr3 bisa dimodifikasi dan digunakan program lain.
```
if ((matrixID = shmget(key, 100, IPC_CREAT | 0666)) < 0)
        	printf("smget returned -1\n");
if (!(arr3 = shmat(matrixID, NULL, 0))){
         printf("Process shmat returned NULL\n");
}
```

**b.** Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang ada. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya (dari paling besar ke paling kecil) (Catatan!: gunakan thread untuk perhitungan di setiap cel). 

Ketentuan		
If a >= b  --> a!/(a-b)!

If b > a   --> a!

If 0       --> 0

**c.** Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” (Catatan!: Harus menggunakan IPC Pipes)

## Soal 3 ##

Seorang mahasiswa bernama Alex sedang mengalami masa gabut. Di saat masa gabutnya, ia memikirkan untuk merapikan sejumlah file yang ada di laptopnya. Karena jumlah filenya terlalu banyak, Alex meminta saran ke Ayub. Ayub menyarankan untuk membuat sebuah program C agar file-file dapat dikategorikan. Program ini akan memindahkan file sesuai ekstensinya ke dalam folder sesuai ekstensinya yang folder hasilnya terdapat di working directory ketika program kategori tersebut dijalankan.

Contoh apabila program dijalankan:

```
# Program soal3 terletak di /home/izone/soal3
$ ./soal3 -f path/to/file1.jpg path/to/file2.c path/to/file3.zip
#Hasilnya adalah sebagai berikut
/home/izone
|-jpg
  |--file1.jpg
|-c
  |--file2.c
|-zip
  |--file3.zip
```

**(a)** Program menerima opsi -f seperti contoh di atas, jadi pengguna bisa menambahkan argumen file yang bisa dikategorikan sebanyak yang diinginkan oleh pengguna.

Output yang dikeluarkan adalah seperti ini :

```
File 1 : Berhasil Dikategorikan (jika berhasil)
File 2 : Sad, gagal :( (jika gagal)
File 3 : Berhasil Dikategorikan
```

![Soal3A1](https://i.postimg.cc/MGRMrWKV/1.png)
![Soal3A2](https://i.postimg.cc/vTSZZjZG/a0.png)
![Soal3A3](https://i.postimg.cc/XqZ0Qvn0/a1.png)
![Soal3A4](https://i.postimg.cc/QtT2TymX/a2.png)

### Cara Pengerjaan ###

1. Looping untuk memproses semua file yang ada dalam array argv.
2. Untuk setiap file dibuat sebuah thread yang disimpan dalam array fileThread dan mempassing fungsi moveFile dan nama filenya sebagai argumen untuk fungsi moveFile.
3. Setelah dibuat sebanyak FILES_MAX, program akan menunggu agar semua thread selesai, kemudian melakukan join thread.
4. Dalam fungsi moveFile, pertama dicek apabila filenya ada atau tidak, jika tidak ada maka gagal.
5. Kemudian fungsi mengecek apabila file tersebut merupakan file biasa, file hidden, atau file dengan tipe yang unknown.
6. Jika filenya merupakan file biasa, maka akan dibuatkan folder sesuai ekstensinya, jika filenya hidden maka akan dibuatkan folder Hidden, jika filenya Unknown dibuatkan folder Unknown.
7. Setelah itu file dipindahkan.

### Kendala ###

Tidak ada kendala.

**(b)** Program juga dapat menerima opsi -d untuk melakukan pengkategorian pada suatu directory. Namun pada opsi -d ini, user hanya bisa memasukkan input 1 directory saja, tidak seperti file yang bebas menginput file sebanyak mungkin.

Contohnya adalah seperti ini:

```
$ ./soal3 -d /path/to/directory/
```

Perintah di atas akan mengkategorikan file di /path/to/directory, lalu hasilnya akan disimpan di working directory dimana program C tersebut berjalan (hasil kategori filenya bukan di /path/to/directory).

Output yang dikeluarkan adalah seperti ini :

```
Jika berhasil, print “Direktori sukses disimpan!”
Jika gagal, print “Yah, gagal disimpan :(“
```

![Soal3B1](https://i.postimg.cc/mgZhyQ0x/2.png)
![Soal3B2](https://i.postimg.cc/TY3XkCYc/b0.png)
![Soal3B3](https://i.postimg.cc/fygqq7BH/b1.png)

### Cara Pengerjaan ###

1. Membaca isi direktori yang diberikan sebagai argumen ke fungsi moveDir.
2. Memindahkan semua file yang ada dalam direktori tersebut dengan memanggil fungsi moveFile dan mempassing path dan nama file tersebut sebagai argumennya.
3. Setelah semua file dalam direktori dipindahkan, maka fungsi akan memanggil moveDir dengan argumen path direktori lain.

### Kendala ###

Tidak ada kendala.

**(c)** Selain menerima opsi-opsi di atas, program ini menerima opsi \*, contohnya ada di bawah ini:

```
$ ./soal3 \*
```

Opsi ini akan mengkategorikan seluruh file yang ada di working directory ketika
menjalankan program C tersebut.

![Soal3C1](https://i.postimg.cc/mgZhyQ0x/2.png)

### Cara Pengerjaan ###

1. Hampir sama dengan no b, hanya saja ketika awal dipanggil mempassing path "." untuk fungsi moveDir.

### Kendala ###

Tidak ada kendala.

**(d)** Semua file harus berada di dalam folder, jika terdapat file yang tidak memiliki ekstensi, file disimpan dalam folder “Unknown”. Jika file hidden, masuk folder “Hidden”.

![Soal3D1](https://i.postimg.cc/vTSZZjZG/a0.png)
![Soal3D2](https://i.postimg.cc/LXxxhBKH/hidden.png)

### Cara Pengerjaan ###

1. Sudah dikerjakan di no a pada fungsi moveFile.

### Kendala ###

Tidak ada kendala.

**(e)** Setiap 1 file yang dikategorikan dioperasikan oleh 1 thread agar bisa berjalan secara paralel sehingga proses kategori bisa berjalan lebih cepat.

![Soal3E1](https://i.postimg.cc/g2bHzBXV/pakethread1.png)
![Soal3E2](https://i.postimg.cc/fygqq7BH/b1.png)

### Cara Pengerjaan ###

1. Sudah dikerjakan di no a dan b.

### Kendala ###

Tidak ada kendala.
