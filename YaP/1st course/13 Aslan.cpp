//N13
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct AEROFLOT
{
    char dest[100];  // пункт назначения
    int num;         // номер рейса
    char typ[100];   // тип самолета
};


void sortf(AEROFLOT fl[], int n)  // cортировка до n-го элемента
{
    for(int i=0; i < n - 1; i++)
        for(int j=0; j < n - i - 1; j++)
            if(fl[j].num > fl[j + 1].num)
            {
                AEROFLOT t = fl[j];
                fl[j] = fl[j + 1];
                fl[j + 1] = t;
            }
}


void clearBuffer() // очистка буфера
{
    cin.clear();
    while (cin.get() != '\n');
}


void Menu()
{
    cout << "\n===== МЕНЮ AEROFLOT =====" << endl;
    cout << "1. Добавить новый рейс" << endl;
    cout << "2. Удалить рейс" << endl;
    cout << "3. Поиск рейсов по пункту назначения" << endl;
    cout << "4. Вывести все рейсы" << endl;
    cout << "5. Выход" << endl;
}


void ReadFromFile(AEROFLOT fl[], int& cnt, const char* filename)    // чтение файла
{
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Файл не найден. Будет создан новый." << endl;
        return;
    }

    cnt = 0;
    while(cnt < 70 && file >> fl[cnt].num) {
        file.ignore(); // пропуск пробела
        file.getline(fl[cnt].dest, 100, ',');
        file.getline(fl[cnt].typ, 100);
        cnt++;
    }
    file.close();
    
    sortf(fl, cnt);
    cout << "Загружено " << cnt << " записей из файла." << endl;
}


void WriteToFile(const AEROFLOT fl[], int cnt, const char* filename)    // запись в файл
{
    ofstream file(filename);
    if(!file.is_open()) {
        cout << "Ошибка открытия файла для записи" << endl;
        return;
    }

    for(int i=0; i < cnt; i++)
        file << fl[i].num << " " << fl[i].dest << "," << fl[i].typ << endl;
    
    file.close();
    cout << "Данные сохранены в файл." << endl;
}


void addFlight(AEROFLOT fl[], int& cnt) // добавление рейса
{
    if(cnt >= 70)
    {
        cout << "Достигнут лимит (70 рейсов)" << endl;
        return;
    }

    AEROFLOT newFlight;
    
    cout << "Введите пункт назначения: ";
    cin.getline(newFlight.dest, 100);
    
    cout << "Введите номер рейса: ";
    cin >> newFlight.num;
    clearBuffer();
    
    cout << "Введите тип самолета: ";
    cin.getline(newFlight.typ, 100);
    
    int index = 0;
    
    while((index < cnt) && (fl[index].num < newFlight.num))
        index++;
    
    for(int i = cnt; index < i; i--)
        fl[i] = fl[i-1];
    
    fl[index] = newFlight;

    cnt++;
    cout << "Рейс добавлен" << endl;
}


void delFlight(AEROFLOT fl[], int& cnt)  // удаление рейса
{
    if(cnt == 0) {
        cout << "Список рейсов пуст" << endl;
        return;
    }

    int flnum;
    cout << "Введите номер рейса для удаления: ";
    cin >> flnum;
    clearBuffer();

    int found = -1;
    for(int i = 0; i < cnt; i++)
    {
        if(fl[i].num == flnum)
        {
            found = i;
            break;
        }
    }

    if(found != -1)
    {
        for(int i = found; i < cnt - 1; i++)    // сдвинуть все влево на 1
            fl[i] = fl[i + 1];
        cnt--;
        cout << "Рейс с номером " << flnum << " удален." << endl;
    }
    else
        cout << "Рейса с таким номером не существует." << endl;
}


void searchByDest(const AEROFLOT fl[], int cnt) // поиск
{
    if(cnt == 0)
    {
        cout << "Список рейсов пуст" << endl;
        return;
    }

    char search[100];
    cout << "Введите пункт назначения для поиска: ";
    cin.getline(search, 100);

    int flag = 0;
    cout << "\nНайденные рейсы:" << endl;
    cout << "-----------------------------" << endl;
    
    for(int i=0; i < cnt; i++)
    {
        if(strcmp(fl[i].dest, search) == 0)
        {
            cout << "Номер рейса: " << fl[i].num
                 << ", Тип самолета: " << fl[i].typ << endl;
            flag = 1;
        }
    }

    if(flag == 0)
        cout << "Рейсов в пункт назначения \"" << search << "\" не найдено." << endl;
}

void AllFlights(const AEROFLOT fl[], int cnt)   // вывод всех рейсов
{
    if(cnt == 0)
    {
        cout << "Список рейсов пуст" << endl;
        return;
    }

    cout << "\n===== ВСЕ РЕЙСЫ =====" << endl;
    cout << "----------------------------------------" << endl;
    
    for(int i=0; i < cnt; i++)
    {
        cout << "Рейс №" << fl[i].num << endl;
        cout << "  Пункт назначения: " << fl[i].dest << endl;
        cout << "  Тип самолета: " << fl[i].typ << endl;
        cout << "----------------------------------------" << endl;
    }
    
    cout << "Всего рейсов: " << cnt << endl;
}

// ====================================================================================

int main() {
    AEROFLOT fl[70];
    int flcount = 0,
        choice = 0;
    const char* filename = "aeroflot_data.txt";

    ReadFromFile(fl, flcount, filename);    // попытка чтения файла

    while(choice != 5)
    {
        Menu();
        int flg = 0;
        cout << "Выберите действие: ";
        cin >> choice;
        clearBuffer();

        switch(choice)
        {
            case 1:
                addFlight(fl, flcount);
                WriteToFile(fl, flcount, filename);
                if(!flg)
                    flg = 1;
                break;
            case 2:
                delFlight(fl, flcount);
                WriteToFile(fl, flcount, filename);
                if(!flg)
                    flg = 1;
                break;
            case 3:
                searchByDest(fl, flcount);
                break;
            case 4:
                AllFlights(fl, flcount);
                break;
            case 5:
                if(!flg)
                    WriteToFile(fl, flcount, filename);
                break;
            default:
                cout << "Такого выбора нет. Попробуйте снова." << endl;
        }
    }

    return 0;
}