/*
 * threadpool.cpp
 *
 *  Created on: Nov 13, 2021
 *      Author: pjarnot
 */

#include "include/threadpool.h"

#include <iostream>



ThreadPool::ThreadPool(int ithreadCount) {
	if (ithreadCount == 0) {
		threadCount = std::thread::hardware_concurrency();
	}
	else {
		threadCount = ithreadCount;
	}
	terminate = false;
	stopped = false;
	construct();
}


ThreadPool::ThreadPool() {
	threadCount = std::thread::hardware_concurrency();
	terminate = false;
	stopped = false;
	construct();
}


void ThreadPool::construct() {
	for (int i = 0; i < threadCount; ++i)
		workers.emplace_back([this] {
			while (true) {
				std::function < void() > task;

				{
					std::unique_lock < std::mutex > lock(this->queue_mutex);
					this->condition.wait(lock, [this] {
						return !this->tasks.empty() || this->terminate;
					});
					if (this->tasks.empty() && this->terminate)
						return;
					task = std::move(this->tasks.front());
					this->tasks.pop();
				}

				task();
			}
		}
		);
}


ThreadPool::~ThreadPool() {
	dispose();
}


void ThreadPool::dispose() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        terminate = true;
    }
    condition.notify_all();
    for(std::thread &worker: workers)
        worker.join();

    stopped = true;
}




int functionThread(int i) {
	std::cout << "hello " << i << std::endl;
	std::this_thread::sleep_for(std::chrono::seconds(1));
	std::cout << "world " << i << std::endl;
	return i*i;
}

void test_threadpool() {
    ThreadPool pool(4);
    std::vector< std::future<int> > results;

    for(int i = 0; i < 8; ++i) {
        results.emplace_back(
        		pool.enqueue(functionThread, i)
        );
    }

    for(auto && result: results)
        std::cout << result.get() << ' ';
    std::cout << std::endl;
}





