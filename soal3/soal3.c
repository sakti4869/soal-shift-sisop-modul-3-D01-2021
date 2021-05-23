#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <ctype.h>

#define FILES_MAX 1000 // Jumlah thread buat proses file max

void* moveFile(void* arg);
void* moveDir(void* arg);
int isDirectory(const char* );

int berhasil = 1; // Nentuin berhasil atau enggak
int mode = 0; // Mode proses file

pthread_t fileThread[FILES_MAX]; // Thread buat proses file
int fileIndex = 0;

int main(int argc, char ** argv) {
	if (argc < 2) {
		printf("Kurang argumen!\n");

		return 1;
	}

	if (!strcmp(argv[1], "-f")) {
		if (argc < 3) {
			printf("Kurang argumen!\n");
			return 1;
		}
	}

	if (!strcmp(argv[1], "-d")) {
		if (argc < 3) {
			printf("Kurang argumen!\n");
			return 1;
		}

		mode = 1;
	}

	if (!strcmp(argv[1], "*")) {
		mode = 2;
	}

	if (mode == 0) { // Mode file
		int i;
		int fileCount = argc - 2; // ./soal3 -f gak dihitung

		for (i = 0; i < fileCount; i++) {
			pthread_create(&fileThread[fileIndex], NULL, moveFile, (void *) argv[argc - 1 - i]);
			fileIndex++;

			if (fileIndex == FILES_MAX) {
				int j;
				for (j = 0; j < fileIndex; j++)
					pthread_join(fileThread[j], NULL);

				fileIndex = 0;
			}
		}

		for (i = 0; i < fileIndex; i++) {
			pthread_join(fileThread[i], NULL);
		}
	} else { // Mode direktori
		// Pindahin isi direktori

		if (mode == 1)
			moveDir((void* ) argv[2]); // kalo pake ./soal3 -d
		else
			moveDir((void* ) "."); // kalo pake ./soal3 \*

		// Output

		if (berhasil)
			printf("Direktori sukses disimpan!\n");
		else
			printf("Yah, gagal disimpan :(\n");
	}

	return 0;
}

void* moveFile(void* arg)
{
	// Get file name

	char* fileName = (char *) arg;

	// Cek filenya ada atau gak

	if (access(fileName, F_OK) != 0) {
		if (mode == 0) {
			printf("%s : Sad, gagal :(\n", fileName);
			berhasil = 0;
		}

		return NULL;
	}

	// File name tanpa path

	char* fileNameNoPath = (char* ) arg;
	char* temp = fileNameNoPath;

	while (1) { // Skip semua tanda /
		if (*temp == '\0') break;

		if (*temp == '/')
			fileNameNoPath = temp + 1;

		temp++;
	}

	// Check tipe file

	int tipeFile = 0; // 0 - File biasa, 1 - File hidden, 2 - File unknown

	if (fileNameNoPath[0] == '.') // Check kalo filenya hidden
		tipeFile = 1;

	if (strchr(fileNameNoPath, '.') == NULL) // Check kalo filenya unknown
		tipeFile = 2;

	// Buat folder tergantung tipe filenya terus pindahin filenya

	if (tipeFile == 0) { // Kalo filenya file biasa
		// Cek ekstensi filenya

		char fileExt[20];
		strcpy(fileExt, strchr(fileNameNoPath, '.') + 1);

		// Buat ekstensi file case - insensitive

		int i;
		for (i = 0; i < strlen(fileExt); i++)
			fileExt[i] = tolower(fileExt[i]);

		if (access(fileExt, F_OK) != 0) // Directory blom ada
			if (mkdir(fileExt, 0777) != 0) { // Kalo gagal buat direktori
				if (mode == 0) printf("%s : Sad, gagal :(\n", fileName);
				berhasil = 0;

				return NULL;
			}

		// File name dengan path baru

		char fileNameNewPath[200]; // Nama file dengan folder baru
		strcpy(fileNameNewPath, fileExt);
		strcat(fileNameNewPath, "/");
		strcat(fileNameNewPath, fileNameNoPath);

		if (rename(fileName, fileNameNewPath) == 0)
			if (mode == 0) printf("%s : Berhasil Dikategorikan\n", fileName);
		else {
			if (mode == 0) printf("%s : Sad, gagal :(\n", fileName);
			return NULL;
		}
	}

	if (tipeFile == 1) { // File hidden
		if (access("Hidden", F_OK) != 0) // Direktori belom ada
			if (mkdir("Hidden", 0777) != 0) { // Gagal buat direktori
				if (mode == 0) printf("%s : Sad, gagal :(\n", fileName);
				berhasil = 0;

				return NULL;
			}

		// File name dengan path baru

		char fileNameNewPath[200]; // Nama file dengan folder baru
		strcpy(fileNameNewPath, "Hidden/");
		strcat(fileNameNewPath, fileNameNoPath + 1); // Skip dot diawal biar gak hidden

		if (rename(fileName, fileNameNewPath) == 0)
			if (mode == 0) printf("%s : Berhasil Dikategorikan\n", fileName);
		else {
			if (mode == 0) printf("%s : Sad, gagal :(\n", fileName);
			return NULL;
		}
	}

	if (tipeFile == 2) { // File unknown
		if (access("Unknown", F_OK) != 0) // Direktori blom ada
			if (mkdir("Unknown", 0777) != 0) { // Gagal buat direktori
				if (mode == 0) printf("%s : Sad, gagal :(\n", fileName);
				berhasil = 0;

				return NULL;
			}

		// File name dengan path baru

		char fileNameNewPath[200]; // Nama file dengan folder baru
		strcpy(fileNameNewPath, "Unknown/");
		strcat(fileNameNewPath, fileNameNoPath);

		if (rename(fileName, fileNameNewPath) == 0)
			if (mode == 0) printf("%s : Berhasil Dikategorikan\n", fileName);
		else {
			if (mode == 0) printf("%s : Sad, gagal :(\n", fileName);
			return NULL;
		}
	}
}

