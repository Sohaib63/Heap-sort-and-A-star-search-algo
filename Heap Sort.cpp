// Heap Sort.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include<iostream>
#include<cmath>
#include<stdlib.h>
#include<ctime>
#include <chrono>
using namespace std;
template <typename objects>
class vector
{
private:
	int thesize;
	int thecapacity;
	objects* object;
public:
	explicit vector(int size = 0) :thesize(0), thecapacity(size + 4), object(new objects[thecapacity])
	{}
	void push_back(const objects&);
	void popback();
	void reserve(int);
	void print();
	int size() const;
	objects& operator[](int);
	typedef objects* iterator;
	iterator begin() const
	{
		return &object[0];
	}
	iterator end() const
	{
		return &object[thesize];
	}
	objects operator *(int i)
	{
		return *(this->object + i);
	}
	~vector()
	{
		delete[]object;
	}
};
template <typename objects>
int vector<objects>::size() const
{
	return this->thesize;
}
template <typename objects>
void vector<objects>::push_back(const objects& that)
{
	if (this->thesize == thecapacity)
		reserve(2 * thecapacity + 1);
	object[thesize++] = that;
}
template <typename objects>
void vector<objects>::popback()
{
	if (thesize == 0)
		return;
	--thesize;
}
template <typename objects>
void vector<objects>::reserve(int newcapacity)
{
	if (newcapacity < thecapacity)
		return;
	objects* oldarray = new objects[newcapacity];
	for (size_t i = 0; i < thesize; i++)
		oldarray[i] = object[i];
	thecapacity = newcapacity;
	delete[] object;
	object = oldarray;
}
template <typename objects>
void vector<objects>::print()
{
	for (size_t i = 0; i < thesize; i++)
	{
		cout << object[i] << endl;
	}
}
template <typename objects>
objects& vector<objects>::operator[](int i)
{
	return object[i];
}
using namespace std::chrono;
using namespace std;
template<typename T>
void removemax(T*);
template<typename E>
class Less {
public:
	bool operator()(const E& left, const E& right)
	{
		return left < right;
	}
};

template<typename T>
T* pos(int i, T*);
template<typename T>
void upheapbubbling(T*);
template<typename T>
int idx(T*);
vector<int> object;
int main()
{
	
	int random_integer;
	int lowest = -1000, highest = 1000;
	srand((unsigned)time(0));
	for (int i = 0; i <100; ++i)
	{
		random_integer = lowest + (rand() % (highest - lowest+1));
		object.push_back(random_integer);
 	}
	auto start = high_resolution_clock::now();

	for (int i = 1; i <= object.size(); i++)
	{
		upheapbubbling(&object[i - 1]);
	}
	for (int i = 1; i <= object.size(); i++)
	{
		removemax(&object[object.size() - i]);
	}
	auto stop = high_resolution_clock::now();
	
	auto duration = duration_cast<milliseconds>(stop - start);
	cout <<"time taken:"<< duration.count() << endl;
	for (auto it : object)
	{
		cout << it << endl;
	}
}
template<typename T>
bool hasRight(T* p, int i)
{
	return (2 * idx(p) + 2) < i;
}
template<typename T>
bool hasLeft(T* p, int i)
{
	return (2 * idx(p) + 1) < i;
}
template<typename T>
int idx(T* p)
{
	return p - object.begin();
}
template<typename T>
T* pos(int i, T* p)
{
	return  object.begin() + i;
}
template<typename T>
T* parent(T* p)
{
	if (idx(p) % 2 == 0)
		return pos(floor(((idx(p) - 1) / 2.0)), p);
	return pos(floor(idx(p) / 2.0), p);
}
template<typename T>
void swap(T* p, T* q)
{
	T e = *q; *q = *p; *p = e;
}
template<typename T>
T* left(T* p)
{
	return pos(((2 * idx(p)) + (1)), p);
}
template<typename T>
T* right(T* p)
{
	return pos((2 * idx(p) + 2), p);
}
template<typename T>
void removemax(T* p)
{
	Less<T> isLess;
	int i = idx(p);
	swap(&object[0], &object[i]);
	int j = 0;
	while (hasLeft(&object[j], i) || hasRight(&object[j], i))
	{
		T* s = left(&object[j]);
		if (hasRight(&object[j], i) && isless(*s, *right(&object[j])))
			s = right(&object[j]);
		if (isless(object[j], *s))
		{
			swap(&object[j], s);
			j = idx(s);
		}
		else
			break;

	}
}
template<typename T>
void upheapbubbling(T* last)
{
	if (idx(last) == 0)
		return;
	Less<T> isLess;
	while (idx(last) != 0)
	{

		T* par = parent(last);
		if (isLess(*par, *last))
		{
			swap(par, last);
			last = par;
		}
		else {
			break;
		}

	}
}
// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
