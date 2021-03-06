// ConditionVariables.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mutex>
#include <string>
#include <condition_variable>
#include <iostream>
#include <vector>

void test1()
{
	std::string message;
	std::mutex m;
	std::condition_variable cond_var;
	bool done = false;

	std::thread producer([&]() {
		while (true) {
			std::unique_lock<std::mutex> lock(m);
			cond_var.wait(lock);
			std::getline(std::cin, message);
			if (message == "X")
			{
				done = true;
				break;
			}

			cond_var.notify_one();
		}

		done = true;
		cond_var.notify_one();
	});

	std::thread consumer([&]() {
		std::unique_lock<std::mutex> lock(m);
		cond_var.notify_one();
		std::cout << "Start chatting:" << std::endl;
		while (!done) {
			cond_var.wait(lock);
			std::cout << "[Consumer] Received message: " << message << "\n";
			cond_var.notify_one();
		}
	});

	producer.join();
	consumer.join();
}

void test2()
{
	std::mutex mtx;
	std::condition_variable cv;
	bool ready = false;

	auto waiter = [&](int id) {
		std::unique_lock<std::mutex> lck(mtx);
		while (!ready) cv.wait(lck);
		std::cout << "thread " << id << '\n';
	};

	auto starter = [&]() {
		std::cout << "Ready? GO!\n";

		std::unique_lock<std::mutex> lck(mtx);
		ready = true;
		cv.notify_all();
	};

	std::vector<std::thread> threads;
	for(int i = 0; i < 10; i++)
	{
		threads.push_back(std::thread{ waiter, i });
	}

	std::thread go { starter };
	for (auto& t : threads)
		t.join();

	go.join();
}

int main()
{
	test1();
	test2();
}

