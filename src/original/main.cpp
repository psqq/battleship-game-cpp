//#include "pch.h"
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <time.h>
#include <windows.h>
#pragma warning(disable : 4996)
using namespace std;



// Все массивы созданы размером 12 х 12 ячеек. Хотя работа происходит только с участком 10х10. Это сделано для того, что бы программа не заступала на поля с противоположной стороны.
// Массив больших размеров специально заполнен 0, что бы при выходе за границы массива, программа видела только 0.

void Print(int mas[12][12]); // Функция печати поля с кораблями
void ARastan(int mas[12][12]); // Функция Автоматической расстановки
void RRastan(int mas[12][12]); // Функция ручной расстановки
int Perevod(char a);  //  Функция перевода букв в цифры

int main()

{

    RECT lpRectToolBar;
    HWND console = GetConsoleWindow();
    RECT ConsoleRect;
    GetWindowRect(console, &ConsoleRect);
    MoveWindow(console, ConsoleRect.left, ConsoleRect.top, 800, 1000, TRUE);

    srand(time(NULL));
    int DMK[12][12];
    int DMI[12][12];


    system("pause");
    system("cls");

    cout << "\n    KOMPUTER RASSTAVIL KORABLI I GOTOV K IGRE.\n ";
    ARastan(DMK);    // Автоматическая расстановка кораблей Компьютера


    cout << "\n    POLE IGROKA:  1 - RUCHNAYA RASSTANOVKA,   2 - AVTOMATICHESKAYA RASSTANOVKA.\n";
    int VRI = 0;      // Вариант расстановки кораблей Игрока ( Ручная / Автоматическая)   
    while (VRI != 1 && VRI != 2)
    {
        cin >> VRI;     //Только 1 или 2
    }
    system("cls");
    if (VRI == 1) RRastan(DMI);     // Ручная расстановка кораблей Игрока 
    if (VRI == 2) ARastan(DMI);     // Автоматическая расстановка кораблей Игрока
    cout << "\n\n    POLE IGROKA:\n ";
    Print(DMI);
    system("pause");
    system("cls");

    int DMS[12][12]; // Заполнение нолями поля стрельбы Игрока
    for (int i = 0; i < 12; i++)
    {
        for (int j = 0; j < 12; j++) DMS[i][j] = 0;
    }
    char chara;
    int a = 1, b = 1, c = 0, d = 0, countK = 1, countI = 1, indpi = 1, indpk = 1, indikranil = 0, indikubil = 0, VV, tc = 0, td = 0, countPK = 0, countPI = 0, indranilK = 0;
    // VV - варианты стрельбы Компьютера, после попадания (вверх - вниз или вправо - влево)
    // indranilK - если Компьютер ранил корабль Игрока, то индикатор сигнализирует о необходимости прицельно стрелять рядом с попаданием
    // a, b , c , d - координаты, countK, countI - счетчики попаданий Игрока и Компьютера, 

    while (countK == 1 && countI == 1)  // Основное тело программы. Первый выстрел всегда за игроком.
    {
        system("pause");
        system("cls");
        cout << "    POLE IGROKA: \n";      // Вывод на экран поля Игрока
        Print(DMI);
        cout << "\n    POLE KOMPUTERA: \n";     // Вывод на экран поля стрельбы Игрока
        Print(DMS);

        while (indpi == 1)
        {
            int start = 1;
            while (start == 1) // Цикл проверки ввода толлько допустимых значений координат выстрела или выхода из игры
            {
                cout << "    VISTREL IGROKA (PERVAYA CIFRA A - J - VISOTA, VTORAYA 1 - 10 - DLINA)." << endl;
                cout << "    BUKVA:  ";
                cin >> chara;
                cout << "\n    CIFRA:  ";
                cin >> b;
                a = Perevod(chara);
                if ((a > 0 && a < 11) && (b > 0 && b < 11)) start = 0;      //  Защита от ввода неправильных значений координат  ПРОБЛЕМА ВВОДА ЦИФРЫ
                else start = 1;
            }
            a--;    // Уменьшение на 1 значений введенных координат
            b--;
            system("cls");
            // Корабли противников обозначены на карте 1, попадания обозначены 2, промахи - 5
            if (DMK[a][b] == 1)     // Если попал
            {
                DMK[a][b] = 2;
                DMS[a][b] = 2;
                cout << "    POLE IGROKA: \n";
                Print(DMI);
                cout << "\n    POLE KOMPUTERA: \n";
                Print(DMS);
                if (DMK[a - 1][b] == 1 || DMK[a + 1][b] == 1 || DMK[a][b - 1] == 1 || DMK[a][b + 1] == 1)
                {
                    cout << "\n    REZULTATI STRELBI IGROKA: POPAL - RANIL \n ";
                }
                else cout << "\n    REZULTATI STRELBI IGROKA: POPAL - UBIL \n";
                indpi = 1;
                countPI++; // Счетчик попаданий Игрока (не более 20)
                if (countPI == 20) break;
            }

            else     // Если промахнулся
            {
                DMS[a][b] = 5;
                DMK[a][b] = 5;
                cout << "    POLE IGROKA: \n";
                Print(DMI);
                cout << "\n    POLE KOMPUTERA: \n";
                Print(DMS);
                cout << "\n    REZULTATI STRELBI IGROKA: NE POPAL \n";
                indpi = 0;
            }
        }
        indpi = 1; // Индикатор попадания Игроком

        cout << "\n    SLIEDUUSHIY HOD KOMPUTERA " << endl;


        while (indpk == 1)      // Здесь начнется ход компьютера
        {
            cout << "   VISTREL KOMPUTERA  " << endl;
            int indpovt = 1;

            while (indpovt == 1)
            {
                indpovt = 0;
                if (indranilK != 1)     //  Если ранения нет, то выстрел снова случайный
                {
                    c = rand() % 10;     //  Компьютер делает первый выстрел полностью случайным 
                    d = rand() % 10;
                    if (DMI[c][d] == 2 || DMI[c][d] == 5 || DMI[c][d] == 3) indpovt = 1;  //    Далее он уже не стреляет еще раз в бывшие точки 
                }

                if (indranilK == 1)     //  Есди Компьютер ранил корабль Игрока, то начинает обстреливать близлижащие точки
                {
                    tc = c;     //  Фиксация координат с попаданием перед новым выстрелом по близлижащим точкам
                    td = d;

                    VV = rand() % 4;

                    if (VV == 0) c--, d = d;
                    if (VV == 1) c++, d = d;
                    if (VV == 2) c = c, d--;
                    if (VV == 3) c = c, d++;

                    if (c > 9) c--;
                    if (c < 0) c++;
                    if (d > 9) d--;
                    if (d < 0) d++;

                    if (DMI[c][d] == 2 || DMI[c][d] == 5 || DMI[c][d] == 3)     //  Если попадание произошло по бывшей точке, то предыдущие результативные координаты восстанавливаются
                    {
                        indpovt = 1;
                        c = tc, d = td;
                    }

                }
            }
            cout << "    BUKVA: " << c + 1 << "    CIFRA:  " << d + 1 << endl;
            system("pause");
            system("cls");

            if (DMI[c][d] == 1)     // В случае попадания
            {
                DMI[c][d] = 2;
                cout << "    POLE IGROKA: \n";
                Print(DMI);
                cout << "\n    POLE KOMPUTERA: \n";
                Print(DMS);
                if (DMI[c - 1][d] == 1 || DMI[c + 1][d] == 1 || DMI[c][d - 1] == 1 || DMI[c][d + 1] == 1)
                {
                    cout << "\n    REZULTATI STRELBI KOMPUTERA: POPAL - RANIL \n ";
                    DMI[c][d] = 3;  // 3 - Ранил
                    indranilK = 1;  //      Индикатор ранения (переход к прицельной стрельбе вокруг точки попадания 
                }

                else
                {
                    cout << "\n    REZULTATI STRELBI KOMPUTERA: POPAL - UBIL \n";
                    indranilK = 0;      //  После "убийства" индикатор ранения обнуляется и стрельба снова по случайной точке
                }

                indpk = 1;
                countPK++;
                if (countPK == 20) break;

            }

            else    //  В случае промаха
            {
                DMI[c][d] = 5;
                cout << "    POLE IGROKA: \n";
                Print(DMI);
                cout << "\n    POLE KOMPUTERA: \n";
                Print(DMS);
                cout << "\n    REZULTATI STRELBI KOMPUTERA: NE POPAL \n";
                indpk = 0;
                if (indranilK == 1)
                {
                    c = tc, d = td;     //  Если Компьютер промахнулся по раненому кораблю, то координаты предыдущего попадания снова восстанавливаются
                    indranilK = 1;      //  А индикатор ранения перезапускается для дальнейшего обстрела соседних точек                   
                }
            }
        }
        indpk = 1; // Индикатор попадания Компьютером
        countK = 0;
        countI = 0;
        for (int l = 0; l < 10; l++)
        {
            for (int m = 0; m < 10; m++)
            {
                if (DMK[l][m] == 1) countK = 1;
                if (DMI[l][m] == 1) countI = 1;
            }
        }
        if (countPK == 20)
        {
            cout << "\n    IGRA OKONCHENA   POBEDIL KOMPUTER \n\n";
            system("pause");
            countK = 0;
        }
        if (countPI == 20)
        {
            cout << "\n    IGRA OKONCHENA   POBEDIL IGROK \n\n";
            system("pause");
            countI = 0;
        }
    }
}

