#include <iostream>
#include <cstring>
#include "Header.h"
using namespace std;

class MyString
{
private:
	char* str; 
	int length; 
	static int obj_count;
public:
	MyString();
	MyString(const char*);
	MyString(const MyString&);
	~MyString();
	static void ObjCount();
	void Init();
	void Print();
	void MyStrcpy(const MyString& obj);
	bool MyStrStr(const char* Substr);
	int  MyChr(char c);
	int MyStrLen();
	void MyStrCat(const MyString& b);
	void MyDelChr(char c);
	int MyStrCmp(const MyString& b);
	MyString& operator=(const MyString& b);
	void operator()();
	char operator[](int index);
	operator int();
	operator char* ();
	MyString(MyString&& b)
	{
		str = b.str;
		b.str = nullptr;
	}
	MyString& operator=(MyString&& b)
	{
		cout << "Движение = \n";
		this->str = b.str;
		b.str = nullptr;
		return *this;
	}
	MyString(initializer_list<char> a);
};
int MyString::obj_count = 0;

MyString::MyString()
{
	length = 80;
	str[length];
	obj_count++;
}

MyString::MyString(const char* text)
{
	if (text == nullptr)
		throw new NullException("Указатель без даных\n");
	str = new char[strlen(text) + 1];
	strcpy_s(str, strlen(text) + 1, text);
	length = strlen(text);
	obj_count++;
}
//MyString::MyString(const MyString& obj)
//{
//	str = new char[strlen(obj.str) + 1];
//	strcpy_s(str, strlen(obj.str) + 1, obj.str);
//	length = strlen(obj.str);
//	obj_count++;
//}

MyString::~MyString()
{
	cout << endl << "Дескриптор" << endl;
	delete[]str;
}

void MyString::Print()
{
	cout << "Символы: " << str << "\tДлина: " << length << endl;
}

void MyString::Init()
{
	char* text = new char[length];
	cout << "Введите симолы -> ";
	cin >> text;
	if (str != nullptr)
	{
		delete[]str;
	}
	str = new char[strlen(text) + 1];
	strcpy_s(str, strlen(text) + 1, text);
	length = strlen(str);
	obj_count++;
	delete[]text;
}

void MyString::MyStrcpy(const MyString& obj)
{
	if (str != nullptr)
	{
		delete[]str;
	}
	str = new char[strlen(obj.str) + 1];
	strcpy_s(str, strlen(obj.str) + 1, obj.str);
	length = strlen(obj.str);
}

bool MyString::MyStrStr(const char* Substr)
{
	return strstr(str, Substr);
}

int MyString::MyChr(char c)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == c)
			cout << i << " ";
		else
			continue;
	}
	return 0;
}

int MyString::MyStrLen()
{
	return strlen(str);
}

void MyString::MyStrCat(const MyString& b)
{
	strcat_s(str, strlen(str) + strlen(b.str) + 1, b.str);
	length = strlen(str);
}

void MyString::MyDelChr(char c)
{
	if (length == 0)
		throw new SizeException("Размер строки не равен нулю");
	int count = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == c)
			continue;
		else
			count++;
	}
	count++;
	char* buf = new char[count];
	int count2 = 0;
	for (int i = 0; i < strlen(str); i++)
	{
		if (str[i] == c)
			continue;
		else
		{
			buf[count2] = str[i];
			count2++;
		}
	}
	delete[]str;
	str = new char[count];
	strcpy_s(str, strlen(buf) + 1, buf);
	length = strlen(str);
	delete[]buff;
}

int MyString::MyStrCmp(const MyString& b)
{
	if (strlen(str) > strlen(b.str))
		return 1;
	else if (strlen(str) < strlen(b.str))
		return -1;
	else
		return 0;
}

MyString& MyString::operator=(const MyString& b)
{
	if (str == b.str)
	{
		return *this;
	}
	if (str != nullptr)
	{
		delete[]str;
	}
	str = new char[strlen(b.str) + 1];
	strcpy_s(str, strlen(b.str) + 1, b.str);
	length = strlen(b.str);
	return *this;
}

void MyString::operator()()
{
	cout << "Симолы: " << str << "\tДлина: " << length << endl;
}
char MyString::operator[](int index)
{
	if (index < 0 || index >= length)
		throw new IndexException("Индекс за массив\n");
	if (index >= 0 && index < strlen(str))
		return str[index];
	else
		return '\0';
}
MyString::operator int()
{
	return length;
}
MyString::operator char* ()
{
	return str;
}
MyString::MyString(initializer_list<char> a)
{
	length = a.size();
	str = new char[length];
	for (int i = 0; i < a.size(); i++)
	{
		str[i] = a.begin()[i];
	}
}
void MyString::ObjCount()
{
	cout << "Счетчик объекта = " << obj_count << endl;
}

int main()
{
	setlocale(LC_ALL, "ru");
	MyString obj1("Hello World");
	MyString obj_nol("");
	char c = '\0';
	const char* ptr_null = nullptr;
	try
	{
		MyString obj2(ptr_null);
		obj_nol.MyDelChr(c);
		cout << obj1[-1];
	}
	catch (BaseException* b)
	{
		b->Print();
	}
}