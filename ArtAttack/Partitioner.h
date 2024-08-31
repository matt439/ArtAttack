#ifndef PARTITIONER_H
#define PARTITIONER_H

#include <vector>

class Partitioner
{
public:
	Partitioner() = default;

	static std::vector<std::pair<int, int>>
		partition(int num_elements, int num_partitions);
};
#endif // !PARTITIONER_H