void RRastan(int masi[12][12])
{
    for (int i = 0; i < 10; i++) { // Расстановка нолей
        for (int j = 0; j < 10; j++)
            masi[i][j] = 0;
    }

    cout << endl;

    Print(masi);

    cout << "\n    RAZMESTITE KORABLI : 1 - 4xPALUBI, 2 - 3xPALUBI, 3 - 2xPALUBI, 4 - 1xPALUBI\n";
    cout << "\n    KOORDINATI A, B, C, D, E, F, G, H, I, J i ciframi 1, 2, 3, 4, 5, 6, 7, 8, 9, 10\n";


    int sign4 = 0, sign3 = 0, sign2 = 0, sign1 = 0;
    char chari;
    int NAPR = 0, i = 0, j = 0, ti = 0, tj = 0;
    while (sign4 != 1 && sign3 != 2 && sign2 != 3 && sign1 != 4)
    {
        int count4 = 0;
        while (sign4 != 1)  // Заполнение четырехпалубными
        {
            cout << "\n    VVOD 4xPALUBNOGO - 1 SHT.: " << endl; // Расстановка 4 палубного
            cout << "    NAPRAVLENIE KORABLYA (1 - VPRAVO, 2 - VNIZ): ";

            while (NAPR != 1 && NAPR != 2)
            {
                cin >> NAPR;     //Только 1 или 2
            }

            cout << "    KOORDINATI PERVOY PALUBI: " << endl;
            cout << "    BUKVA:  ";
            cin >> chari;
            i = Perevod(chari);
            cout << "\n    CIFRA:  ";
            cin >> j;

            i--;
            j--;
            ti = i;
            tj = j;
            sign4 = 0;

            if (NAPR == 1)
            {
                count4 = 0;
                for (int i = ti - 1; i <= ti + 1; i++)
                {
                    for (int j = tj - 1; j <= tj + 4; j++)
                    {
                        if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9))  count4++;
                    }
                }

                if (count4 == 18 && j < 7) {
                    masi[i][j] = 1;
                    masi[i][j + 1] = 1;
                    masi[i][j + 2] = 1;
                    masi[i][j + 3] = 1;
                    sign4 = 1;
                }
            }

            if (NAPR == 2)
            {
                count4 = 0;
                for (int i = ti - 1; i <= ti + 4; i++)

                    for (int j = tj - 1; j <= tj + 1; j++)
                    {
                        if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9)) count4++;
                    }

                if (count4 == 18 && i < 7) {
                    masi[i][j] = 1;
                    masi[i + 1][j] = 1;
                    masi[i + 2][j] = 1;
                    masi[i + 3][j] = 1;
                    sign4 = 1;
                }
            }
            system("cls");
            Print(masi);
        }

        int sign3 = 0;
        int count3 = 0;
        while (sign3 != 2)  // Заполнение трехпалубными
        {
            cout << "\n    VVOD 3xPALUBNOGO - 2 SHT.: " << endl; // Расстановка 3 палубных
            cout << "    NAPRAVLENIE KORABLYA (1 - VPRAVO, 2 - VNIZ): ";
            int NAPR = 0, i = 0, j = 0, ti = 0, tj = 0;
            while (NAPR != 1 && NAPR != 2)
            {
                cin >> NAPR;     //Только 1 или 2
            }
            cout << "    KOORDINATI PERVOY PALUBI: " << endl;
            cout << "    BUKVA:  ";
            cin >> chari;
            i = Perevod(chari);
            cout << "\n    CIFRA:  ";
            cin >> j;
            i--;
            j--;
            ti = i;
            tj = j;

            if (NAPR == 1)
            {
                count3 = 0;
                for (int i = ti - 1; i <= ti + 1; i++)
                    for (int j = tj - 1; j <= tj + 3; j++)
                    {
                        if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9)) count3++;
                    }

                if (count3 == 15 && j < 8) {
                    masi[i][j] = 1;
                    masi[i][j + 1] = 1;
                    masi[i][j + 2] = 1;
                    sign3++;
                }
            }

            if (NAPR == 2)
            {
                count3 = 0;
                for (int i = ti - 1; i <= ti + 3; i++)
                    for (int j = tj - 1; j <= tj + 1; j++)
                    {
                        if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9)) count3++;
                    }
                if (count3 == 15 && i < 8)
                {
                    masi[i][j] = 1;
                    masi[i + 1][j] = 1;
                    masi[i + 2][j] = 1;
                    sign3++;
                }
            }
            system("cls");
            Print(masi);
        }

        int sign2 = 0;
        int count2 = 0;
        while (sign2 != 3)  // Заполнение двухпалубными
        {
            cout << "\n    VVOD 2xPALUBNOGO - 3 SHT.: " << endl; // Расстановка 2 палубного
            cout << "    NAPRAVLENIE KORABLYA (1 - VPRAVO, 2 - VNIZ): ";
            int NAPR = 0, i = 0, j = 0, ti = 0, tj = 0;
            while (NAPR != 1 && NAPR != 2)
            {
                cin >> NAPR;     //Только 1 или 2
            }
            cout << "    KOORDINATI PERVOY PALUBI: " << endl;
            cout << "    BUKVA:  ";
            cin >> chari;
            i = Perevod(chari);
            cout << "\n    CIFRA:  ";
            cin >> j;
            i--;
            j--;
            ti = i;
            tj = j;

            if (NAPR == 1)
            {
                count2 = 0;
                for (int i = ti - 1; i <= ti + 1; i++)
                    for (int j = tj - 1; j <= tj + 2; j++)
                    {
                        if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9)) count2++;
                    }
                if (count2 == 12 && j < 9) {
                    masi[i][j] = 1;
                    masi[i][j + 1] = 1;
                    sign2++;
                }
            }

            if (NAPR == 2)
            {
                count2 = 0;
                for (int i = ti - 1; i <= ti + 2; i++)
                    for (int j = tj - 1; j <= tj + 1; j++)
                    {
                        if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9)) count2++;
                    }

                if (count2 == 12 && i < 9) {
                    masi[i][j] = 1;
                    masi[i + 1][j] = 1;
                    sign2++;
                }
            }
            system("cls");
            Print(masi);
        }

        int sign1 = 0;
        int count1 = 0;
        while (sign1 != 4)  // Заполнение однопалубными
        {
            cout << "\n    VVOD 1xPALUBNOGO - 4 SHT.: " << endl; // Расстановка 1 палубного

            int NAPR = 0, i = 0, j = 0, ti = 0, tj = 0;

            cout << "    KOORDINATI PALUBI: " << endl;
            cout << "    BUKVA:  ";
            cin >> chari;
            i = Perevod(chari);
            cout << "\n    CIFRA:  ";
            cin >> j;
            i--;
            j--;
            ti = i;
            tj = j;
            count1 = 0;
            for (int i = ti - 1; i <= ti + 1; i++)
                for (int j = tj - 1; j <= tj + 1; j++)
                {
                    if ((masi[i][j] != 1) || (i < 0 || i>9 || j < 0 || j>9)) count1++;
                }

            if (count1 == 9 && j < 10) {
                masi[i][j] = 1;
                sign1++;
            }
            system("cls");
            Print(masi);
        }
    }
    system("cls");

}


