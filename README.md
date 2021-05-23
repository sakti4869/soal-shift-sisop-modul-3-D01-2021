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
Keverk adalah orang yang cukup ambisius dan terkenal di angkatannya. Sebelum dia menjadi ketua departemen di HMTC, dia pernah mengerjakan suatu proyek dimana keverk tersebut meminta untuk membuat server database buku. Proyek ini diminta agar dapat digunakan oleh pemilik aplikasi dan diharapkan bantuannya dari pengguna aplikasi ini.

Di dalam proyek itu, Keverk diminta:

a. Pada saat client tersambung dengan server, terdapat dua pilihan pertama, yaitu register dan login. Jika memilih register, client akan diminta input id dan passwordnya untuk dikirimkan ke server. User juga dapat melakukan login. Login berhasil jika id dan password yang dikirim dari aplikasi client sesuai dengan list akun yang ada didalam aplikasi server. Sistem ini juga dapat menerima multi-connections. Koneksi terhitung ketika aplikasi client tersambung dengan server. Jika terdapat 2 koneksi atau lebih maka harus menunggu sampai client pertama keluar untuk bisa melakukan login dan mengakses aplikasinya. Keverk menginginkan lokasi penyimpanan id dan password pada file bernama akun.txt dengan format :

akun.txt
``
id:password
id2:password2
``
Jawaban : 
Pada saat penggunaan yang menginginkan multi-connections maka kita membutuhkan thread sebagai alat untuk melakukan aktifitas tersebut. Oleh karena itu disini saya membuat dua buah thread untuk mengakomodasi hal tersebut untuk menyimpan username dan password.
```
//client
int main(int argc, char const *argv[])
{
    pthread_t tid[2];
    int fdc = create_socket();
    //bisa menghandle client banyak
    //minta masukka username
    pthread_create(&(tid[0]), NULL, &cekoutput, (void *) &fdc);
    //minta masukkan email
    pthread_create(&(tid[1]), NULL, &cekinput, (void *) &fdc);
    //joinkan
    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    close(fdc);
    return 0;
}
```
```
//register
void daftar(char *messages, int fd)
{
    char id[300], password[300];
    FILE *fp = fopen("akun.txt", "a+");

    if (validasi(fd, id, password) != 0) {
        if (sudahregister(fp, id)) {
            send(fd, "Username tersebut sudah ada\n", SIZE_BUFFER, 0);
        } else {
            fprintf(fp, "%s:%s\n", id, password);
            send(fd, "Register akun berhasil\n", SIZE_BUFFER, 0);
        }
    }
    fclose(fp);
}

//login
void login(char *messages, int fd)
{
    if (socketawal != -1) {
        send(fd, "Server sedang sibuk. Mohon menunggu\n", SIZE_BUFFER, 0);
        return;
    }
    //buka akun
    char id[300], password[300];
    FILE *fp = fopen("akun.txt", "a+");
    //cek apakah berhasil
    if (validasi(fd, id, password) != 0) {
        if (loginberhasil(fp, id, password)) {
            send(fd, "Login berhasil!\n", SIZE_BUFFER, 0);
            socketawal = fd;
            strcpy(validator[0], id);
            strcpy(validator[1], password);
        } else {
            send(fd, "Username atau password salah!\n", SIZE_BUFFER, 0);
        }
    }
    fclose(fp);
}
```
b. Sistem memiliki sebuah database yang bernama files.tsv. Isi dari files.tsv ini adalah path file saat berada di server, publisher, dan tahun publikasi. Setiap penambahan dan penghapusan file pada folder file yang bernama  FILES pada server akan memengaruhi isi dari files.tsv. Folder FILES otomatis dibuat saat server dijalankan.

