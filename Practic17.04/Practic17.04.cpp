#include <iostream>
#include <Windows.h>

#include <stdio.h>
// fopen_s(FILE* file, const char* filename, const char* mode);
	// r, w, a
	// rb, wb, ab
// fclose(FILE* file); EOF - возвращает в случае ошибки

// fgets(char* string, int n, FILE* file);
// fputs(const char* string, FILE* file);

// fread(void* buffer, size_t size, size_t count, FILE* file);
// fwrite(const void* buffer, size_t size, size_t count, FILE* file);

// int _fileno(FILE* file);
// int fseek(FILE* file, int offset [, int whence])
	// SEEK_SET(0)
	// SEEK_CUR(1)
	// SEEK_END(2)

// rename(char* oldname, char* newname);
// remove(const char* filename);

#include <io.h>
// int _access(const char* path, int mode)
	// 00
	// 02
	// 04
	// 06

// long _fileLength(int handle)
// 
	//#include <sys/locking.h>
// int _locking(int handle, int mode, long nbytes)
	// _LK_LOCK _LK_RCLK
	// _LK_NBLCK _LK_NBRLCK
	// _LK_UNLCK

// _findfirst(char* path, _finddata_t* fileinfo)
	// attrib
		// _A_NORMAL
		// _A_RDONLY
		// _A_HIDDEN
		// _A_SYSTEM
		// _A_SUBDIR
		// _A_ARCH
	// time_access
	// time_write
	// size
	// name

// _findnext(long done, _finddata_t* fileinfo)
// _findclose(long done)


using namespace std;

void RussianMessage(const char* str) {
	char message[100];
	CharToOemA(str, message);
	cout << message;
}

bool CopyFiles(char* source, char* destination) {
	const int size = 65536;
	FILE* src, * dest;
	if (fopen_s(&src, source, "rb")) return false;
	size_t handle = _fileno(src);

	char* data = new char[size];

	if (fopen_s(&dest, destination, "wb")) return false;
	size_t realsize;
	while (!feof(src)) {
		realsize = fread(data, sizeof(char), size, src);
		fwrite(data, sizeof(char), realsize, dest);
	}
	fclose(src);
	fclose(dest);
	return true;
}
// --------------------------------------------------------------- //
void RenameFile(); // переименование файла
void RemoveFile(); // удаление файла
void Dir(); // поиск файла
// --------------------------------------------------------------- //
#include <direct.h>
// int _mkdir(const char* dirname);
// int _rmdir(const char* dirname);

void RenameDir(); // переименование папки
void RemoveDir(); // удаление папки
void CreateDir(); // создание папки

void main()
{
	/*char source[_MAX_PATH];
	char destination[_MAX_PATH];
	char answer[20];

	RussianMessage("\nвведите путь и название копируемого файла\n");
	cin.getline(source, _MAX_PATH);

	if (_access(source, 00) == -1)
	{
		RussianMessage("\nУказанный файл не существет\n");
		return;
	}

	RussianMessage("\nвведите путь и название нового файла\n");
	cin.getline(destination, _MAX_PATH);
	if (_access(destination, 00) == 0)
	{
		RussianMessage("\nТакой файл уже существует. Перезаписать? (1- Да/2 - Нет)\n");
		cin.getline(answer, 20);
		if (!strcmp(answer, "2"))
		{
			RussianMessage("\nОтмена операции\n");
			return;
		}
		else if (strcmp(answer, "1"))
		{
			RussianMessage("\nНеправильный ввод\n");
			return;
		}

		if (_access(destination, 02) == -1) {
			RussianMessage("\nНет доступа к записи\n");
			return;
		}
	}

	if (!CopyFiles(source, destination)) {
		RussianMessage("\nОшибка при работе с файлом\n");
	}*/

	cout << "Please, select number...\n";
	char ch;
	do {
		cout << "1 - Rename\n"
			<< "2 - Remove\n"
			<< "3 - Search file\n"
			<< "0 - Exit\n\n-> "; cin >> ch;

		switch (ch)
		{
		case '1':
			//RenameFile();
			RenameDir();
			break;
		case '2':
			//RemoveFile();
			RemoveDir();
			break;
		case '3':
			//Dir();
			CreateDir();
			break;
		}
	} while(ch != '0');
}

void RenameFile() {
	char oldName[50], newName[50];

	cout << "Enter old name -> "; cin >> oldName;
	cout << "Enter new name -> "; cin >> newName;

	if (rename(oldName, newName) != 0)
		cout << "Error rename\n\n";
	else
		cout << "Ok...\n\n";
}
void RemoveFile() {
	char name[50];
	cout << "Enter name -> "; cin >> name;

	if (remove(name) != 0)
		cout << "Error remove\n\n";
	else
		cout << "Ok...\n\n";
}
void Dir() {
	char path[70];
	cout << "Enter full path (Example, C:\\) -> "; cin >> path;

	char mask[15];
	cout << "Enter mask (example, *.* or *.txt) -> "; cin >> mask;

	strcat_s(path, mask);
	_finddata_t* fileinfo = new _finddata_t;
	intptr_t done = _findfirst(path, fileinfo);
	int count = 0;
	intptr_t MayWeWork = done;

	while (MayWeWork != -1) {
		count++;
		cout << fileinfo->name << "\n";
		MayWeWork = _findnext(done, fileinfo);
	}

	cout << "Count file(s) = " << count << endl;

	_findclose(done);
	delete fileinfo;
}


void RenameDir(){
	char oldName[50], newName[50];

	cout << "Enter old name -> "; cin >> oldName;
	cout << "Enter new name -> "; cin >> newName;

	if (rename(oldName, newName) != 0)
		cout << "Error rename\n\n";
	else
		cout << "Ok...\n\n";
}
void RemoveDir(){
	char name[50];
	cout << "Enter name -> "; cin >> name;

	if (_rmdir(name) == -1)
		cout << "Error remove\n";
	else
		cout << "Ok...\n";
}
void CreateDir(){
	char name[50];
	cout << "Enter name -> "; cin >> name;

	if (_mkdir(name) == -1)
		cout << "Error create\n";
	else
		cout << "Ok...\n";
}

