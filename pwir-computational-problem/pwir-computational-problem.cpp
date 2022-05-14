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
    bool isIntervalGood = false;
    bool displayStatment = false;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    ShowIntroInformation(hConsole);

    /*do {
      SetConsoleTextAttribute(hConsole, 14);
      cout << "\n -> Jaki rozmiar ma mieæ macierz kwadratowa? ";
      SetConsoleTextAttribute(hConsole, 12);
      cout << "(maksymalny rozmiar to 700): ";
      SetConsoleTextAttribute(hConsole, 15);
      cin >> matrixSize;
      if (!matrixSize || matrixSize <= 0 || matrixSize > MAX_TAB_SIZE) {
        matrixSize = 0;
        SetConsoleTextAttribute(hConsole, 4);
        cout << "    ! Musisz wprowadziæ liczbê wiêksz¹ od 0 i mniejsz¹, b¹dŸ równ¹ 700\n";
        SetConsoleTextAttribute(hConsole, 15);
        cin.clear();
        cin.ignore();
      }
    } while (matrixSize == 0);

    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n -> Jaki przedzia³ liczb losowych ma posiadaæ macierz?\n";
    do {
    SetConsoleTextAttribute(hConsole, 14);
    cout << " --> Podaj minimum: ";
    SetConsoleTextAttribute(hConsole, 15);
    cin >> min;
    if (!min) {
        min = 0;
        SetConsoleTextAttribute(hConsole, 4);
        cout << "     ! Wartoœæ minimum musi byæ liczb¹\n";
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
                cout << "     ! Wartoœæ maksimum musi byæ liczb¹\n";
                SetConsoleTextAttribute(hConsole, 15);
                cin.clear();
                cin.ignore();
            }
            else if (max < min) {
                max = 0;
                SetConsoleTextAttribute(hConsole, 4);
                cout << "     ! Wartoœæ maksimum musi byæ wiêksze od minimum\n";
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
        cout << "\n -> Wyœwietliæ macierze? [1/0]: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> whetherDisplay;
        displayStatment = !(whetherDisplay == 0 || whetherDisplay == 1) || !whetherDisplay ;
        if (displayStatment) {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Wartoœæ musi byæ liczb¹ 0 lub 1\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
    } while (displayStatment);*/

    //auto matrix = new int[matrixSize][MAX_TAB_SIZE];
    //GenerateRandomMatrix(matrix, matrixSize, min, max);
    whetherDisplay = 1;
    matrixSize = 10;
    delay = 1;
    int matrix[10][MAX_TAB_SIZE] = {{2, 4, 2, 3, 5, 1, 3, 8, 1, 8},
        {9, 5, 1, 8, 4, 6, 9, 3, 4, 1},
        {4, 5, 6, 1, 5, 2, 4, 4, 6, 4},
        {4, 3, 8, 3, 1, 5, 3, 6, 6, 1},
        {2, 8, 6, 3, 8, 4, 1, 2, 4, 3},
        {6, 2, 1, 9, 7, 6, 9, 9, 3, 5},
        {2, 3, 9, 6, 9, 4, 1, 9, 5, 9},
        {3, 5, 7, 3, 1, 3, 6, 7, 2, 2},
        {8, 9, 3, 2, 2, 9, 5, 4, 7, 4},
        {1, 2, 6, 4, 7, 5, 5, 4, 5, 8}};

    if (whetherDisplay) {
        cout << "\n";
        DisplayMatrix(matrix, matrixSize);
    }
    cout << "\n";
    /*auto begin = std::chrono::high_resolution_clock::now();
    BubbleSortRowsMatrix(matrix, matrixSize, delay);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    DisplayMatrix(matrix, matrixSize);
    cout << endl << "Zmierzony czas: " << elapsed << " ms" << endl;*/
    cout << "\n";


    cout << "\n";
    auto begin = std::chrono::high_resolution_clock::now();
    OptimizedBubbleSortRowsMatrix(matrix, matrixSize, delay);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    DisplayMatrix(matrix, matrixSize);
    cout << endl << "Zmierzony czas: " << elapsed << " ms" << endl;
    cout << "\n";
    

    //delete[] matrix;
}

void ShowIntroInformation(HANDLE hConsole) {
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n\n  PROGRAMOWANIE WSPÓ£BIE¯NE I ROZPROSZONE 21/22L\n  Autor programu: ";
    SetConsoleTextAttribute(hConsole, 15);
    cout << "Kamil Hojka -- S97632\n\n";
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

void DisplayMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize) {
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize; j++) {
            cout << matrix[i][j] << " ";
        }
        cout << "\n";
    }
}

void BubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay)
{
    for (int i = 0; i < matrixSize; i++) {
        for (int j = 0; j < matrixSize - 1; j++) {
            for (int m = 0; m < matrixSize - j - 1; m++) {
                if (matrix[i][m] > matrix[i][m + 1]) {
                    swap(matrix[i][m], matrix[i][m + 1]);
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
                    swap(matrix[m][i], matrix[m][i + 1]);

                    swapped = 1;
                    this_thread::sleep_for(chrono::milliseconds(delay));
                }
            }

            if (swapped == 0)
                break;
        }
    }
}