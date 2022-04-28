// Laba6EC.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "windows.h"
#include "C:\Users\Степан\Desktop\Laba6Dll\Laba6Dll\Laba6DLL.h"

int main()
{
    std::cout << "Hello World!\n";
    setlocale(LC_ALL, "Rus");
    HINSTANCE dll = LoadLibrary(L"C:\\Users\\Степан\\Desktop\\Laba6Dll\\x64\\Debug\\Laba6Dll.dll");
    //Turn turn = Turn();
    //turn.GetSize();
    if (dll != NULL)
    {
        void(Turn:: * constructor)();
        void(Turn:: * Push)(int);
        int(Turn:: * GetFirstEl)();
        int(Turn:: * GetSize)();
        (FARPROC&)constructor = GetProcAddress(dll, "??0Turn@@QEAA@XZ");
        (FARPROC&)Push = GetProcAddress(dll, "?Push@Turn@@QEAAXH@Z");
        (FARPROC&)GetSize = GetProcAddress(dll, "?GetSize@Turn@@QEAAHXZ");
        (FARPROC&)GetFirstEl = GetProcAddress(dll, "?GetFirstEl@Turn@@QEAAHXZ");
        std::cout << "Лабораторная работа №6\nВыполнил Едавкин С.И.\nГруппа 6215\n" << std::endl;
        Turn* turn = (Turn*)malloc(sizeof(Turn));
        (turn->*constructor)();
        printf("Вталкиваем элемент : % d в очередь\n", 20);
        (turn->*Push)(20);
        printf("Вталкиваем элемент : % d в очередь\n", 30);
        (turn->*Push)(30);
        printf("Получаем размер : % d \n", (turn->*GetSize)());
        printf("Получаем первый элемент : % d \n", (turn->*GetFirstEl)());
        FreeLibrary(dll);
        system("pause");
    }
    else
    {
        printf("Ошибка при загрузке dll\n");
        system("pause");
    }
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
