#ifndef PERFORMANCE_STATISTICS_H
#define PERFORMANCE_STATISTICS_H

#include <vector>

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
	PerformanceStatistics() = default;
	void add_frame_time(double frame_time);
	Statistics calculate_statistics() const;
	GameStatistics calculate_game_statistics(const Statistics& frame_time_stats) const;
	void print_statistics(const Statistics& statistics) const;
private:
	std::vector<double> _frame_times;
	double calculate_median() const;
	double calculate_standard_deviation(double mean) const;
};

#endif // !PERFORMANCE_STATISTICS_H