void Print(int mas[12][12])     //  Функция печати полей Игроков
{
    cout << endl;
    cout << "   1 2 3 4 5 6 7 8 9 10" << endl;
    for (int i = 0; i < 10; i++)
    {
        if (i == 9) cout << " " << (char)(65 + i) << " ";
        if (i != 9) cout << " " << (char)(65 + i) << " ";
        for (int j = 0; j < 10; j++) {

            if (mas[i][j] == 0) cout << (char)176 << (char)176;
            if (mas[i][j] == 1) cout << (char)219 << (char)219;
            if (mas[i][j] == 2 || mas[i][j] == 3) cout << "XX";
            if (mas[i][j] == 5) cout << "--";
        }
        cout << endl;
    }
    cout << endl;
}

void ARastan(int masi[12][12]) // Автоматическая расстановка кораблей
{
    Sleep(1000);
    srand(time(NULL));
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++)
            masi[i][j] = 0;
    }

    int i, ti, j, tj;
    int count4 = 0;
    int sign4 = 0, sign3 = 0, sign2 = 0, sign1 = 0;
    while (sign4 != 1 && sign3 != 2 && sign2 != 3 && sign1 != 4)
    {

        while (sign4 != 1)  // Заполнение четырехпалубными
        {
            i = rand() % 10;
            j = rand() % 10;
            ti = i;
            tj = j;
            sign4 = 0;
            int NAPR = (rand() % 2) + 1;

            if (NAPR == 1)
            {
                count4 = 0;
                for (int i = ti - 1; i <= ti + 1; i++)
                    for (int j = tj - 1; j <= tj + 4; j++) if (masi[i][j] != 1) count4++;

                if (count4 == 18 && j < 7) {
                    masi[i][j] = 1;
                    masi[i][j + 1] = 1;
                    masi[i][j + 2] = 1;
                    masi[i][j + 3] = 1;
                    sign4 = 1;
                }
            }

            if (NAPR == 2) {
                count4 = 0;
                for (int i = ti - 1; i <= ti + 4; i++)
                    for (int j = tj - 1; j <= tj + 1; j++) if (masi[i][j] != 1) count4++;
                if (count4 == 18 && i < 7) {
                    masi[i][j] = 1;
                    masi[i + 1][j] = 1;
                    masi[i + 2][j] = 1;
                    masi[i + 3][j] = 1;
                    sign4 = 1;
                }
            }
        }

        int sign3 = 0;
        int count3 = 0;
        while (sign3 != 2)  // Заполнение трехпалубными
        {
            i = rand() % 10;
            j = rand() % 10;
            ti = i;
            tj = j;

            int NAPR = (rand() % 2) + 1;

            if (NAPR == 1)
            {
                count3 = 0;
                for (int i = ti - 1; i <= ti + 1; i++)
                    for (int j = tj - 1; j <= tj + 3; j++) if (masi[i][j] != 1) count3++;

                if (count3 == 15 && j < 8) {
                    masi[i][j] = 1;
                    masi[i][j + 1] = 1;
                    masi[i][j + 2] = 1;
                    sign3++;
                }
            }

            if (NAPR == 2)
            {
                count3 = 0;
                for (int i = ti - 1; i <= ti + 3; i++)
                    for (int j = tj - 1; j <= tj + 1; j++) if (masi[i][j] != 1) count3++;
                if (count3 == 15 && i < 8)
                {
                    masi[i][j] = 1;
                    masi[i + 1][j] = 1;
                    masi[i + 2][j] = 1;
                    sign3++;
                }
            }
        }

        int sign2 = 0;
        int count2 = 0;
        while (sign2 != 3)  // Заполнение двухпалубными
        {
            i = rand() % 10;
            j = rand() % 10;
            ti = i;
            tj = j;

            int NAPR = (rand() % 2) + 1;

            if (NAPR == 1)
            {
                count2 = 0;
                for (int i = ti - 1; i <= ti + 1; i++)
                    for (int j = tj - 1; j <= tj + 2; j++)  if (masi[i][j] != 1) count2++;
                if (count2 == 12 && j < 9) {
                    masi[i][j] = 1;
                    masi[i][j + 1] = 1;
                    sign2++;
                }
            }

            if (NAPR == 2)
            {
                count2 = 0;
                for (int i = ti - 1; i <= ti + 2; i++)
                    for (int j = tj - 1; j <= tj + 1; j++) if (masi[i][j] != 1) count2++;
                if (count2 == 12 && i < 9) {
                    masi[i][j] = 1;
                    masi[i + 1][j] = 1;
                    sign2++;
                }
            }
        }

        int sign1 = 0;
        int count1 = 0;
        while (sign1 != 4)  // Заполнение однопалубными
        {
            i = rand() % 10;
            j = rand() % 10;
            ti = i;
            tj = j;

            count1 = 0;
            for (int i = ti - 1; i <= ti + 1; i++)
                for (int j = tj - 1; j <= tj + 1; j++) if (masi[i][j] != 1) count1++;
            if (count1 == 9 && j < 10) {
                masi[i][j] = 1;
                sign1++;

            }
        }
    }

}

int Perevod(char a)
{
    int b = 100;
    if (a == 'A') b = 1;
    if (a == 'B') b = 2;
    if (a == 'C') b = 3;
    if (a == 'D') b = 4;
    if (a == 'E') b = 5;
    if (a == 'F') b = 6;
    if (a == 'G') b = 7;
    if (a == 'H') b = 8;
    if (a == 'I') b = 9;
    if (a == 'J') b = 10;

    if (b > 0 && b <= 10) return b;
    else return 100;

}
