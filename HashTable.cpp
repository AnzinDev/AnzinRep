#include <iostream>
#include <vector>
#include <string>
#include <ios>

using namespace std;

class HashTable
{
private:

	class Row
	{
	public:

		int hash, count;
		string Data;
		Row* next;
		Row(string str = "nodata")
		{
			count = 0;
			hash = 0;
			Data = str;
			next = nullptr;
		}
	};

	vector<Row*> Heads;
	Row* head;

public:

	HashTable();
	~HashTable();

	int hash(const string& str);
	void add();
	void show();
};

HashTable::HashTable()
{
	head = nullptr;
	Heads.push_back(nullptr);
}


HashTable::~HashTable()
{
	for (int i = 0; i < Heads.size(); i++)
	{
		delete Heads[i];
	}
}

int HashTable::hash(const string& str)
{
	return str.length() + 1;
}

void HashTable::add()
{
	string tempStr;
	int hashVal;
	Row* newHead;
	cout << "Введите данные" << endl;
	getline(cin, tempStr);
	hashVal = hash(tempStr);
	if (*Heads.begin() != nullptr)
	{
		int p = 0;
		for (int i = 0; i < Heads.size(); i++)
		{
			if (Heads[i]->hash == hashVal)
			{
				p++;
				for (Row* temp = Heads[i]; ; temp = temp->next)
				{
					if (temp->next == nullptr)
					{
						temp->next = new Row(tempStr);
						cout << "Добавлено" << endl;
						break;
					}
				}
			}

		}
		if (p == 0)
		{
			newHead = new Row(tempStr);
			cout << "Добавлено" << endl;
			Heads.push_back(newHead);
			newHead->hash = hashVal;
		}
	}
	else
	{
		newHead = new Row(tempStr);
		cout << "Добавлено" << endl;
		*Heads.begin() = newHead;
		newHead->hash = hashVal;
	}
}


void HashTable::show()
{
	cout << "Хэш-таблица";
	if (*Heads.begin() == nullptr)
	{
		cout << endl << "Пустая таблица" << endl;
	}
	else
	{
		for (int i = 0; i < Heads.size(); i++)
		{
			cout << endl << "# " << Heads[i]->hash << " => ";
			for (Row* temp = Heads[i]; ; )
			{
				if (temp == nullptr)
				{
					break;
				}
				cout << temp->Data << ";  ";
				temp = temp->next;
			}
		}
	}
	cout << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");
	HashTable t1;
	int i = 5;
	while (i)
	{
		t1.add();
		i--;
	}
	t1.show();

	return 0;
}
