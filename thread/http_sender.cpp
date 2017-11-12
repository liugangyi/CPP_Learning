#include "http_sender.h"
#include <iostream>



http_sender::http_sender():m_thread(bind(&http_sender::do_task, this))
						  ,m_exit(false)
{
}


http_sender::~http_sender()
{
}

void http_sender::do_task()
{
	cout << "do_task" << endl;
	while (!m_exit)
	{
		pair<char*, int> task = get_task();
		cout << "do_task: " << task.second << endl;
	}

	cout << "http_sender quit" << endl;
}

void http_sender::add_task(pair<char*, int> content)
{
	{
		lock_guard<mutex> lock(m_mutex);
		cout << "add_task: " << content.second << endl;
		m_queue.push(content); 
	}
	m_condition.notify_all();
	this_thread::yield();
}

void http_sender::quit()
{
	m_exit = true;
	m_condition.notify_all();
	m_thread.join();
}

pair<char*, int> http_sender::get_task()
{
	unique_lock<mutex> lock(m_mutex);
	if (m_queue.empty()) m_condition.wait(lock);
	//m_condition.wait(lock, [&]() {return m_exit || !m_queue.empty();});
	pair<char*, int> task(nullptr, -1);
	if (m_exit || m_queue.empty()) return task;

	task = m_queue.front();
	m_queue.pop();
	cout << "get_task: " << task.second << endl;
	return task;
}
