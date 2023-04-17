#include <iostream>
#include <io.h>
#include <Windows.h>
using namespace std;

const int size = 255;

// для удаления пробела и лишнего слэша в конце строки
void RemoveSpacesAndSlashes(char* str) {
    int index = strlen(str) - 1;
    while (str[index] == ' ' || str[index] == '\\') index--;
    strncpy_s(str, strlen(str)+1, str, index);
    str[index + 1] = '\0';
}

// для показа текущей директории
void ShowCurrentDir(char path[]) {
    printf("%s>", path);
}

// показ всего содержимого текущей директории
bool ShowDir(char path[]) {
    _finddata_t find;
    char pathfind[MAX_PATH];
    strcpy_s(pathfind, path);
    strcat_s(pathfind, "\\*.*");
    char info[MAX_PATH];

    intptr_t result = _findfirst(pathfind, &find);
    system("cls");

    if (result == -1) {
        strcpy(info, "Такой директории нет");
        printf("%s\n", info);
        return false;
    }
    intptr_t flag = result;
    while (flag != -1) {
        if (strcmp(find.name, ".") || strcmp(find.name, "..")) {
            find.attrib& _A_SUBDIR ? strcpy(info, " Каталог ") :
                strcpy(info, " Файл ");
            printf("%30s %10s\n", find.name, info);
        }
        flag = _findnext(result, &find);
    }
    ShowCurrentDir(path);
    _findclose(result);
    return true;
}

int main()
{
    
}
