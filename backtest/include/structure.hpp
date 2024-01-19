#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <vector>
#include <optional>

using default_vector = std::vector<std::optional<double>>;

struct OHLCV
{
	std::vector<double> open;
	std::vector<double> close;
	std::vector<double> high;
	std::vector<double> low;
	std::vector<double> volume;
	std::vector<__int64> time;
};

struct MEMORY_BACKTEST
{
	std::vector<double> pnl;
	std::vector<double> _long;
	std::vector<double> _short;
	std::vector<__int64> time_pnl;
	std::vector<__int64> time_long;
	std::vector<__int64> time_short;
	std::vector<double> fees_pnl;
	std::vector<double> fees_long;
	std::vector<double> fees_short;
    std::vector<double> evolution_capital;
};

struct POSITION_INDICE {
    std::vector<int> open_long;
    std::vector<int> close_long;
    std::vector<int> open_short;
    std::vector<int> close_short;
};

#endif