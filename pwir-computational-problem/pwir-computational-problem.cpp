// pwir-computational-problem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <windows.h>
#include <ctype.h>
#include <chrono>
#include <thread>
#include <vector>
#include <omp.h>

using namespace std;

#define MAX_TAB_SIZE 700

void ShowIntroInformation(HANDLE hConsole);
void GenerateRandomMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int min, int max);
void DisplayMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize);
void DisplayGeneratedMatrix(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int matrixSize);
void CopyMatrix(int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize);
void BubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay);
void OptimizedBubbleSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay);
void InsertionSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay);
void BubbleSortRowsMatrixParallel(int matrix[][MAX_TAB_SIZE], int matrixSize, int selectedRow, int delay);
void OptimizedBubbleSortRowsMatrixParallel(int matrix[][MAX_TAB_SIZE], int matrixSize, int selectedRow, int delay);
void InsertionSortRowsMatrixParallel(int matrix[][MAX_TAB_SIZE], int matrixSize, int selectedRow, int delay);
void RunBubbleSort(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize, int delay, int displayOption);
void RunOptimizedBubbleSort(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize, int delay, int displayOption);
void RunInsertionSort(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize, int delay, int displayOption);
void SetMatrixSize(HANDLE hConsole, int& matrixSize);
void SetMatrixInterval(HANDLE hConsole, int& min, int& max);
void SetDelay(HANDLE hConsole, int& delay);
void SetDisplayOption(HANDLE hConsole, int& displayOption);
void SetSortOption(HANDLE hConsole, int& sortOption);

int main()
{
    setlocale(LC_CTYPE, "Polish");

    HANDLE hConsole;
    int matrixSize = 0;
    int min = 0;
    int max = 0;
    int delay = 0;
    int displayOption = 0;
    int sortOption = 0;
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    ShowIntroInformation(hConsole);
    SetMatrixSize(hConsole, matrixSize);
    SetMatrixInterval(hConsole, min, max);
    SetDelay(hConsole, delay);
    SetDisplayOption(hConsole, displayOption);
    SetSortOption(hConsole, sortOption);

    auto matrix = new int[matrixSize][MAX_TAB_SIZE];
    GenerateRandomMatrix(matrix, matrixSize, min, max);

    if (displayOption) { 
        DisplayGeneratedMatrix(hConsole, matrix, matrixSize);
    }

    auto copyMatrix = new int[matrixSize][MAX_TAB_SIZE];

    if (sortOption == 1) {
        RunBubbleSort(hConsole, matrix, copyMatrix, matrixSize, delay, displayOption);
    }
    else if (sortOption == 2) {
        RunOptimizedBubbleSort(hConsole, matrix, copyMatrix, matrixSize, delay, displayOption);
    }
    else if (sortOption == 3) {
        RunInsertionSort(hConsole, matrix, copyMatrix, matrixSize, delay, displayOption);
    }

    delete[] matrix;
}

