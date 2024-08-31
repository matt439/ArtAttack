#ifndef THREAD_POOL_H
#define THREAD_POOL_H

#include <thread>
#include <vector>
#include <queue>
#include <condition_variable>


class ThreadPool final
{
public:
	ThreadPool(int num_threads);
	~ThreadPool();
	void add_task(std::function<void()> task);
	void wait_for_tasks_to_complete();
	int get_num_threads() const;
private:
	std::vector<std::jthread> _threads;
	std::queue<std::function<void()>> _tasks;
	std::condition_variable _condition;
	std::mutex _mutex;
	bool _stop = false;
	void thread_loop();
};

#endif // !THREAD_POOL_H
