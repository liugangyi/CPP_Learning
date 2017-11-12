#include "http_sender.h"
#include <iostream>
#include <string>
#include <thread>
#include <chrono>

void test_thread();

int main()
{
	test_thread();
	return 0;
}

void test_thread()
{
	http_sender con;

	for (size_t i = 0; i < 100; i++)
	{
		con.add_task(make_pair(nullptr, int(i)));
		this_thread::sleep_for(chrono::milliseconds(1));
	}

	con.quit();

	cout << "main quit" << endl;

	system("pause");
}