#include "../include/api.hpp"

static size_t writeCallback(void *contents, size_t size, size_t nmemb, std::string *buffer)
{
    size_t realsize = size * nmemb;
    buffer->append((char *)contents, realsize);
    return realsize;
}

static std::string requete_api(std::string const url)
{
    CURL *curl;
    CURLcode res;
    std::string buffer;
	std::cout << url << "\n";


    curl_global_init(CURL_GLOBAL_ALL);
    curl = curl_easy_init();
    
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buffer);

        res = curl_easy_perform(curl);

        if (res != CURLE_OK) {
            std::cerr << curl_easy_strerror(res) << std::endl;
        }

        curl_easy_cleanup(curl);
    }

    curl_global_cleanup();

    return buffer;
}

std::vector<std::string> convert_milliseconde_date(std::vector<__int64> &data)
{
    std::vector<std::string> output;
    for (auto &i : data)
    {
        std::chrono::milliseconds duration(i);

        auto time_since_epoch = std::chrono::system_clock::time_point(duration);

        std::time_t time = std::chrono::system_clock::to_time_t(time_since_epoch);

        std::tm* time_info = std::localtime(&time);

        char buffer[80];
        std::strftime(buffer, 80, "%Y-%m-%d %H:%M:%S", time_info);

        std::string string_(buffer);
        output.push_back(string_);
    }
    return output;
}

OHLCV crypto(std::string const symbol, std::string const timeframe, int limit)
{
    OHLCV data;

    std::vector<std::string> liste_timeframe {"1s", "1m", "3m", "5m", "15m", "30m", "1h", "2h", "4h", "6h", "8h", "12h", "1d", "3d", "1w", "1M"};

    bool timeframe_is_valide {false};
    for (std::string time : liste_timeframe)
    {
        if (timeframe == time)
        {
            timeframe_is_valide = true;
            break;
        }
    }

    if (!timeframe_is_valide)
    {
        std::cerr << "timeframe is not valid" << std::endl;
        return data;
    }


    std::ostringstream url;
    url << "https://api.binance.com/api/v3/klines?symbol=" << symbol << "&interval=" << timeframe << "&limit=" << limit;

    std::string buffer = requete_api(url.str());
    json jsonData = json::parse(buffer);

    if (jsonData.is_null())
    {
        return data;
    }

    if (jsonData.contains("code"))
    {
        std::cout << jsonData["msg"] << std::endl;

        return data;
    }
    

    for (auto &tableau : jsonData)
    {
        data.time.push_back(tableau[0]);
        data.open.push_back(std::stod(tableau[1].get<std::string>()));
        data.high.push_back(std::stod(tableau[2].get<std::string>()));
        data.low.push_back(std::stod(tableau[3].get<std::string>()));
        data.close.push_back(std::stod(tableau[4].get<std::string>()));
        data.volume.push_back(std::stod(tableau[5].get<std::string>()));
    }
            
    
    return data;
}

void get_crypto_symbol(bool exporte)
{
    const std::string url { "https://api.binance.com/api/v3/exchangeInfo" };
    
    std::string buffer = requete_api(url);
    json jsonData = json::parse(buffer);

    if (exporte)
    {
        std::ofstream file("temp_binance.txt");

        if (file.is_open())
        {
            file.clear();
            for (auto &exchange : jsonData ["symbols"]) 
            {
                file << exchange["symbol"] << " ";
            }
            file.close();
        }
    }
    else
    {
        for (auto &exchange : jsonData["symbols"]) 
        {
            std::cout << exchange["symbol"] << " ";
        }
    }    
}

OHLCV forex(std::string const symbol, std::string const timeframe, std::string const from, std::string const to , int const multiplicateur, std::string apikey, bool adjusted)
{
    OHLCV data;
    const std::string base_url = "https://api.polygon.io/v2/aggs/ticker/";

    std::ostringstream url;
    url << base_url << symbol << "/range/" << multiplicateur << "/" << timeframe << "/" << from << "/" << to << "?" << (adjusted ? "true" : "false") << "&sort=asc&apiKey=" << apikey;

    std::string buffer = requete_api(url.str());
    
    json jsonData = json::parse(buffer);

    if (jsonData["status"] == "ERROR")
    {
        std::cout << jsonData["error"] << std::endl;
        return data;
    }


    for (auto &i : jsonData["results"])
    {
        data.close.push_back(i["c"]);
        data.high.push_back(i["h"]);
        data.low.push_back(i["l"]);
        data.open.push_back(i["o"]);
        data.volume.push_back(i["v"]);
        data.time.push_back(i["t"]);
    }

    return data;
}

void get_forex_symbol(bool exporte)
{
    std::string temp = std::getenv("cle_api_polygon");
    const std::string url  = "https://api.polygon.io/v3/reference/tickers?market=fx&active=true&apiKey=" + temp;
    
    std::string buffer = requete_api(url);
    json jsonData = json::parse(buffer);


    if (exporte)
    {
        std::ofstream file("temp_polygon.txt");

        if (file.is_open())
        {
            file.clear();
            for (auto &exchange : jsonData["results"]) 
            {
                file << exchange["ticker"] << " ";
            }
            file.close();
        }
    }
    else
    {
        for (auto &exchange : jsonData["results"]) 
        {
            std::cout << exchange["ticker"] << " ";
        }
    }    
}