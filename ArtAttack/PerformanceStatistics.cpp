#include "pch.h"
#include "PerformanceStatistics.h"
#include <iostream>
#include <fstream>

PerformanceStatistics::PerformanceStatistics(
	int target_fps, int num_threads) :
	_target_fps(target_fps), _num_threads(num_threads)
{
}

void PerformanceStatistics::add_frame_time(double frame_time)
{
	this->_frame_times.push_back(frame_time);
}

void PerformanceStatistics::write_statistics_to_file(const std::string& file_name) const
{
	std::ofstream file(file_name);
	if (file.is_open())
	{
		GameStatistics game_stats = this->calculate_game_statistics();
		file << "##### Performance Statistics #####" << std::endl;
		file << "Target FPS: " << this->_target_fps << std::endl;
		file << "Number of Threads: " << this->_num_threads << std::endl << std::endl;
		file << "### FPS Statistics ###" << std::endl;
		file << "Min: " << game_stats.fps.min << std::endl;
		file << "Max: " << game_stats.fps.max << std::endl;
		file << "Mean: " << game_stats.fps.mean << std::endl;
		file << "Std Dev: " << game_stats.fps.standard_deviation << std::endl;
		file << "Median: " << game_stats.fps.median << std::endl << std::endl;
		file << "### Frame Time Statistics ###" << std::endl;
		file << "Min: " << game_stats.frame_time.min << std::endl;
		file << "Max: " << game_stats.frame_time.max << std::endl;
		file << "Mean: " << game_stats.frame_time.mean << std::endl;
		file << "Std Dev: " << game_stats.frame_time.standard_deviation << std::endl;
		file << "Median: " << game_stats.frame_time.median << std::endl;
		file << "Total: " << game_stats.frame_time.total << std::endl << std::endl;
		file << "# End of Performance Statistics #" << std::endl;
		file.close();
	}
}


void PerformanceStatistics::print_statistics(const Statistics& statistics) const
{
	std::cout << "Min: " << statistics.min << std::endl;
	std::cout << "Max: " << statistics.max << std::endl;
	std::cout << "Mean: " << statistics.mean << std::endl;
	std::cout << "Standard Deviation: " << statistics.standard_deviation << std::endl;
	std::cout << "Median: " << statistics.median << std::endl;
	std::cout << "Total: " << statistics.total << std::endl;
}

Statistics PerformanceStatistics::calculate_statistics() const
{
	Statistics stats;
	if (this->_frame_times.size() == 0)
	{
		return stats;
	}

	stats.min = this->_frame_times[0];
	stats.max = this->_frame_times[0];
	stats.total = 0.0;
	for (auto& time : this->_frame_times)
	{
		if (time < stats.min)
		{
			stats.min = time;
		}
		if (time > stats.max)
		{
			stats.max = time;
		}
		stats.total += time;
	}
	stats.mean = stats.total / this->_frame_times.size();
	stats.median = this->calculate_median();
	stats.standard_deviation = this->calculate_standard_deviation(stats.mean);
	return stats;
}

GameStatistics PerformanceStatistics::calculate_game_statistics() const
{
	Statistics frame_time_stats = this->calculate_statistics();
	
	GameStatistics stats;
	stats.frame_time = frame_time_stats;
	stats.fps.mean = 1.0 / frame_time_stats.mean;
	stats.fps.min = 1.0 / frame_time_stats.max;
	stats.fps.max = 1.0 / frame_time_stats.min;
	stats.fps.total = 0.0;
	stats.fps.median = 1.0 / frame_time_stats.median;
	stats.fps.standard_deviation = frame_time_stats.standard_deviation /
		pow(frame_time_stats.mean, 2);
	return stats;

}

double PerformanceStatistics::calculate_median() const
{
	if (this->_frame_times.size() == 0)
	{
		return 0.0;
	}
	std::vector<double> sorted_frame_times = this->_frame_times;
	std::sort(sorted_frame_times.begin(), sorted_frame_times.end());
	if (sorted_frame_times.size() % 2 == 0)
	{
		return (sorted_frame_times[sorted_frame_times.size() / 2] +
			sorted_frame_times[sorted_frame_times.size() / 2 - 1]) / 2;
	}
	else
	{
		return sorted_frame_times[sorted_frame_times.size() / 2];
	}
}

double PerformanceStatistics::calculate_standard_deviation(double mean) const
{
	if (this->_frame_times.size() == 0)
	{
		return 0.0;
	}
	double sum = 0.0;
	for (auto& time : this->_frame_times)
	{
		sum += pow(time - mean, 2);
	}
	return sqrt(sum / this->_frame_times.size());
}