void* moveDir(void* arg) {
	char* path = (char* ) arg;

	DIR* dir; // Buat buka direktori
	struct dirent* dent; // Buat baca isi direktori

	dir = opendir(path); // Baca directorynya

	if (!dir) { // Directory gak bisa dibaca
		berhasil = 0;

		return NULL;
	}

	// Cek semua direktori dulu baru nanti kategoriin filenya

	char fileWithPath[200]; // Nama file tambah pathnya

	while ((dent = readdir(dir)) != NULL) {
		if (strcmp(dent->d_name, "..") && strcmp(dent->d_name, ".")) {
			strcpy(fileWithPath, path);
			strcat(fileWithPath, "/");
			strcat(fileWithPath, dent->d_name);

			if (isDirectory(fileWithPath)) { // Kalau direktori
				moveDir((char* ) fileWithPath); // Masuk direktorinya terus proses filenya
			}
		}
	}

	char fileNameList[FILES_MAX][200]; // Nama - nama file buat dikategorikan
	int fileCount = 0; // Jumlah file bukan direktori
	int error;

	seekdir(dir, 0);

	while ((dent = readdir(dir)) != NULL) {
		if (strcmp(dent->d_name, "..") && strcmp(dent->d_name, ".")) {
			strcpy(fileWithPath, path);
			strcat(fileWithPath, "/");
			strcat(fileWithPath, dent->d_name);

			if (!isDirectory(fileWithPath)) {
				strcpy(fileNameList[fileIndex], fileWithPath); // Simpen nama file
				fileIndex++;
			}
		}

		if (fileIndex == FILES_MAX) { // Kalau jumlah file dah mencapai limit
			int j;
			for (j = 0; j < fileIndex; j++) {
				error = pthread_create(&fileThread[j], NULL, moveFile, (void* ) fileNameList[j]);
				if (error) berhasil = 0;
			}

			for (j = 0; j < fileIndex; j++) { // Join semua thread
				pthread_join(fileThread[j], NULL);
			}

			fileIndex = 0;
		}
	}

	if (fileIndex) { // Kalau masih ada file yang belom dikategorikan
		int j;
		for (j = 0; j < fileIndex; j++) {
			error = pthread_create(&fileThread[j], NULL, moveFile, (void* ) fileNameList[j]);
			if (error) berhasil = 0;
		}

		for (j = 0; j < fileIndex; j++) {
			pthread_join(fileThread[j], NULL);
		}
	}

	// Close directorynya

	closedir(dir);
}

int isDirectory(const char* path) { // Buat ngecek file directory atau bukan
	struct stat checkDir;
	if (stat(path, &checkDir) != 0) return 0;
	return S_ISDIR(checkDir.st_mode);
}
