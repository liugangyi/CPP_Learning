#pragma once

#include <mutex>
#include <condition_variable>
#include <thread>
#include <queue>
#include <chrono>
#include <string>
using namespace std;

class http_sender
{
public:
	http_sender();
	~http_sender();

public:
	void add_task(pair<char*, int> content);
	void quit();

private:
	void do_task();
	pair<char*, int> get_task();

private:
	thread m_thread;
	mutex m_mutex;
	condition_variable m_condition;
	queue<pair<char*, int>> m_queue;
	bool m_exit;
};
