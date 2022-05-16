// pwir-computational-problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <chrono>
#include <thread>

using namespace std;

#define MAX_TAB_SIZE 700

void ShowIntroInformation(HANDLE hConsole);
void GenerateRandomMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int min, int max);
void DisplayMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize);
void CopyMatrix(int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize);
void BubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay);
void OptimizedBubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay);

int main()
{
    setlocale(LC_CTYPE, "Polish");

    HANDLE hConsole;
    int matrixSize = 0;
    int min = 0;
    int max = 0;
    int whetherDisplay = 0;
    int delay = 0;
    int sortOption = 0;
    bool isIntervalGood = false;
    bool displayStatment = false;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ShowIntroInformation(hConsole);

    do {
      SetConsoleTextAttribute(hConsole, 14);
      cout << "\n -> Jaki rozmiar ma mie� macierz kwadratowa? ";
      SetConsoleTextAttribute(hConsole, 12);
      cout << "(maksymalny rozmiar to 700): ";
      SetConsoleTextAttribute(hConsole, 15);
      cin >> matrixSize;
      if (!matrixSize || matrixSize <= 0 || matrixSize > MAX_TAB_SIZE) {
        matrixSize = 0;
        SetConsoleTextAttribute(hConsole, 4);
        cout << "    ! Musisz wprowadzi� liczb� wi�ksz� od 0 i mniejsz�, b�d� r�wn� 700\n";
        SetConsoleTextAttribute(hConsole, 15);
        cin.clear();
        cin.ignore();
      }
    } while (matrixSize == 0);

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n -> Jaki przedzia� liczb losowych ma posiada� macierz?\n";
    do {
    SetConsoleTextAttribute(hConsole, 14);
    cout << " --> Podaj minimum: ";
    SetConsoleTextAttribute(hConsole, 15);
    cin >> min;
    if (!min) {
        min = 0;
        SetConsoleTextAttribute(hConsole, 4);
        cout << "     ! Warto�� minimum musi by� liczb�\n";
        SetConsoleTextAttribute(hConsole, 15);
        cin.clear();
        cin.ignore();
    }
    else {
        do {
            SetConsoleTextAttribute(hConsole, 14);
            cout << " --> Podaj maksimum: ";
            SetConsoleTextAttribute(hConsole, 15);
            cin >> max;
            if (!max) {
                max = 0;
                SetConsoleTextAttribute(hConsole, 4);
                cout << "     ! Warto�� maksimum musi by� liczb�\n";
                SetConsoleTextAttribute(hConsole, 15);
                cin.clear();
                cin.ignore();
            }
            else if (max < min) {
                max = 0;
                SetConsoleTextAttribute(hConsole, 4);
                cout << "     ! Warto�� maksimum musi by� wi�ksze od minimum\n";
                SetConsoleTextAttribute(hConsole, 15);
                cin.clear();
                cin.ignore();
            }
            else if (max >= min) { 
                isIntervalGood = true; 
            }
        } while (!isIntervalGood);
    }
    } while (!isIntervalGood);

    do {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n -> Podaj op�nienie? [ms]: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> delay;
        if (!delay) {
            delay = 0;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Warto�� op�nienia musi by� liczb�\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
    } while (!delay);

    if (delay < 0) delay = 0;

    do {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n -> Wy�wietli� macierze? [1/0]: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> whetherDisplay;
        displayStatment = !(whetherDisplay == 0 || whetherDisplay == 1) || !whetherDisplay ;
        if (displayStatment) {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Warto�� musi by� liczb� 0 lub 1\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
    } while (displayStatment);

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n -> Opcje sortowania:";
    cout << "\n --> [1] Sortowanie b�belkowe";
    cout << "\n --> [2] Sortowanie b�belkowe zoptymalizowane\n";
    do {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n --> Wybierz spo�r�d dost�pnych opcji: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> sortOption;
        if (!sortOption)
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Warto�� musi by� liczb�\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
        else if (!(sortOption == 1 || sortOption == 2))
        {
            sortOption = 0;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Warto�� musi by� r�wna jednej z dost�pnych opcji\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
    } while (!sortOption && !(sortOption == 1 || sortOption == 2));
    

    auto matrix = new int[matrixSize][MAX_TAB_SIZE];
    GenerateRandomMatrix(matrix, matrixSize, min, max);

    if (whetherDisplay) {
        cout << "\n\n";
        SetConsoleTextAttribute(hConsole, 11);
        for (int i = 0; i < 70; i++) cout << '*';
        SetConsoleTextAttribute(hConsole, 3);
        cout << "\n ---> Wygenerowana macierz\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        DisplayMatrix(matrix, matrixSize);
    }

    auto copyMatrix = new int[matrixSize][MAX_TAB_SIZE];

    if (sortOption == 1)
    {
        CopyMatrix(matrix, copyMatrix, matrixSize);
        cout << "\n";
        SetConsoleTextAttribute(hConsole, 11);
        for (int i = 0; i < 70; i++) cout << '*';
        SetConsoleTextAttribute(hConsole, 3);
        cout << "\n ---> Sekwencyjne sortowanie macierzy - sortowanie b�belkowe\n\n";
        SetConsoleTextAttribute(hConsole, 15);

        auto begin = std::chrono::high_resolution_clock::now();
        BubbleSortRowsMatrix(copyMatrix, matrixSize, delay);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        if (whetherDisplay) {
            DisplayMatrix(copyMatrix, matrixSize);
        }
        cout << endl << "Zmierzony czas: " << elapsed << " ms" << endl;
        cout << "\n";
    }
    else if (sortOption == 2)
    {
        CopyMatrix(matrix, copyMatrix, matrixSize);
        cout << "\n";
        SetConsoleTextAttribute(hConsole, 11);
        for (int i = 0; i < 70; i++) cout << '*';
        SetConsoleTextAttribute(hConsole, 3);
        cout << "\n ---> Sekwencyjne sortowanie macierzy - sortowanie b�belkowe zoptymalizowane\n\n";
        SetConsoleTextAttribute(hConsole, 15);
        auto begin = std::chrono::high_resolution_clock::now();
        OptimizedBubbleSortRowsMatrix(copyMatrix, matrixSize, delay);
        auto end = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        if (whetherDisplay) {
            DisplayMatrix(copyMatrix, matrixSize);
        }
        cout << endl << "Zmierzony czas: " << elapsed << " ms" << endl;
    }

    delete[] matrix;
}

void ShowIntroInformation(HANDLE hConsole) 
{
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n\n  PROGRAMOWANIE WSPӣBIE�NE I ROZPROSZONE 21/22L\n  Autor programu: ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Kamil Hojka -- 97632\n\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 15);
}

void GenerateRandomMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int min, int max) 
{
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            matrix[i][j] = min + (rand() % static_cast<int>(max - min + 1));
        }
    }
}

void DisplayMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize) 
{
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void CopyMatrix(int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize) 
{
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            copyMatrix[i][j] = matrix[i][j];
        }
    }
}

void BubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay) 
{
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize - 1; j++) {
            for (int k = 0; k < matrixSize - j - 1; k++) {
                if (matrix[i][k] > matrix[i][k + 1]) {
                    this_thread::sleep_for(std::chrono::milliseconds(delay));
                    swap(matrix[i][k], matrix[i][k + 1]);
                }
            }
        }
    }
}

void OptimizedBubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay)
{
    for (int m = 0; m < matrixSize; m++) {
        for (int step = 0; step < (matrixSize - 1); ++step) {
            int swapped = 0;

            for (int i = 0; i < (matrixSize - step - 1); ++i) {
                if (matrix[m][i] > matrix[m][i + 1]) {
                    this_thread::sleep_for(std::chrono::milliseconds(delay));
                    swap(matrix[m][i], matrix[m][i + 1]);
                    swapped = 1;
                }
            }

            if (swapped == 0)
                break;
        }
    }
}