void ShowIntroInformation(HANDLE hConsole) 
{
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n\n  PROGRAMOWANIE WSPÓ£BIE¯NE I ROZPROSZONE 21/22L\n  Autor programu: ";
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

void DisplayGeneratedMatrix(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int matrixSize)
{
    cout << "\n\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Wygenerowana macierz\n\n";
    SetConsoleTextAttribute(hConsole, 15);
    DisplayMatrix(matrix, matrixSize);
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


void InsertionSortRowsMatrix(int matrix[][MAX_TAB_SIZE], int matrixSize, int delay)
{
    for (int k = 0; k < matrixSize; k++) {
        for (int i = 1; i < matrixSize; i++) {
            int temp = matrix[k][i];
            int j = i - 1;
            for (j; j >= 0 && matrix[k][j] > temp; j--) {
                this_thread::sleep_for(std::chrono::milliseconds(delay));
                matrix[k][j + 1] = matrix[k][j];
            }
            matrix[k][j + 1] = temp;
        }
    }
}


void BubbleSortRowsMatrixParallel(int matrix[][MAX_TAB_SIZE], int matrixSize, int selectedRow, int delay)
{
    for (int j = 0; j < matrixSize - 1; j++) {
        for (int k = 0; k < matrixSize - j - 1; k++) {
            if (matrix[selectedRow][k] > matrix[selectedRow][k + 1]) {
                this_thread::sleep_for(std::chrono::milliseconds(delay));
                swap(matrix[selectedRow][k], matrix[selectedRow][k + 1]);
            }
        }
    }
}

void OptimizedBubbleSortRowsMatrixParallel(int matrix[][MAX_TAB_SIZE], int matrixSize, int selectedRow, int delay)
{
    for (int step = 0; step < (matrixSize - 1); ++step) {
        int swapped = 0;

        for (int i = 0; i < (matrixSize - step - 1); ++i) {
            if (matrix[selectedRow][i] > matrix[selectedRow][i + 1]) {
                this_thread::sleep_for(std::chrono::milliseconds(delay));
                swap(matrix[selectedRow][i], matrix[selectedRow][i + 1]);
                swapped = 1;
            }
        }

        if (swapped == 0)
            break;
    }
}


void InsertionSortRowsMatrixParallel(int matrix[][MAX_TAB_SIZE], int matrixSize, int selectedRow, int delay)
{
    for (int i = 1; i < matrixSize; i++) {
        int temp = matrix[selectedRow][i];
        int j = i - 1;
        for (j; j >= 0 && matrix[selectedRow][j] > temp; j--) {
            this_thread::sleep_for(std::chrono::milliseconds(delay));
            matrix[selectedRow][j + 1] = matrix[selectedRow][j];
        }
        matrix[selectedRow][j + 1] = temp;
    }
}

void RunBubbleSort(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize, int delay, int displayOption)
{
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Sekwencyjne sortowanie macierzy - sortowanie b¹belkowe\n";
    SetConsoleTextAttribute(hConsole, 15);
    auto begin = std::chrono::high_resolution_clock::now();
    BubbleSortRowsMatrix(copyMatrix, matrixSize, delay);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";

    // Parallel 
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Równoleg³e sortowanie macierzy - sortowanie b¹belkowe\n";
    SetConsoleTextAttribute(hConsole, 15);
    begin = std::chrono::high_resolution_clock::now();
    vector<thread> threads(matrixSize);
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i] = thread(BubbleSortRowsMatrixParallel, copyMatrix, matrixSize, i, delay);
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";

    // Parallel - OpenMP
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Równoleg³e sortowanie macierzy OpenMP - sortowanie b¹belkowe\n";
    SetConsoleTextAttribute(hConsole, 15);
    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < matrixSize; i++) {
        BubbleSortRowsMatrixParallel(copyMatrix, matrixSize, i, delay);
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";
}

void RunOptimizedBubbleSort(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize, int delay, int displayOption)
{
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Sekwencyjne sortowanie macierzy - sortowanie b¹belkowe zoptymalizowane\n";
    SetConsoleTextAttribute(hConsole, 15);
    auto begin = std::chrono::high_resolution_clock::now();
    OptimizedBubbleSortRowsMatrix(copyMatrix, matrixSize, delay);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";

    // Parallel
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Równoleg³e sortowanie macierzy - sortowanie b¹belkowe zoptymalizowane\n";
    SetConsoleTextAttribute(hConsole, 15);
    begin = std::chrono::high_resolution_clock::now();
    vector<thread> threads(matrixSize);
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i] = thread(OptimizedBubbleSortRowsMatrixParallel, copyMatrix, matrixSize, i, delay);
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";

    // Parallel - OpenMP
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Równoleg³e sortowanie macierzy OpenMP - sortowanie b¹belkowe zoptymalizowane\n";
    SetConsoleTextAttribute(hConsole, 15);
    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < matrixSize; i++) {
        OptimizedBubbleSortRowsMatrixParallel(copyMatrix, matrixSize, i, delay);
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";
}

