#include <iostream>
#include <fstream>
#include <ctime>
#include <string>

using namespace std;

template <typename T>
class SmartPtr
{
	T* ptr;

public:

	SmartPtr()
	{
		cout << "\t#SmartPtr constructor." << endl;
	}

	void in(T* ptr)
	{
		this->ptr = ptr;
	}

	T& operator[](int i)
	{
		
		return *(ptr + i);
	}

	~SmartPtr()
	{
		cout << "\t#SmartPtr destructor" << endl;
		delete ptr;
	}

	T& operator*()
	{
		return *ptr;
	}
};

SmartPtr<int> sptr;

class Image {

	int mx, my;
	int* data;

public:

	Image(int x, int y);
	int getMx();
	int getMy();
	int getSquare();
	void set(int i);
	void show();
	void putInFile();
};

Image::Image(int x, int y)
{
	mx = x;
	my = y;
	sptr.in(new int[x * y]);
}

int Image::getMx()
{
	return mx;
}

int Image::getMy()
{
	return my;
}

int Image::getSquare()
{
	return mx * my;
}

void Image::set(int i)
{
	sptr[i] = rand() % 2;
}

void Image::show()
{
	int p = 0;
	cout << "P1\n" << mx << " " << my << endl;
	for (int i = 0; i < this->getSquare(); i++)
	{
		cout << sptr[i];
		p++;
		if (p == mx)
		{
			cout << endl;
			p = 0;
		}
	}
}

void Image::putInFile()
{
	ofstream Input;
	string name, exp = ".txt";
	int p = 0;

	cout << "Enter file name" << endl;
	cin >> name;
	name = name + exp;
	Input.open(name);

	if (Input.is_open())
	{
		cout << endl << "Recording in file " << name << "..." << endl;
		Input << "P1\n";
		Input << mx << " " << my << "\n";
		for (int i = 0; i < this->getSquare(); i++)
		{
			Input << sptr[i];
			p++;
			if (p == mx) 
			{
				Input << "\n";
				p = 0;
			}
		}
	}
	else
	{
		cerr << "Can`t open file " << name << endl;
		exit(1);
	}

	Input.close();
}

int main() {

	int a = 10;

	Image img(a, a);

	srand(time(NULL));
	for (int i = 0; i < img.getSquare(); i++)
	{
		img.set(i);
	}

	img.show();
	img.putInFile();
	
	return 0;
}
