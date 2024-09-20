#include "pch.h"
#include "Partitioner.h"

std::vector<std::pair<int, int>> Partitioner::partition(int num_elements, int num_partitions)
{
	std::vector<std::pair<int, int>> result;
	int elements_per_partition = num_elements / num_partitions;
	int remainder = num_elements % num_partitions;
	int start = 0;
	for (int i = 0; i < num_partitions && i < num_elements; i++)
	{
		int end = start + elements_per_partition;
		if (remainder > 0)
		{
			end++;
			remainder--;
		}
		result.push_back(std::make_pair(start, end));
		start = end;
	}
	return result;
}

std::vector<std::pair<int, int>> Partitioner::partition(size_t num_elements, int num_partitions)
{
	return Partitioner::partition(static_cast<int>(num_elements), num_partitions);
}