Jawaban : 
Setiap memasukkan sesuatu akan dideteksi dan akan dimasukkan ke database yaitu files.tsv disemua fungsi terdapat semua open files.tsv untuk mencatat apakah data tersebut ditambahkan atau dihapus.
```
void add(char *messages, int fd)
{
    char *dirName = "FILES";
    char publisher[300], year[300], client_path[300];
    sleep(0.001);
    if (ambilinput(fd, "Publisher: ", publisher) == 0) return;
    if (ambilinput(fd, "Tahun Publikasi: ", year) == 0) return;
    if (ambilinput(fd, "Filepath: ", client_path) == 0) return;

    FILE *fp = fopen("files.tsv", "a+");
    char *fileName = ceknamafile(client_path);

    if (sudahdownload(fp, fileName)) {
        send(fd, "File yang anda upload sudah ada\n", SIZE_BUFFER, 0);
    } else {
        send(fd, "Memulai mengirimkan file\n", SIZE_BUFFER, 0);
        mkdir(dirName, 0777);
        if (masukkanfile(fd, dirName, fileName) == 0) {
            fprintf(fp, "%s\t%s\t%s\n", client_path, publisher, year);
            printf("File berhasil dikirimkan\n");
            runninglog("add", fileName);
        } else {
            printf("Error occured when receiving file\n");
        }
    }
    fclose(fp);
}
```
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

Jawaban : 
Disini perlu melakukan pengecekkan apakah data tersebut sudah ada atau belum. Apabila data tersebut belum ada maka akan dilakukan input data seperti diabawah ini.
```
void add(char *messages, int fd)
{
    char *dirName = "FILES";
    char publisher[300], year[300], client_path[300];
    sleep(0.001);
    if (ambilinput(fd, "Publisher: ", publisher) == 0) return;
    if (ambilinput(fd, "Tahun Publikasi: ", year) == 0) return;
    if (ambilinput(fd, "Filepath: ", client_path) == 0) return;

    FILE *fp = fopen("files.tsv", "a+");
    char *fileName = ceknamafile(client_path);

    if (sudahdownload(fp, fileName)) {
        send(fd, "File yang anda upload sudah ada\n", SIZE_BUFFER, 0);
    } else {
        send(fd, "Memulai mengirimkan file\n", SIZE_BUFFER, 0);
        mkdir(dirName, 0777);
        if (masukkanfile(fd, dirName, fileName) == 0) {
            fprintf(fp, "%s\t%s\t%s\n", client_path, publisher, year);
            printf("File berhasil dikirimkan\n");
            runninglog("add", fileName);
        } else {
            printf("Error occured when receiving file\n");
        }
    }
    fclose(fp);
}
```
d. Dan client dapat mendownload file yang telah ada dalam folder FILES di server, sehingga sistem harus dapat mengirim file ke client. Server harus melihat dari files.tsv untuk melakukan pengecekan apakah file tersebut valid. Jika tidak valid, maka mengirimkan pesan error balik ke client. Jika berhasil, file akan dikirim dan akan diterima ke client di folder client tersebut. 

Contoh Command client
``download TEMPfile.pdf``

Jawaban : 
Disini saya membuat sebuah fungsi yang berguna untuk melakukan pengecekkan sehingga dibutuhkan pesan error apabila file tersebut tidak ada, dan memberikan peringatan juga agar file tersebut tidak duplikat.
```
void download(char *filename, int fd)
{
    FILE *fp = fopen("files.tsv", "a+");
    if (sudahdownload(fp, filename)) {
        kirim(fd, filename);
    } else {
        send(fd, "File tersebut tidak ada\n", SIZE_BUFFER, 0);
    }
    fclose(fp);
}
```
e. Setelah itu, client juga dapat menghapus file yang tersimpan di server. Akan tetapi, Keverk takut file yang dibuang adalah file yang penting, maka file hanya akan diganti namanya menjadi ‘old-NamaFile.ekstensi’. Ketika file telah diubah namanya, maka row dari file tersebut di file.tsv akan terhapus.

Contoh Command Client:
``delete TEMPfile.pdf``

