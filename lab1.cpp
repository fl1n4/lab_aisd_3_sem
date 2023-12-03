#pragma once
#include <cstdlib>
#include <ctime>
#include <utility>
#include <iostream>
using namespace std;

template<typename T1>
class Set
{
private:
	T1* items;
	int size;
public:
	//consructors and destructor
	Set();
	Set(const Set<T1>& other);
	Set(int _size);
	Set(int _size, T1 min, T1 max);
	~Set();
	//methods
	bool contains(const T1& item) const;
	void add(const T1& item);
	void remove(const T1& item);
	int Size();

	//operators
	T1 operator[](int index);
	Set<T1> operator+(const Set<T1>& other) const;
	Set<T1>& operator+=(const Set<T1>& other);
	Set<T1> operator+(const T1& element) const;
	Set<T1>& operator+=(const T1& element);
	Set<T1> operator-(const Set<T1>& other) const;
	Set<T1>& operator-=(const Set<T1>& other);
	Set<T1> operator-(const T1& element) const;
	Set<T1>& operator-=(const T1& element);
	Set<T1>& operator=(const Set<T1>& other);
	friend ostream& operator<<(ostream& os, const Set<T1>& set)
	{
		os << "{";
		for (int i = 0; i < set.size; ++i) {
			os << set.items[i];
			if (i < set.size - 1) {
				os << ", ";
			}
		}
		os << "}";
		return os;
	}
};

//constructors and destructor
template<typename T1>
Set<T1>::Set()
{
	items = nullptr;
	size = 0;
}
template<typename T1>
Set<T1>::Set(int _size)
{
	if (_size)
	{
		items = new T1[_size];
		size = _size;
	}
}
template <typename T1>
Set<T1>::Set(const Set<T1>& other)
{
	size = other.size;
	items = new T1[size];

	for (int i = 0; i < size; ++i)
	{
		items[i] = other.items[i];
	}
}
template<typename T1>
Set<T1>::Set(int _size, T1 min, T1 max) : size(0), items(nullptr)
{
	if (_size > 0)
	{
		size = _size;
		items = new T1[size];
		srand(static_cast<unsigned>(time(nullptr)));
		T1 temp;
		for (int i = 0; i < size; ++i)
		{
			temp = static_cast<T1>(min + rand() / (RAND_MAX / (max - min + 1.0)));
			if (!contains(temp))
			{
				items[i] = temp;
			}
			else
			{
				i--;
			}
		}
	}
}

template<typename T1>
Set<T1>::~Set()
{
	delete[] items;
}
//methods
template<typename T1>
bool Set<T1>::contains(const T1& item) const
{
	for (int i = 0; i < size; ++i)
	{
		if (items[i] == item)
		{
			return true;
		}
	}
	return false;
}
template<typename T1>
void Set<T1>::add(const T1& item)
{
	if (!contains(item))
	{
		T1* newElements = new T1[size + 1];
		for (int i = 0; i < size; ++i)
		{
			newElements[i] = items[i];
		}
		newElements[size] = item;
		delete[] items;
		items = newElements;
		size += 1;
	}
}
template<typename T1>
void Set<T1>::remove(const T1& item)
{
	if (contains(item))
	{
		T1* newElements = new T1[size - 1];
		int newIndex = 0;
		for (int i = 0; i < size; ++i)
		{
			if (items[i] != item)
			{
				newElements[newIndex] = items[i];
				newIndex++;
			}
		}
		delete[] items;
		items = newElements;
		size -= 1;
	}
}
template<typename T1>
Set<T1> intersection(const Set<T1>& set1, const Set<T1>& set2)
{
	Set<T1> result;
	result = set1 + set2 - (set1 - set2) - (set2 - set1);
	return result;
}
template<typename T1>
Set<T1> exclusiveOr(const Set<T1>& set1, const Set<T1>& set2)
{
	Set<T1> result;
	result = ((set1 + set2) - set1) + ((set1 + set2) - set2);
	return result;
}
//operators
template<typename T1>
T1 Set<T1>::operator[](int index)
{
	if (index > size)
	{
		throw invalid_argument("Invalid index");
	}
	return items[index];
}
template<typename T1>
Set<T1> Set<T1>::operator+(const Set<T1>& other) const
{
	Set<T1> result(*this);
	result += other;
	return result;
}
template <typename T1>
Set<T1>& Set<T1>::operator+=(const Set<T1>& other)
{
	for (int i = 0; i < other.size; ++i)
	{
		add(other.items[i]);
	}
	return *this;
}
template<typename T1>
Set<T1> Set<T1>::operator+(const T1& element) const
{
	Set<T1> result(*this);
	result.add(element);
	return result;
}
template <typename T1>
Set<T1>& Set<T1>::operator+=(const T1& element)
{
	add(element);
	return *this;
}

template <typename T1>
Set<T1>& Set<T1>::operator-=(const Set<T1>& other)
{
	for (int i = 0; i < other.size; ++i)
	{
		remove(other.items[i]);
	}
	return *this;
}
template <typename T1>
Set<T1> Set<T1>::operator-(const Set<T1>& other) const
{
	Set<T1> result(*this);
	result -= other;
	return result;
}
template <typename T1>
Set<T1> Set<T1>::operator-(const T1& element) const
{
	Set<T1> result(*this);
	result.remove(element);
	return result;
}
template <typename T1>
Set<T1>& Set<T1>::operator-=(const T1& element)
{
	remove(element);
	return *this;
}
template<typename T1>
Set<T1>& Set<T1>::operator=(const Set<T1>& other)
{
	if (this == &other)
	{
		return *this;
	}
	delete[] items;
	size = other.size;
	items = new T1[size];
	for (int i = 0; i < size; ++i)
	{
		items[i] = other.items[i];
	}
	return *this;
}
template<typename T1>
int Set<T1>::Size()
{
	return size;
}
template<typename T1, typename T2>
void printPair(const pair<T1, T2>& pair)
{
	cout << "(" << pair.first << ", " << pair.second << ")";
}

