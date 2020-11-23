#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx1, mtx2;

void addition(vector<int>& container)
{
	mtx1.lock();
	this_thread::sleep_for(chrono::milliseconds(1));
	mtx2.lock();
	for (int i = 0; i < 10; i++)
	{
		cout << this_thread::get_id() << " add" << endl;
		container[i] = i;
	}
	mtx1.unlock();
	mtx2.unlock();
}

void read(vector<int>& container)
{
	mtx1.lock();
	this_thread::sleep_for(chrono::milliseconds(1));
	mtx2.lock();
	for (int i = 0; i < 10; i++)
	{
		cout << this_thread::get_id() << "\t" << container[i] << endl;
	}
	mtx1.unlock();
	mtx2.unlock();
}

int main()
{
	vector<int> container(10, -1);

	thread t1(addition, ref(container));

	thread t2(read, ref(container));

	t1.join();
	t2.join();

	return 0;
}
