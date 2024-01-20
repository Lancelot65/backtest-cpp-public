# Documentation principal header backtest.hpp

## Description
This file grouping other function of class in [header backtest](headers%20backtest) in only one class\
the class  10 functions : 
- [open_long](#open_long)
- [open_short](#open_short)
- [close_long](#close_long)
- [close_short](#close_short)
- [update](#update)
- [load_ohlcv_crypto](#load_ohlcv_crypto)
- [load_ohlcv_forex](#load_ohlcv_forex)
- [return_capital](#return_capital)
- [return_data](#return_data)
- [metrique](#metrique)


## Dependencies
- nlohmann/json.hpp (api.hpp)
- curl/curl.h (api.hpp)

<a id="open_long"></a>
### `void open_long(int i, double _take_profit, double _stop_loss, double _size)`
This function is implementation in the class of [this one](headers%20backtest/position.md#constructor_long)\
It's use for open long position.

#### parameters : 
- i &#8594; iteration of loop for, this function directly retrieves the value in the class data
- _take_profit &#8594; take profit in %
- _stop_loss &#8594; stop loss in %
- _size &#8594; size in %

<a id="open_short"></a>
### `void open_short(int i, double _take_profit, double _stop_loss, double _size)`
This function is implementation in the class of [this one](headers%20backtest/position.md#constructor_short)\
It's use for open short position.

#### parameters : 
- i &#8594; iteration of loop for, this function directly retrieves the value in the class data
- _take_profit &#8594; take profit in %
- _stop_loss &#8594; stop loss in %
- _size &#8594; size in %


<a id="close_long"></a>
### `void close_long(int i)`
This function is implementation in the class of [this one](headers%20backtest/position.md#fermeture_long)\
It's use for close long position.

#### parameter : 
- i &#8594; iteration of loop for, this function directly retrieves the value in the class data

<a id="close_short"></a>
### `void close_short(int i)`
This function is implementation in the class of [this one](headers%20backtest/position.md#fermeture_short)
It's use for close short position.

#### parameter : 
- i &#8594; iteration of loop for, this function directly retrieves the value in the class data


<a id="update"></a>
### `void update(int i)`
This function is implementation in the class of [this one](headers%20backtest/position.md#update_short) and [this one](headers%20backtest/position.md#update_long)
It's use for check if long or short position touch stop loss or take profit.

#### parameter : 
- i &#8594; iteration of loop for, this function directly retrieves the value in the class data

<a id="load_ohlcv_crypto"></a>
### `void load_ohlcv_crypto(std::string _symbol, std::string _timeframe, int _limit)`
This function is implementation in the class of [this one](headers%20backtest/api.md#ohlcvforex)
Tt's used to retrieve crypto ohlcv data from binance api and stored in a private variable.

#### parameter : 
- _symbol &#8594; "BTCUSDT", "ETHUSDT"...
- _timeframe &#8594; "1h", "1m" ...
- _limit &#8594; 200 (max : 1000)


<a id="load_ohlcv_forex"></a>
### `void load_ohlcv_forex(std::string _symbol, std::string _timeframe, std::string _from, std::string _to, int _multiplicateur, std::string _apikey, bool _adjusted = false)`
This function is implementation in the class of [this one](headers%20backtest/api.md#ohlcvforex)
Tt's used to retrieve forex ohlcv data from polygon api and stored in a private variable.

#### parameter : 
- _symbol    ("C:EURUSD", "C:USDJPY" ...) -> C:symbol
- _timeframe ("minute", "hour", "day", "week", "month", "quarter", "year")
- _from      syntax : year:month:day, example : 2023-09-01 
- _to        syntax : year:month:day, example : 2024-09-01
- _multiplicateur 2 minute : 2 here, minute in timeframe, 5 hour : 5 here, hour in timeframe 
- _apikey     your apikey : [polygon](https://polygon.io)
- _adjusted adjusted data or note



<a id="return_capital"></a>
### `double return_capital();`
This function return capital (double), for example after backtest you would like to know your new capital

<a id="return_data"></a>
### `double return_capital();`
This function return capital (OHLCV), return ohlcv data after load with api function


<a id="metrique"></a>
### `double return_capital();`
After a backtest you would like more simple information of long, short position, this function write analyse in terminal


# Example
### This is a simple exemple for use correctly backtest.hpp
#### don't forget to compile over header and exteranl lib: g++ main.cpp backtest/src/.cpp -lcurl

```cpp
#include "backtest/include/backtest.hpp"
#include <iostream>
#include <algorithm>
#include <vector>

// simple function for very simple moving average, this function is very limited
std::vector<double> sma(std::vector<double> &data, int length)
{
    std::vector<double> indicateur {};
    if (data.empty()) // id vectoris empty
    {
        std::cout << "vector is empty" << std::endl;
        return indicateur; // for better error you can use throw
    }

    double sum;

    indicateur.reserve(data.size());

    indicateur.insert(indicateur.end(), length - 1, -1); // for firts value who can not calculation add -1 for None value

    std::transform(data.begin() + length, data.end() + 1, std::back_inserter(indicateur),
                [&] (auto &it)
                {
                    sum = std::accumulate(&it - length, &it, 0.0); // sum of value
                    return sum / static_cast<double>(length); // mean of sum
                });
    return indicateur;
}


int main()
{
    Backtest obj;
    obj.load_ohlcv_crypto("BTCUSDT", "1h", 200);
    // or obj.load_ohlcv_forex("C:EURUSD", "hour", "2023-09-01", "2024-09-01", 1, "mG0dZlFzFpd0msBzITaYdMOk3UN4jRuh", false);
    OHLCV data = obj.return_data();

    

    std::vector<double> sma10 = sma(data.close, 10);

    for (size_t i {0}; i < data.close.size(); i++)
    {
        if (sma10[i] == -1) // if none value
        {
            continue;
        }
        if (data.close[i] > sma10[i])
        {
            obj.open_long(i, 10, 5, 1); // open long
            obj.close_short(i);         // close short
        }
        else if (data.close[i] < sma10[i])
        {
            obj.open_short(i, 10, 5, 1); // open short
            obj.close_long(i);           // lose long
        }
        obj.update(i); // update
    }

    std::cout << obj.return_capital() << std::endl; // print capital
    obj.metrique(); // print metrique

    return 0;
}
```
