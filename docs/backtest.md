# Documentation principal header backtest.hpp

## Description
This file grouping other function of class in [header backtest](headers%20backtest) in only one class\
the class  10 functions : 
- [open_long](#open_long)
- [open_short](#open_short)
- [close_long](#close_long)
- [close_short](#close_short)
- [load_ohlcv_crypto](#load_ohlcv_crypto)
- [load_ohlcv_forex](#load_ohlcv_forex)
- [update](#update)
- [return_capital](#return_capital)
- [return_data](#return_data)
- [metrique](#metrique)


## Dependencies
- nlohmann/json.hpp (api.hpp)
- curl/curl.h (api.hpp)

<a id="open_long"></a>
### `void open_long(int i, double _take_profit, double _stop_loss, double _size);`
This function is implementation of [this one](headers%20backtest/position.md#constructor_long)
#### parameters : 
- symbol    ("BTCUSDT", "ETHUSDT" ...)
- timeframe ("1s", "1m", "3m", "5m", "15m", "30m", "1h", "2h", "4h", "6h", "8h", "12h" ,"1d", "3d", "1w", "1M")
- limit     (max : 1000)

## Example

```cpp
#include "api.hpp"

int main()
{
    OHLCV data {};
    data = crypto("BTCUSDT", "1h", 200);
    return 0;
}
```
<a id="ohlcvforex"></a>
### `OHLCV forex(std::string const symbol, std::string const timeframe, std::string const from, std::string const to , int const multiplicateur, std::string apikey = std::getenv("cle_api_polygon"), bool adjusted = false)`
This function return OHLCV crypto data from polygon api : [polygon api doc](https://polygon.io/docs/forex/getting-started)
#### parameters : 
- symbol    ("C:EURUSD", "C:USDJPY" ...) -> C:symbol
- timeframe ("minute", "hour", "day", "week", "month", "quarter", "year")
- from      syntax : year:month:day, example : 2023-09-01 
- to        syntax : year:month:day, example : 2024-09-01
- multiplicateur 2 minute : 2 here, minute in timeframe, 5 hour : 5 here, hour in timeframe 
- apikey     your apikey : [polygon](https://polygon.io)
- adjusted adjusted data or note

## Example
```cpp
#include "api.hpp"

int main()
{
    OHLCV data {};
    data = forex("C:EURUSD", "hour", "2023-09-01", "2024-09-01", 5, "your_apikey", 200, false);
    return 0;
}
```

## Secondary function
<a id="convert_milliseconde_date"></a>
### `std::vector<std::string> convert_milliseconde_date(std::vector<__int64> &data)`
This function convert milliseconde to lisible time in vector.
#### parameters : 
- data std::vector with __int64

```cpp
#include "api.hpp"
#include <vector>
#include <string>

int main()
{
    OHLCV data {};
    data = crypto("BTCUSDT", "1h", 200);
    
    std::vector<std::string> time = convert_milliseconde_date(data.time);

    return 0;
}
```

<a id="get_crypto_symbol"></a>
### `void get_crypto_symbol(bool exporte = true)`
This function print or load in file symbol you can use in crypto api.
#### parameters : 
- export true : load symbol in file, false print symbol in terminal

```cpp
#include "api.hpp"

int main()
{
    get_crypto_symbol(true);

    return 0;
}
```

<a id="get_forex_symbol"></a>
### `void get_forex_symbol(bool exporte = true)`
This function print or load in file symbol you can use in forex api.
#### parameters : 
- export true : load symbol in file, false print symbol in terminal

```cpp
#include "api.hpp"

int main()
{
    get_forex_symbol(true);

    return 0;
}
```