Jawaban : 
Disini saya membuat sebuah fungsi delete yang berguna untuk melakukan penghapusan data di files.tsv serta menambahkan history di running.log
```
void hapus(char *filename, int fd)
{
    //buka file
    FILE *fp = fopen("files.tsv", "a+");
    char db[300], currFilePath[300], publisher[300], year[300];
    if (sudahdownload(fp, filename)) {
        rewind(fp);
        FILE *tmp_fp = fopen("temp.tsv", "a+");
        //buat sebuah temp supaya pada saat pertukaran data tidak berubah2
        while (fgets(db, SIZE_BUFFER, fp)) {
            sscanf(db, "%s\t%s\t%s", currFilePath, publisher, year);
            if (strcmp(ceknamafile(currFilePath), filename) != 0) { 
                fprintf(tmp_fp, "%s", db);
            }
            memset(db, 0, SIZE_BUFFER);
        }
        fclose(tmp_fp);
        fclose(fp);
        remove("files.tsv");
        rename("temp.tsv", "files.tsv");
        char deletedFileName[300];
        sprintf(deletedFileName, "FILES/%s", filename);
        char newFileName[300];
        sprintf(newFileName, "FILES/old-%s", filename);
        rename(deletedFileName, newFileName);
        send(fd, "File tersebut berhasil dihapus\n", SIZE_BUFFER, 0);
        runninglog("delete", filename);
    } 
    else {
        send(fd, "File gagal didownload\n", SIZE_BUFFER, 0);
        fclose(fp);
    }
}
```
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

Jawaban : 
Disini saya membuat sebuah fungsi yang bertujuan untuk melihat data di files.tsv untuk memastikan data tersebut ada dengan membuat fitur boolean sehingga bisa digunakan didua kondisi. Kondisi see dan find dengan menggunakan strstr
```
void see(char *buf, int fd, bool isFind)
{
    int counter = 0;
    FILE *src = fopen("files.tsv", "r");
    if (!src) {
        write(fd, "Files.tsv not found\n", SIZE_BUFFER);
        return;
    }

    char temp[300 + 85], namafile[300/3], ext[5],
        filepath[300/3], publisher[300/3], year[10];
        
    while (fscanf(src, "%s\t%s\t%s", filepath, publisher, year) != EOF) {
        pemisahfile(filepath, namafile, ext);
        if (isFind && strstr(namafile, buf) == NULL) continue;
        counter++;

        sprintf(temp, 
            "Nama: %s\nPublisher: %s\nTahun publishing: %s\nEkstensi File: %s\nFilepath: %s\n\n",
            namafile, publisher, year, ext, filepath
        );
        write(fd, temp, SIZE_BUFFER);
        sleep(0.001);
    }
    if(counter == 0) {
        if (isFind) write(fd, "perintah tersebut tidak ada di files.tsv\n", SIZE_BUFFER);
        else write(fd, "Data tidak ada di database files.tsv\n", SIZE_BUFFER);
    } 
    fclose(src);
}
```
g. Aplikasi client juga dapat melakukan pencarian dengan memberikan suatu string. Hasilnya adalah semua nama file yang mengandung string tersebut. Format output seperti format output f.

Contoh Client Command:
``find TEMP``

Jawaban : 
Disini saya membuat sekaligus dengan fungsi see untuk upaya tidak doublenya pencarian. Karena disini mengecek data yang dengan menggunakan strstr.
```
void see(char *buf, int fd, bool isFind)
{
    int counter = 0;
    FILE *src = fopen("files.tsv", "r");
    if (!src) {
        write(fd, "Files.tsv not found\n", SIZE_BUFFER);
        return;
    }

    char temp[300 + 85], namafile[300/3], ext[5],
        filepath[300/3], publisher[300/3], year[10];
        
    while (fscanf(src, "%s\t%s\t%s", filepath, publisher, year) != EOF) {
        pemisahfile(filepath, namafile, ext);
        if (isFind && strstr(namafile, buf) == NULL) continue;
        counter++;

        sprintf(temp, 
            "Nama: %s\nPublisher: %s\nTahun publishing: %s\nEkstensi File: %s\nFilepath: %s\n\n",
            namafile, publisher, year, ext, filepath
        );
        write(fd, temp, SIZE_BUFFER);
        sleep(0.001);
    }
    if(counter == 0) {
        if (isFind) write(fd, "perintah tersebut tidak ada di files.tsv\n", SIZE_BUFFER);
        else write(fd, "Data tidak ada di database files.tsv\n", SIZE_BUFFER);
    } 
    fclose(src);
}
```
h. Dikarenakan Keverk waspada dengan pertambahan dan penghapusan file di server, maka Keverk membuat suatu log untuk server yang bernama running.log. Contoh isi dari log ini adalah

