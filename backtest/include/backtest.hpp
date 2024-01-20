#ifndef BACKTEST_HPP
#define BACKTEST_HPP

#include <vector>
#include <string>
#include <iostream>
#include <cstdlib>

#include "api.hpp"
#include "metrique.hpp"
#include "position.hpp"
#include "structure.hpp"

class Backtest final
{
private:
    OHLCV ohlcv;

    double capital;
    bool etat_long = false;
    bool etat_short = false;

    Position_long *position_l = nullptr;
    Position_short *position_s = nullptr;

    MEMORY_BACKTEST memory_backtest;

public:
    Backtest() = default;

    void open_long(int i, double _take_profit, double _stop_loss, double _size);
    void open_short(int i, double _take_profit, double _stop_loss, double _size);
    void close_long(int i);
    void close_short(int i);

    void update(int i);

    void load_ohlcv_crypto(std::string _symbol, std::string _timeframe, int _limit);
    void load_ohlcv_forex(std::string _symbol, std::string _timeframe, std::string _from, std::string _to, int _multiplicateur, std::string _apikey, bool _adjusted = false);

    // void performance();
    double return_capital();

    OHLCV return_data();

    void metrique();
};

#endif