#pragma once

#include <vector>
#include <iostream>

class Queue
{
public:
	Queue() {}
	~Queue() { Size = 0; data.clear(); }

	void addQueue(int x) { data.push_back(x); Size += 1; }
	void deleteQueue()
	{
		if (Size > 0)
		{
			for (int i = 0; i < Size - 1; i++)
			{
				data[i] = data[i + 1];
			}
			Size -= 1;
			data.erase(data.begin() + Size - 1);
		}
		else
			std::cout << "Queue is empty!\n";
	}
	void destroyQueue() { data.clear(); Size = 0; }
	bool isEmptyQueue() { if (Size == 0) return true; else return false; }
	int Front() { return data[0]; }
	int Back() { return data[Size - 1]; }

private:
	std::vector<int> data;
	int Size = 0;
};