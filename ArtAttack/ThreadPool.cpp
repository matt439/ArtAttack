#include "pch.h"
#include "ThreadPool.h"

ThreadPool::ThreadPool(int num_threads)
{
	for (int i = 0; i < num_threads; i++)
	{
		this->_threads.push_back(std::jthread(&ThreadPool::thread_loop, this));
	}
}

ThreadPool::~ThreadPool()
{
	this->_stop = true;
	this->_condition.notify_all();
	for (auto& thread : this->_threads)
	{
		if (thread.joinable())
		{
			thread.join();
		}
	}
}

void ThreadPool::add_task(std::function<void()> task)
{
	std::scoped_lock lock(this->_mutex);
	this->_tasks.push(task);
	this->_condition.notify_one();
}

void ThreadPool::wait_for_tasks_to_complete()
{
	std::unique_lock lock(this->_mutex);
	this->_condition.wait(lock, [this] { return this->_tasks.empty(); });
}

void ThreadPool::thread_loop()
{
	while (!this->_stop)
	{
		std::function<void()> task;
		{
			std::unique_lock lock(this->_mutex);
			this->_condition.wait(lock, [this] { return this->_stop || !this->_tasks.empty(); });
			if (this->_stop)
			{
				return;
			}
			task = std::move(this->_tasks.front());
			this->_tasks.pop();
		}
		task();
	}
}
