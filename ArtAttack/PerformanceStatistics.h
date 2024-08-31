#ifndef PERFORMANCE_STATISTICS_H
#define PERFORMANCE_STATISTICS_H

#include <vector>
#include <string>

struct Statistics
{
	double min = 0.0;
	double max = 0.0;
	double mean = 0.0;
	double standard_deviation = 0.0;
	double median = 0.0;
	double total = 0.0;
};

struct GameStatistics
{
	Statistics frame_time;
	Statistics fps;
};


class PerformanceStatistics
{
public:
	PerformanceStatistics(int target_fps, int num_threads);
	void add_frame_time(double frame_time);
	void write_statistics_to_file(const std::string& file_name) const;
private:
	std::vector<double> _frame_times;
	int _target_fps;
	int _num_threads;
	double calculate_median() const;
	double calculate_standard_deviation(double mean) const;
	Statistics calculate_statistics() const;
	GameStatistics calculate_game_statistics() const;
	void print_statistics(const Statistics& statistics) const;
};

#endif // !PERFORMANCE_STATISTICS_H
