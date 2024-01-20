#include "../include/backtest.hpp"


void Backtest::open_long(int i, double _take_profit, double _stop_loss, double _size)
{
    if (!this->etat_long)
    {
        etat_long = true;
        position_l = new Position_long(this->ohlcv.close[i], _take_profit, _stop_loss, _size, this->ohlcv.time[i]);
        std::cout << "open long" << i << std::endl;
    }
}

void Backtest::open_short(int i, double _take_profit, double _stop_loss, double _size)
{
    if (!this->etat_short)
    {
        etat_short = true;
        position_s = new Position_short(this->ohlcv.close[i], _take_profit, _stop_loss, _size, this->ohlcv.time[i]);
        std::cout << "open short" << i << std::endl;
    }
}

void Backtest::close_long(int i)
{

    if (this->etat_long)
    {
        this->etat_long = false;
        INFO_POSITION info_position = this->position_l->fermeture(this->ohlcv.close[i], this->ohlcv.time[i]);
        this->capital += info_position.profit;

        // add data in memory backtest
        this->memory_backtest.pnl.push_back(info_position.profit);
        this->memory_backtest._long.push_back(info_position.profit);

        this->memory_backtest.time_pnl.push_back(info_position.time);
        this->memory_backtest.time_long.push_back(info_position.time);

        this->memory_backtest.fees_pnl.push_back(info_position.fees);
        this->memory_backtest.fees_long.push_back(info_position.fees);

        this->memory_backtest.evolution_capital.push_back(this->capital);

        delete position_l;
        this->position_l = nullptr;
        std::cout << "close long" << i << '\n';

    }
}

void Backtest::close_short(int i)
{
    if (this->etat_short)
    {
        this->etat_short = false;

        INFO_POSITION info_position = this->position_s->fermeture(this->ohlcv.close[i], this->ohlcv.time[i]);
        this->capital += info_position.profit;

        // add data in memory backtest
        this->memory_backtest.pnl.push_back(info_position.profit);
        this->memory_backtest._short.push_back(info_position.profit);

        this->memory_backtest.time_pnl.push_back(info_position.time);
        this->memory_backtest.time_short.push_back(info_position.time);

        this->memory_backtest.fees_pnl.push_back(info_position.fees);
        this->memory_backtest.fees_short.push_back(info_position.fees);

        this->memory_backtest.evolution_capital.push_back(this->capital);

        delete position_s;
        this->position_s = nullptr;
        std::cout << "close short" << i <<'\n';
    }
}

void Backtest::update(int i)
{
    if (this->etat_long && this->position_l != nullptr)
    {
        if (this->position_l->update(this->ohlcv.close[i]))
        {
            this->close_long(i);
        }
        
    }
    
    if (this->etat_short && this->position_s != nullptr)
    {
        if (this->position_s->update(this->ohlcv.close[i]))
        {
            this->close_short(i);
        }
        
    }
}

double Backtest::return_capital()
{
    return this->capital;
}

/// @brief This function return crypto ohlcv from https://www.binance.com/fr/binance-api
/// @param symbol syntax : symbol 
/// @param timeframe 1s, 1m, 3m, 5m, 15m, 30m, 1h, 2h, 4h, 6h, 8h, 12h ,1d, 3d, 1w, 1M
/// @param limit limit, standard is 200
/// @return struct ohlcv
void Backtest::load_ohlcv_crypto(std::string _symbol, std::string _timeframe, int _limit)
{

    this->ohlcv = crypto(_symbol, _timeframe, _limit);
}

/// @brief This function return forex ohlcv from https://polygon.io api
/// @param symbol syntax : C:symbol
/// @param timeframe minute, hour, day, week, month, quarter, year
/// @param from start of data : 2023-09-01
/// @param to end of data : 2023-09-02
/// @param multiplicateur 2 minute : 2 here, minute in timeframe, 5 hour : 5 here, hour in timeframe
/// @param apikey your apiket
/// @param limit limit, standard is 200
/// @param adjusted adjusted data, stanndart false
/// @return struct ohlcv
void Backtest::load_ohlcv_forex(std::string _symbol, std::string _timeframe, std::string _from, std::string _to, int _multiplicateur, std::string _apikey, bool _adjusted)
{

    this->ohlcv = forex(_symbol, _timeframe, _from, _to, _multiplicateur, _apikey, _adjusted);
}


void Backtest::metrique()
{
    _metrique(this->memory_backtest);
}


OHLCV Backtest::return_data()
{
    return ohlcv;
}