running.log
``
Tambah : File1.ektensi (id:pass)
Hapus : File2.ektensi (id:pass)
``

Jawaban : 
Disini saya membuat sebuah fungsi yang bertujuan untuk mengecek apakah ada penambahan atau pengurangan data sehingga fungsi ini dimasukkan kedalam fungsi penambahan dan fungsi pengurangan untuk pengecekkan.
```
void runninglog(char *cmd, char *filename)
{
    FILE *fp = fopen("running.log", "a+");
    cmd = (strcmp(cmd, "add") == 0) ? "Tambah" : "Hapus";
    fprintf(fp, "%s : %s (%s:%s)\n", cmd, filename, validator[0], validator[1]);
    fclose(fp);
}
```
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

Karena nantinya kita memerlukan matrix hasil program ```soal2a.c``` untuk pengerjaan ```soal2b.c```, maka kita gunakan shared memory. Key dari shared memory sendiri bisa diinputkan saat program dijalankan. 
```
int key;
sscanf(argv[1], "%d", &key);
```

Kemudian, kita buat space untuk shared memory dengan key yang kita buat sebelumnya. KIta lakukan juga attach shared memory, agar isi arr3 bisa dimodifikasi dan digunakan program lain.
```
if ((matrixID = shmget(key, 100, IPC_CREAT | 0666)) < 0)
        	printf("smget returned -1\n");
if (!(arr3 = shmat(matrixID, NULL, 0))){
         printf("Process shmat returned NULL\n");
}
```

Selanjutnya, kita perlu menampilkan hasil perkalian matrix 4x3 dan 3x6 yang diinputkan user ke monitor dan menyimpannya langsung ke space arr3.
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

Setelah selesai, kita lakukan detach memory, agar shared memory dapat digunakan program lain.
```
shmdt(arr3);
```

**b.** Membuat program dengan menggunakan matriks output dari program sebelumnya (program soal2a.c) (Catatan!: gunakan shared memory). Kemudian matriks tersebut akan dilakukan perhitungan dengan matrix baru (input user) sebagai berikut contoh perhitungan untuk matriks yang ada. Perhitungannya adalah setiap cel yang berasal dari matriks A menjadi angka untuk faktorial, lalu cel dari matriks B menjadi batas maksimal faktorialnya (dari paling besar ke paling kecil) (Catatan!: gunakan thread untuk perhitungan di setiap cel). 

Ketentuan
```
If a >= b  --> a!/(a-b)!

If b > a   --> a!

If 0       --> 0
```

Pertama, kita lakukan attach shared memory yang berisi hasil matriks dari ```soal2a.c```. Kemudian, kita tampilkan matriks tersebut.
```
int matrixID;
int key;
sscanf(argv[1], "%d", &key);

if ((matrixID = shmget(key, 100, IPC_CREAT | 0666)) < 0) printf("shmget returned -1\n");
if (!(init = shmat(matrixID, NULL, 0))) printf("Process shmat returned NULL\n");

printf("Previous Matrix 4x6:\n");
for(int i=0; i<4; i++){
	for(int j=0; j<6; j++){
		printf("%d ", init[i][j]);
	}
	printf("\n");
}
```

Lalu kita minta input matriks baru 4x6 kepada user.
```
printf("Input Matrix 4x6:\n");
for(int i=0; i<4; i++){
	for(int j=0; j<6; j++){
		scanf("%d", &input[i][j]);
	}
}
printf("\n");
```

Selanjutnya kita definisikan sebuah fungsi yang akan di threading.
```
void *factorial_thread(void *arg){
	pthread_t id = pthread_self();
	for(int i=0; i<4; i++){
		for(int j=0; j<6; j++){
			if(pthread_equal(id, thrid[i])) 
				result[i][j] = factorial(init[i][j], input[i][j]);
		}
	}

}
```

