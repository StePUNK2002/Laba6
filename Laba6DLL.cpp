#include "pch.h"
#include <utility>
#include <limits.h>
#include "Laba6DLL.h"
#include "windows.h"

Turn::Turn()
{
	heaphandle = GetProcessHeap();
	size = 0;
	mass = (int*)HeapAlloc(heaphandle, HEAP_ZERO_MEMORY, size * sizeof(int));
}

Turn::Turn(const Turn& turn)
{
	heaphandle = GetProcessHeap();
	size = turn.size;
	mass = (int*)HeapAlloc(heaphandle, NULL, size * sizeof(int));
	for (int i = 0; i < size; i++)
	{
		mass[i] = turn.mass[i];
	}
}


void Turn::EjectionElemet() // �������� 1 ��������
{
	//�������� ������ ������ � ����������� � �����
	if (size == 0)
	{
		
	}
	else
	{
		HANDLE heap = GetProcessHeap();
		int newsize = size - 1;
		int* mass1 = (int*)HeapAlloc(heaphandle, HEAP_ZERO_MEMORY, newsize * sizeof(int));
		for (int i = 1; i < size; i++)
		{
			mass1[i - 1] = mass[i];
		}
		HeapFree(heaphandle, HEAP_NO_SERIALIZE, mass);
		size = newsize;
		mass = (int*)HeapAlloc(heaphandle, HEAP_ZERO_MEMORY, size * sizeof(int));
		for (int i = 0; i < size; i++)
		{
			mass[i] = mass1[i];
		}
		HeapFree(heap, HEAP_NO_SERIALIZE, mass1);
	}
}

int Turn::GetFirstEl() //��������� ������� ��������
{
	if (size == 0)
	{
		return 0;
	}
	else
	{
		return mass[0];
	}
}

int Turn::GetSize() //��������� ��������
{
	return size;
}

void Turn::WriteToFile() //������ � ����
{
	DWORD dwTemp;
	HANDLE hFile = CreateFile(L"file.dat", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile) {
		return;
	}
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	for (int i = 0; i < size; i++)
	{
		WriteFile(hFile, &(mass[i]), sizeof(int), &dwTemp, NULL);
	}
	CloseHandle(hFile);
}

Turn Turn::ReadFromFile()
{
	Turn turn;
	DWORD dwCounter, dwTemp;
	HANDLE hFile = CreateFile(L"file.dat", GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	DWORD dwEOF = SetFilePointer(hFile, 0, 0, FILE_END);
	SetFilePointer(hFile, 0, 0, FILE_BEGIN);
	while (SetFilePointer(hFile, 0, 0, FILE_CURRENT) < dwEOF)
	{
		ReadFile(hFile, &dwCounter, sizeof(dwCounter), &dwTemp, NULL);
		turn.Push(dwCounter);
	}
	CloseHandle(hFile);

	return turn;
}

void Turn::Push(int value) //����� ���������� �������� � �������
{
	if (size == 0)
	{
		HeapFree(heaphandle, HEAP_NO_SERIALIZE, mass);
		size = 1;
		mass = (int*)HeapAlloc(heaphandle, HEAP_ZERO_MEMORY, size * sizeof(int));
		mass[0] = value;
	}
	else
	{
		//�������� ������ ������ � ����������� � �����
		HANDLE heap = GetProcessHeap();
		int* mass1 = (int*)HeapAlloc(heaphandle, HEAP_ZERO_MEMORY, size * sizeof(int));
		for (int i = 0; i < size; i++)
		{
			mass1[i] = mass[i];
		}
		HeapFree(heaphandle, HEAP_NO_SERIALIZE, mass);
		size = size + 1;
		mass = (int*)HeapAlloc(heaphandle, HEAP_ZERO_MEMORY, size * sizeof(int));
		for (int i = 0; i < size; i++)
		{
			mass[i] = mass1[i];
		}
		mass[size - 1] = value;
		HeapFree(heap, HEAP_NO_SERIALIZE, mass1);
	}
}


Turn::~Turn()
{
	HeapFree(heaphandle, HEAP_NO_SERIALIZE, mass);
}
