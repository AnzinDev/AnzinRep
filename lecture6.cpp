#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <chrono>

using namespace std;

mutex mtx;

void addition(vector<int>& container)
{
	const lock_guard<mutex> mtxLock(mtx);
	this_thread::sleep_for(chrono::milliseconds(1));
	for (int i = 0; i < 10; i++)
	{
		cout << this_thread::get_id() << " add" << endl;
		container[i] = i;
	}
}

void read(vector<int>& container)
{
	const lock_guard<mutex> mtxLock(mtx);
	this_thread::sleep_for(chrono::milliseconds(1));
	for (int i = 0; i < 10; i++)
	{
		cout << this_thread::get_id() << "\t" << container[i] << endl;
	}
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