int main()
{
	//int
	Set<int> int_set1(5, 0, 10);
	Set<int> int_set2(5, 6, 15);
	Set<int> int_set3 = int_set1 + int_set2;
	cout << "-----------INT----------" << endl;
	cout << "set1: " << int_set1 << endl << "size set1: " << int_set1.Size() << endl << endl;
	cout << "set2: " << int_set2 << endl << "size set2: " << int_set2.Size() << endl << endl;
	int_set3 = int_set1 - int_set2;
	cout << "set1-set2: " << int_set3 << endl << "size set1-set2: " << int_set3.Size() << endl << endl;
	int_set3 = int_set1 + int_set2;
	cout << "set1+set2: " << int_set3 << endl << endl;
	cout << "Result intersection: " << intersection(int_set1,int_set2) << endl << endl;
	cout << "Result XOR: " << exclusiveOr(int_set1,int_set2) << endl << endl;
	//float
	Set<float> float_set1(5, 0.0, 10.0);
	Set<float> float_set2(5, 6.0, 15.0);
	Set<float> float_set3 = float_set1 + float_set2;
	cout << "---------FLOAT----------" << endl;
	cout << "set1: " << float_set1 << endl << "size set1: " << float_set1.Size() << endl << endl;
	cout << "set2: " << float_set2 << endl << "size set2: " << float_set2.Size() << endl << endl;
	float_set3 = float_set1 - float_set2;
	cout << "set1-set2: " << float_set3 << endl << "size set1-set2: " << float_set3.Size() << endl << endl;
	float_set3 = float_set1 + float_set2;
	cout << "set1+set2: " << float_set3 << endl << endl;
	cout << "Result intersection: " << intersection(float_set1,float_set2) << endl << endl;
	cout << "Result XOR: " << exclusiveOr(float_set1,float_set2) << endl << endl;
	//string
	Set<string> string_set1;
	Set<string> string_set2;
	Set<string> string_set3;
	string_set1.add("Sydney");
	string_set1.add("Tokyo");
	string_set1.add("Toronto");
	string_set1.add("London");
	string_set2.add("Paris");
	string_set2.add("Tokyo");
	string_set2.add("Toronto");
	string_set2.add("New York");
	cout << "---------STRING----------" << endl;
	cout << "set1: " << string_set1 << endl << "size set1: " << string_set1.Size() << endl << endl;
	cout << "set2: " << string_set2 << endl << "size set2: " << string_set2.Size() << endl << endl;
	string_set3 = string_set1 + string_set2;
	cout << "set1+set2: " << string_set3 << endl << "size set1+set2: " << string_set3.Size() << endl << endl;
	string_set3 = string_set1 - string_set2;
	cout << "set1-set2: " << string_set3 << endl << "size set1-set2: " << string_set3.Size() << endl << endl;
	cout << "Result intersection: " << intersection(string_set1,string_set2) << endl << endl;
	cout << "Result XOR: " << exclusiveOr(string_set1,string_set2) << endl << endl;
	//pair
	Set<pair<double, int>> pair_set1;
	Set<pair<double, int>> pair_set2;
	Set<pair<double, int>> pair_set3;

	pair_set1.add(make_pair(3.14, 5));
	pair_set1.add(make_pair(14.2, 3));
	pair_set1.add(make_pair(32.2, 7));
	pair_set1.add(make_pair(2.5, 67));
	pair_set1.add(make_pair(13.37, 1));

	pair_set2.add(make_pair(3.21, 5));
	pair_set2.add(make_pair(3.2, 3));
	pair_set2.add(make_pair(32.2, 7));
	pair_set2.add(make_pair(13.37, 1));
	pair_set2.add(make_pair(2.12, 45));

	cout << "----------PAIR----------" << endl;
	cout << "pairSet1: {";
	for (int i = 0; i < pair_set1.Size(); ++i)
	{
		printPair(pair_set1[i]);
		if (i < pair_set1.Size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
	cout << "size set1: " << pair_set1.Size() << endl << endl;
	cout << "pairSet2: {";
	for (int i = 0; i < pair_set2.Size(); ++i)
	{
		printPair(pair_set2[i]);
		if (i < pair_set2.Size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
	cout << "size set2: " << pair_set2.Size() << endl << endl;
	pair_set3 = pair_set1 + pair_set2;
	cout << "set1+set2: {";
	for (int i = 0; i < pair_set3.Size(); ++i)
	{
		printPair(pair_set3[i]);
		if (i < pair_set3.Size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
	cout << "size set1+set2: " << pair_set3.Size() << endl << endl;
	pair_set3 = pair_set1 - pair_set2;
	cout << "set1-set2: {";
	for (int i = 0; i < pair_set3.Size(); ++i)
	{
		printPair(pair_set3[i]);
		if (i < pair_set3.Size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
	cout << "size set1-set2: " << pair_set3.Size() << endl << endl;
	cout << "Result intersection: {";
	pair_set3=intersection(pair_set1,pair_set2);
	for (int i = 0; i < pair_set3.Size(); ++i)
	{
		printPair(pair_set3[i]);
		if (i < pair_set3.Size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
	cout << endl;
	cout << "Result XOR: {";
	pair_set3 = exclusiveOr(pair_set1,pair_set2);
	for (int i = 0; i < pair_set3.Size(); ++i)
	{
		printPair(pair_set3[i]);
		if (i < pair_set3.Size() - 1)
		{
			cout << ", ";
		}
	}
	cout << "}" << endl;
	cout << endl;
}