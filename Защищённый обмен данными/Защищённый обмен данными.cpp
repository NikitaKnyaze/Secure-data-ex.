#include <mutex>
#include <iostream>
#include <Windows.h>

class Data
{
public:
	int value{};
	std::mutex m;
	
		Data(int v) : value(v) {};
};

void swap(int& a, int& b)
{
	int temp = a;
	a = b;
	b = temp;
}

void swap_lock(Data& a, Data& b)
{
	std::lock(a.m, b.m);
	std::lock_guard<std::mutex> lock_a(a.m, std::adopt_lock);
	std::lock_guard<std::mutex> lock_b(b.m, std::adopt_lock);
	swap(a.value, b.value);
}

void swap_scoped_lock(Data& a, Data& b)
{
	std::scoped_lock <std::mutex, std::mutex> lock (a.m, b.m);
	swap(a.value, b.value);
}

void swap_unique_lock(Data& a, Data& b)
{
	std::unique_lock<std::mutex> lock_a(a.m);
	std::unique_lock<std::mutex> lock_b(b.m);

	swap(a.value, b.value);
}

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
    
	Data d1(1);
	Data d2(4);

	std::cout << "До swap: а=" << d1.value << " b=" << d2.value << std::endl; 

	/*swap_lock(d1, d2);
	std::cout << "После swap_lock: а=" << d1.value<<" b="<<d2.value<<std::endl;*/

	/*swap_scoped_lock(d1, d2);
	std::cout << "После swap_scoped_lock: а=" << d1.value << " b=" << d2.value << std::endl;*/
	
	swap_unique_lock(d1, d2);
	std::cout << "После swap_unique_lock: а=" << d1.value << " b=" << d2.value << std::endl;

	return EXIT_SUCCESS;
}

