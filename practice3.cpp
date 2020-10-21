#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <thread>
#include <ctime>
#include <cmath>
#include <fstream>

using namespace std;

void gystConst(int* g, int** image, int start, int end)
{
	for (int i = start; i <= end; i++)
	{
		for (int k = 0; k < 10000; k++)
		{
			g[image[i][k]] += 1;
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	clock_t start1, start2, start3, end1, end2, end3;
	start2 = clock();
	int p = 1;
	int** image = new int* [20];
	for (int i = 0; i < 20; i++)
	{
		image[i] = new int[10000];
	}

	int g[256] = { 2 };
	srand(time(NULL));
	for (int i = 0; i < 20; i++)
	{
		for (int k = 0; k < 10000; k++)
		{
			image[i][k] = rand() % 256;
		}
	}
	cout << "20x10000 dot picture" << endl;
	start1 = clock();
	thread th1(gystConst, g, image, 0, 0);
	thread th2(gystConst, g, image, 1, 1);
	thread th3(gystConst, g, image, 2, 2);
	thread th4(gystConst, g, image, 3, 3);
	thread th5(gystConst, g, image, 4, 4);
	thread th6(gystConst, g, image, 5, 5);
	thread th7(gystConst, g, image, 6, 6);
	thread th8(gystConst, g, image, 7, 7);
	thread th9(gystConst, g, image, 8, 8);
	thread th10(gystConst, g, image, 9, 9);
	thread th11(gystConst, g, image, 10, 10);
	thread th12(gystConst, g, image, 11, 11);
	thread th13(gystConst, g, image, 12, 12);
	thread th14(gystConst, g, image, 13, 13);
	thread th15(gystConst, g, image, 14, 14);
	thread th16(gystConst, g, image, 15, 15);
	thread th17(gystConst, g, image, 16, 16);
	thread th18(gystConst, g, image, 17, 17);
	thread th19(gystConst, g, image, 18, 18);
	thread th20(gystConst, g, image, 19, 19);
	th1.join();
	th2.join();
	th3.join();
	th4.join();
	th5.join();
	th6.join();
	th7.join();
	th8.join();
	th9.join();
	th10.join();
	th11.join();
	th12.join();
	th13.join();
	th14.join();
	th15.join();
	th16.join();
	th17.join();
	th18.join();
	th19.join();
	th20.join();
	end1 = clock();
	start3 = clock();
	cout << "10 scope scale" << endl;
	for (int i = 0; i <= 255; i++)
	{
		g[i] = (int)(g[i] / 10);
		cout << i << " ";
		for (; g[i] > 0; )
		{
			cout << "#";
			g[i]--;
		}
		cout << endl;
	}
	end3 = clock();
	for (int i = 0; i < 20; i++)
	{
		delete[] image[i];
	}
	delete[] image;

	cout << "threads time = " << ((double)end1 - start1) / ((double)CLOCKS_PER_SEC) << endl;
	cout << "gyst out time = " << ((double)end3 - start3) / ((double)CLOCKS_PER_SEC) << endl;
	end2 = clock();
	cout << "full time = " << ((double)end2 - start2) / ((double)CLOCKS_PER_SEC) << endl;
	cout << "20x10000 dot picture" << endl;
	cout << "hardware concurency = " << thread::hardware_concurrency() << endl;
	//Тесты разного количества потоков производились один за другим
	//отсутствие какой-либо видимой зависимости могу объяснить малым временем выполнения потока
	//в теории, после превышения значения hardware concurency для данной машины должно 
	//увеличиваться время выполнения всех потоков из-за частого переключения выполнения задач 
	//между потоками процессора
	cout << "++-------------------------------------------++" << endl;
	cout << "||threads|  1  |  2  |  4  |  5  |  10 |  20 ||" << endl;
	cout << "|+-------------------------------------------+|" << endl;
	cout << "||time   |0.004|0.003|0.004|0.003|0.004|0.005||" << endl;
	cout << "++-------------------------------------------++" << endl;
	return 0;
}
