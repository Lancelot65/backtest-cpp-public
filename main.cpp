#include "backtest/include/metrique.hpp"

int main()
{
    MEMORY_BACKTEST data;
    data.evolution_capital = {10, 20, 30};
    data.pnl = {1, 2, 3, 4};
    data.time_pnl = {1,2,3,4};
    data._long = {1,2,3,4};
    data.time_long = {1,2,3,4};

    _metrique(data);

    return 0;
}