void RunInsertionSort(HANDLE hConsole, int matrix[][MAX_TAB_SIZE], int copyMatrix[][MAX_TAB_SIZE], int matrixSize, int delay, int displayOption)
{
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Sekwencyjne sortowanie macierzy - Sortowanie przez wstawianie\n";
    SetConsoleTextAttribute(hConsole, 15);
    auto begin = std::chrono::high_resolution_clock::now();
    InsertionSortRowsMatrix(copyMatrix, matrixSize, delay);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";

    // Parallel 
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Równoleg³e sortowanie macierzy - Sortowanie przez wstawianie\n";
    SetConsoleTextAttribute(hConsole, 15);
    begin = std::chrono::high_resolution_clock::now();
    vector<thread> threads(matrixSize);
    for (int i = 0; i < threads.size(); i++)
    {
        threads[i] = thread(InsertionSortRowsMatrixParallel, copyMatrix, matrixSize, i, delay);
    }
    for (auto& thread : threads)
    {
        thread.join();
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";

    // Parallel - OpenMP
    CopyMatrix(matrix, copyMatrix, matrixSize);
    cout << "\n";
    SetConsoleTextAttribute(hConsole, 11);
    for (int i = 0; i < 70; i++) cout << '*';
    SetConsoleTextAttribute(hConsole, 3);
    cout << "\n ---> Równoleg³e sortowanie macierzy OpenMP - Sortowanie przez wstawianie\n";
    SetConsoleTextAttribute(hConsole, 15);
    begin = std::chrono::high_resolution_clock::now();
#pragma omp parallel for
    for (int i = 0; i < matrixSize; i++) {
        InsertionSortRowsMatrixParallel(copyMatrix, matrixSize, i, delay);
    }
    end = std::chrono::high_resolution_clock::now();
    elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
    if (displayOption) {
        cout << "\n";
        DisplayMatrix(copyMatrix, matrixSize);
    }
    cout << "\nZmierzony czas: " << elapsed << " ms\n";
}

void SetMatrixSize(HANDLE hConsole, int& matrixSize)
{
    do {
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
}

void SetMatrixInterval(HANDLE hConsole, int& min, int& max)
{
    bool isIntervalGood = false;
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
}

void SetDelay(HANDLE hConsole, int& delay)
{
    bool isSetProperly = false;
    do {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n -> Podaj opóŸnienie? [ms]: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> delay;
        if (!cin.good()) {
            isSetProperly = false;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Wartoœæ opóŸnienia musi byæ liczb¹\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
        else isSetProperly = true;
    } while (!isSetProperly);

    if (delay < 0) delay = 0;
}

void SetDisplayOption(HANDLE hConsole, int& displayOption)
{
    bool isSetProperly = false;
    do {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n -> Wyœwietliæ macierze? [1/0]: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> displayOption;
        if (!cin.good()) {
            isSetProperly = false;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Wartoœæ musi byæ liczb¹ 0 lub 1\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
        else if (displayOption == 0 || displayOption == 1) isSetProperly = true;
    } while (!isSetProperly);
}

void SetSortOption(HANDLE hConsole, int& sortOption)
{
    SetConsoleTextAttribute(hConsole, 14);
    cout << "\n -> Opcje sortowania:";
    cout << "\n --> [1] Sortowanie b¹belkowe";
    cout << "\n --> [2] Sortowanie b¹belkowe zoptymalizowane";
    cout << "\n --> [3] Sortowanie przez wstawianie\n";
    do {
        SetConsoleTextAttribute(hConsole, 14);
        cout << "\n --> Wybierz spoœród dostêpnych opcji: ";
        SetConsoleTextAttribute(hConsole, 15);
        cin >> sortOption;
        if (!sortOption)
        {
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Wartoœæ musi byæ liczb¹\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
        else if (!(sortOption == 1 || sortOption == 2 || sortOption == 3))
        {
            sortOption = 0;
            SetConsoleTextAttribute(hConsole, 4);
            cout << "    ! Wartoœæ musi byæ równa jednej z dostêpnych opcji\n";
            SetConsoleTextAttribute(hConsole, 15);
            cin.clear();
            cin.ignore();
        }
    } while (!sortOption && !(sortOption == 1 || sortOption == 2 || sortOption == 3));
}