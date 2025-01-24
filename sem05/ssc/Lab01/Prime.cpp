#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <iostream>

unsigned long *numbers;

typedef struct MyData
{
	unsigned long start;
	unsigned long len;
} MYDATA, *PMYDATA;

DWORD WINAPI MyThreadFunction(LPVOID lpParam);
void RunNoThreads(unsigned long len);
void RunOnThreads(unsigned long len, int32_t threadCount);

int isPrime(unsigned long n)
{

	for (unsigned long i = 2; i < n; i++)
	{
		if (n % i == 0)
			return 0;
	}
	return 1;
}

int main(int argc, char *argv[])
{
	unsigned long upperLimit, arrayLength, threadCount = 0;

	clock_t startTime = 0;
	clock_t elapsedTime = 0;

	if (argc != 3)
	{
		printf("Provide the upper limit: ");
		scanf("%lu", &upperLimit);

		printf("Provide the number of threads: ");
		scanf("%lu", &threadCount);
	}
	else
	{
		upperLimit = atol(argv[1]);
		threadCount = atol(argv[2]);
	}

	arrayLength = upperLimit - 1;

	numbers = new unsigned long[arrayLength];

	for (int i = 0; i < arrayLength; i++)
	{
		numbers[i] = i + 2;
	}

	if (threadCount == 0)
	{
		RunNoThreads(arrayLength);
	}
	else
	{
		RunOnThreads(arrayLength, threadCount);
	}

	delete[] numbers;

	return 0;
}

DWORD WINAPI MyThreadFunction(LPVOID lpParam)
{
	PMYDATA pDataArray;
	pDataArray = (PMYDATA)lpParam;

	unsigned long k, j = 0;
	for (k = pDataArray->start; k < pDataArray->start + pDataArray->len; k++)
	{
		if (isPrime(numbers[k]) == 1)
		{
			for (j = 2 * numbers[k] - 2; j < pDataArray->len; j += numbers[k])
			{
				numbers[j] = 0;
			}
		}
		else
		{
			numbers[k] = 0;
		}
	}
	return 0;
}

void RunNoThreads(unsigned long len)
{
	MYDATA pData = {0};
	pData.len = len;
	pData.start = 0;

	clock_t startTime = clock();
	MyThreadFunction(&pData);
	clock_t elapsedTime = clock() - startTime;

	std::cout << (float)elapsedTime / CLOCKS_PER_SEC << "sec" << std::endl;
}

void RunOnThreads(unsigned long len, int32_t threadCount)
{
	PHANDLE threadArray = new HANDLE[threadCount];
	PDWORD threadIdArray = new DWORD[threadCount];
	PMYDATA *dataArray = new PMYDATA[threadCount];

	clock_t startTime = clock();

	for (int i = 0; i < threadCount; i++)
	{
		dataArray[i] = (PMYDATA)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(MYDATA));
		dataArray[i]->len = len / threadCount;
		dataArray[i]->start = i * len / threadCount;
		if (i == threadCount - 1)
		{
			dataArray[i]->len += len - (len / threadCount + i * len / threadCount);
		}
		threadArray[i] = CreateThread(NULL, 0, MyThreadFunction, dataArray[i], 0, &threadIdArray[i]);
	}

	WaitForMultipleObjects(threadCount, threadArray, TRUE, INFINITE);

	clock_t elapsedTime = clock() - startTime;
	std::cout << (float)elapsedTime / CLOCKS_PER_SEC << "sec" << std::endl;

	for (int i = 0; i < threadCount; i++)
	{
		CloseHandle(threadArray[i]);

		if (dataArray[i] != NULL)
		{
			HeapFree(GetProcessHeap(), 0, dataArray[i]);
			dataArray[i] = NULL;
		}
	}

	delete[] threadArray;
	delete[] threadIdArray;
	delete[] dataArray;
}