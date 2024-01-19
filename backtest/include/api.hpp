#ifndef API_HPP
#define API_HPP

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>

#include "structure.hpp"


//? this hpp is clean

using json = nlohmann::json;

/// @brief convert milliseconde to lisible time
/// @param data llong long int
/// @return time : 2024-01-05 01:00:00
std::vector<std::string> convert_milliseconde_date(std::vector<__int64> &data);

/// @brief This function return crypto ohlcv from https://www.binance.com/fr/binance-api
/// @param symbol syntax : symbol 
/// @param timeframe 1s, 1m, 3m, 5m, 15m, 30m, 1h, 2h, 4h, 6h, 8h, 12h ,1d, 3d, 1w, 1M
/// @param limit limit, standard is 200
/// @return struct ohlcv
OHLCV crypto(std::string const symbol, std::string const timeframe, int limit = 200);

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
OHLCV forex(std::string const symbol, std::string const timeframe, std::string const from, std::string const to , int const multiplicateur, std::string apikey = std::getenv("cle_api_polygon"), bool adjusted = false);

/// @brief return over symbol can binance give
/// @param exporte write data in file or in console
void get_crypto_symbol(bool exporte = true);

/// @brief return over symbol can polygon forex give
/// @param exporte write data in file or in console
void get_forex_symbol(bool exporte = true);

#endif