Dan juga fungsi untuk melakukan perhitungan faktorial.
```
ll factorial(int a, int b){
	ll res=1;
	if(!a || !b) res=0;
	else if(a<b) for(int i=1; i<=a; i++) res *= i;
	else for(int i=a; i>a-b; --i) res *= i;
	return res;
}
```

Lalu di fungsi ```main``` dilakukan pembuatan thread.
```
for(int i=0; i<24; i++)
	if(pthread_create(&(thrid[i]), NULL, &factorial_thread, NULL)) 
		printf("Threading Error\n");
for(int i=0; i<24; i++) pthread_join(thrid[i],NULL);
```

Selnajutnya matriks hasil ditampilkan ke monitor, kemudian dilakukan detach shared memory.
```
printf("Resulting Matrix 4x6:\n");
for(int i=0; i<4; i++){
	for(int j=0; j<6; j++){
		printf("%lld ", result[i][j]);
	}
	printf("\n");
}	
printf("\n");
shmdt(init);
```

**c.** Karena takut lag dalam pengerjaannya membantu Loba, Crypto juga membuat program (soal2c.c) untuk mengecek 5 proses teratas apa saja yang memakan resource komputernya dengan command “ps aux | sort -nrk 3,3 | head -5” (Catatan!: Harus menggunakan IPC Pipes)

Pertama, dibuat pipe pertama untuk ```ps aux```.
```
if (pipe(pipe1) == -1) {
    	perror("pipe 1 fail");
    	exit(1);
}
```
Kemudian dilakukan fork untuk exec ```ps aux```.
```
if ((pid = fork()) == -1) {
    	perror("fork 1 failed");
    	exit(1);
} 
else if (pid == 0) exec1();
```

Fungsi exec1() didefinisikan seperti berikut.
```
void exec1() {
  	dup2(pipe1[1], 1);			//input dari stdin, output ke pipe 1
	
  	close(pipe1[0]); close(pipe1[1]);	//menutup bagian pipe yang tidak digunakan

  	execlp("ps", "ps", "aux", NULL);

  	perror("exec ps fail");			//pesan error jika exec fail dan melanjutkan fungsi dibawahnya
  	_exit(1);
}
```

Kemudian kembali lagi ke main, kita buat pipe 2, dan kita lakukan fork.
```
if (pipe(pipe2) == -1) {
    	perror("pipe 2 failed");
    	exit(1);
}
	
if ((pid = fork()) == -1) {
	perror("fork 2 failed");
	exit(1);
} 
else if (pid == 0) exec2();
```

Fungsi exec 2 didefinisikan seperti berikut.
```
void exec2() { 
  	dup2(pipe1[0], 0); //input dari pipe 1
  	dup2(pipe2[1], 1); //output ke pipe 2
	
	//menutup bagian pipe yang tidak digunakan
  	close(pipe1[0]); close(pipe1[1]);
  	close(pipe2[0]); close(pipe2[1]);

  	execlp("sort", "sort", "-nrk", "3,3", NULL);

  	perror("exec sort failed");
 	_exit(1);
}
```

Kemudian kembali lagi ke main, tutup bagian pipe yang sudah tidak digunakan.
```
close(pipe1[0]);
close(pipe1[1]);
```

Kemudian kita buat pipe 3, dan kita lakukan fork.
```
if (pipe(pipe3) == -1) {
    	perror("pipe 3 failed");
    	exit(1);
}
	
if ((pid = fork()) == -1) {
	perror("fork 3 failed");
	exit(1);
} 
else if (pid == 0) exec3();
```

Selanjutnya, exec3 didefinisikan seperti berikut. Hasil akan ditampilkan ke monitor.
```
void exec3() {
	//input dari pipe2, output ke stdout
  	dup2(pipe2[0], 0);
	//menutup pipe yang tidak digunakan
  	close(pipe2[0]); close(pipe2[1]);

  	execlp("head", "head", "-5", NULL);
  	perror("EXEC HEAD FAIL");
  	_exit(1);
}
```

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
