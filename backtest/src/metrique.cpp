#include "../include/metrique.hpp"

static double round_custom(double const &value, int const &lenght)
{
    double temp {1};
    for (int i = 0; i < lenght; i++) { temp = temp * 10; }
    return std::round(value * temp) / temp;
}

template <typename T>
static double median(T value)
{
    if (value.size() == 0)
    {
        return 0;
    }

    std::sort(value.begin(), value.end());

    if (value.size() % 2 == 0)
    {
        return (value[value.size() / 2 - 1] + value[value.size() / 2]) / 2;
    }
    else
    {
        return value[value.size() / 2];
    }
}

template <typename T>
static double sum_vector(T value)
{
    if (value.size() == 0)
    {
        return 0;
    }
    
    return std::accumulate(value.begin(), value.end(), 0.0);
}

template <typename T>
static double ecart_type(T const &value, double const &average)
{
    std::vector<double> temp;
    std::transform(value.begin(), value.end(), std::back_inserter(temp),
               [average] (auto value)  
               {
                    return std::abs(value - average) * std::abs(value - average);
               });

    double sum = sum_vector(temp);
    return std::sqrt(sum / temp.size());
}

static std::string color_value(double value, bool blue = false)
{
    std::stringstream ss;
    ss << std::setprecision(0) << value;
    if (blue)
    {
        return "\033[0;94m" + ss.str() + "\033[0m";
    }
    return "\033[0;" + (value < 0 ? std::to_string(31) : std::to_string(32)) + "m" + ss.str() + "\033[0m";
}

template <typename T>
std::string convert_time(T time) {
    int timeInt = static_cast<int>(time);
    if (time >= 86400000) // time >= one day
    {
        int jours = timeInt / (1000 * 60 * 60 * 24);
        return std::to_string(jours) + "J";
    }
    else if (time >= 3600000) // time >= one hour
    {
        int heures = (timeInt / (1000 * 60 * 60)) % 24;
        return std::to_string(heures) + "h";
    }
    else if (time >= 60000) // time >= one minute
    {
        int minutes = (timeInt / (1000 * 60)) % 60;
        return std::to_string(minutes) + "m";
    }
    else
    {
        float secondes = static_cast<float>(time) / 1000.0f;
        return std::to_string(secondes) + "s";
    }
}

static void mise_en_page(std::string name, double all, double _long, double _short, bool blue = false, bool time = false)
{
    std::cout << std::setw(25) << std::left << name;

    if (blue) {
        std::cout << "\033[34m";
    }
    else {
        if (all < 0)
            std::cout << "\033[31m";
        else
            std::cout << "\033[32m";
    }
    if (time) { std::cout << std::setw(20) << std::left << convert_time(all); }
    else { std::cout << std::setw(20) << std::left << std::setprecision(3) << all; }

    std::cout << "\033[0m";

    if (blue) {
        std::cout << "\033[34m";
    }
    else {
        if (_long < 0)
            std::cout << "\033[31m";
        else
            std::cout << "\033[32m";
    }
    if (time) { std::cout << std::setw(20) << std::left << convert_time(_long); }
    else { std::cout << std::setw(20) << std::left << std::setprecision(3) << _long; }
    std::cout << "\033[0m";

    if (blue) {
        std::cout << "\033[34m";
    }
    else {
        if (_short < 0)
            std::cout << "\033[31m";
        else
            std::cout << "\033[32m";
    }
    if (time) { std::cout << std::setw(20) << std::left << convert_time(_short); }
    else { std::cout << std::setw(20) << std::left << std::setprecision(3) << _short; }
    std::cout << "\033[0m" << '\n';
}


void _metrique(MEMORY_BACKTEST data)
{
    const double max_drawdawn = *std::max_element(data.evolution_capital.begin(), data.evolution_capital.end()) - *std::min_element(data.evolution_capital.begin(), data.evolution_capital.end());

    std::cout << "max drawdawn      " << "\033[0;31m" << max_drawdawn << "\033[0m\n";


    double Max_dd_duration {0};
    for (size_t i = 0; i < data.pnl.size(); i++)
    {
        double duration_temp {0};
        size_t temp_i        {1};

        if (data.pnl[i] < 0)
        {
            duration_temp += data.time_pnl[i];
            while(data.pnl[i + temp_i] < 0 && i + temp_i < data.pnl.size())
            {
                duration_temp += data.time_pnl[i + temp_i];
                temp_i++;
            }
            if (duration_temp > Max_dd_duration)
            {
                Max_dd_duration = duration_temp;
            }
        }
    }
    std::cout << "Max dd duration   " << "\033[0;94m" << convert_time(Max_dd_duration) << "\033[0m\n";

    double Time_in_drawdown {0};
    for (size_t i = 0; i < data.pnl.size(); i++)
    {
        // si profits negatif
        if (data.pnl[i] < 0)
        {
            Time_in_drawdown += data.time_pnl[i];
        }
    }
    std::cout << "Time in drawdown  " << "\033[0;94m" << convert_time(Time_in_drawdown) << "\033[0m\n";
    
    std::cout << "\n\n\n"; //? separation des principales métrique


    // pnl du backtest ??
    const double PnL_Cumulative_all   = sum_vector(data.pnl);
    const double PnL_Cumulative_long  = sum_vector(data._long);
    const double PnL_Cumulative_short = sum_vector(data._short);

    std::cout << std::setw(25) << std::left << "    ";
    std::cout << std::setw(20) << std::left << "All trades";
    std::cout << std::setw(20) << std::left << "Long";
    std::cout << std::setw(20) << std::left << "short" << "\n\n";



    mise_en_page("Pnl cumulative", PnL_Cumulative_all, PnL_Cumulative_long, PnL_Cumulative_short);

    const double PnL_average_all   = PnL_Cumulative_all / data.pnl.size();
    const double PnL_average_long  = PnL_Cumulative_long / data._long.size();
    const double PnL_average_short = PnL_Cumulative_short / data._short.size();

    mise_en_page("Pnl average", PnL_average_all, PnL_average_long, PnL_average_short);

    const double PnL_median_all   = median(data.pnl);
    const double PnL_median_long  = median(data._long);
    const double PnL_median_short = median(data._short);

    mise_en_page("Pnl median", PnL_median_all, PnL_median_long, PnL_median_short);

    const double PnL_std_all   = ecart_type(data.pnl, PnL_average_all);
    const double PnL_std_long  = ecart_type(data._long, PnL_average_long);
    const double PnL_std_short = ecart_type(data._short, PnL_average_short);

    mise_en_page("Pnl std", PnL_std_all, PnL_std_long, PnL_std_short, true);

    const double PnL_best_all   = *std::max_element(data.pnl.begin(), data.pnl.end());
    const double PnL_best_long  = *std::max_element(data._long.begin(), data._long.end());
    const double PnL_best_short = *std::max_element(data._short.begin(), data._short.end());

    mise_en_page("Pnl best", PnL_best_all, PnL_best_long, PnL_best_short);

    const double PnL_wrost_all   = *std::min_element(data.pnl.begin(), data.pnl.end());
    const double PnL_wrost_long  = *std::min_element(data._long.begin(), data._long.end());
    const double PnL_wrost_short = *std::min_element(data._short.begin(), data._short.end());

    mise_en_page("Pnl wrost", PnL_wrost_all, PnL_wrost_long, PnL_wrost_short);

    const double Exposure_cumulative_all   = sum_vector(data.time_pnl);
    const double Exposure_cumulative_long  = sum_vector(data.time_long);
    const double Exposure_cumulative_short = sum_vector(data.time_short);

    mise_en_page("Exposure cumulative", Exposure_cumulative_all, Exposure_cumulative_long, Exposure_cumulative_short, true, true);

    const double Exposure_average_all   = Exposure_cumulative_all / data.time_pnl.size();
    const double Exposure_average_long  = Exposure_cumulative_long / data.time_long.size();
    const double Exposure_average_short = Exposure_cumulative_short / data.time_short.size();

    mise_en_page("Exposure average", Exposure_average_all, Exposure_average_long, Exposure_average_short, true, true);
    
    const double Exposure_median_all   = median(data.time_pnl);
    const double Exposure_median_long  = median(data.time_long);
    const double Exposure_median_short = median(data.time_short);

    mise_en_page("Exposure median", Exposure_median_all, Exposure_median_long, Exposure_median_short, true, true);

    const double Exposure_std_all   = ecart_type(data.time_pnl, Exposure_average_all);
    const double Exposure_std_long  = ecart_type(data.time_long, Exposure_average_long);
    const double Exposure_std_short = ecart_type(data.time_short, Exposure_average_short);

    mise_en_page("Exposure std", Exposure_std_all, Exposure_std_long, Exposure_std_short, true, true);

    const double Longest_trade_all   = *std::max_element(data.time_pnl.begin(), data.time_pnl.end());
    const double Longest_trade_long  = *std::max_element(data.time_long.begin(), data.time_long.end());
    const double Longest_trade_short = *std::max_element(data.time_short.begin(), data.time_short.end());

    mise_en_page("Longest trade", Longest_trade_all, Longest_trade_long, Longest_trade_short, true, true);

    const double Shortest_trade_all   = *std::min_element(data.time_pnl.begin(), data.time_pnl.end());
    const double Shortest_trade_long  = *std::min_element(data.time_long.begin(), data.time_long.end());
    const double Shortest_trade_short = *std::min_element(data.time_short.begin(), data.time_short.end());

    mise_en_page("Shortest trade", Shortest_trade_all, Shortest_trade_long, Shortest_trade_short, true, true);

    // faire les fees -> frais

    std::cout << "\nWinning\n";
    
    //? metrique trade gagnant

    std::vector<double> all_win;
    std::vector<double> all_time_win;

    std::vector<double> long_win;
    std::vector<double> long_time_win;

    std::vector<double> short_win;
    std::vector<double> short_time_win;


    for (int i = 0; i < data.pnl.size(); i++)
    {
        if (data.pnl[i] > 0)
        {
            all_win.push_back(data.pnl[i]);
            all_time_win.push_back(data.time_pnl[i]); 
        }
    }

    for (int i = 0; i < data._long.size(); i++)
    {
        if (data._long[i] > 0)
        {
            long_win.push_back(data._long[i]);
            long_time_win.push_back(data.time_long[i]);
        }
    }

    for (int i = 0; i < data._short.size(); i++)
    {
        if (data._short[i] > 0)
        {
            short_win.push_back(data._short[i]);
            short_time_win.push_back(data.time_short[i]); 
        }
    }


    const double PnL_Cumulative_all_win   = sum_vector(all_win);
    const double PnL_Cumulative_long_win  = sum_vector(long_win);
    const double PnL_Cumulative_short_win = sum_vector(short_win);

    mise_en_page("PnL Cumulative win", PnL_Cumulative_all_win, PnL_Cumulative_long_win, PnL_Cumulative_short_win);

    const double PnL_average_all_win   = PnL_Cumulative_all_win / all_win.size();
    const double PnL_average_long_win  = PnL_Cumulative_long_win / long_win.size();
    const double PnL_average_short_win = PnL_Cumulative_short_win / short_win.size();

    mise_en_page("PnL average win", PnL_average_all_win, PnL_average_long_win, PnL_average_short_win);

    const double PnL_median_all_win   = median(all_win);
    const double PnL_median_long_win  = median(long_win);
    const double PnL_median_short_win = median(short_win);

    mise_en_page("Pnl median win", PnL_median_all_win, PnL_median_long_win, PnL_median_short_win);

    const double PnL_std_all_win   = ecart_type(all_win, PnL_average_all_win);
    const double PnL_std_long_win  = ecart_type(long_win, PnL_average_long_win);
    const double PnL_std_short_win = ecart_type(short_win, PnL_average_short_win);

    mise_en_page("Pnl std win", PnL_std_all_win, PnL_std_long_win, PnL_std_short_win, true);
    

    const double Exposure_cumulative_all_win   = sum_vector(all_time_win);
    const double Exposure_cumulative_long_win  = sum_vector(long_time_win);
    const double Exposure_cumulative_short_win = sum_vector(short_time_win);

    mise_en_page("Exposure cumulative win", Exposure_cumulative_all_win, Exposure_cumulative_long_win, Exposure_cumulative_short_win, true, true);

    const double Exposure_average_all_win   = Exposure_cumulative_all_win / all_time_win.size();
    const double Exposure_average_long_win  = Exposure_cumulative_long_win / long_time_win.size();
    const double Exposure_average_short_win = Exposure_cumulative_short_win/ short_time_win.size();

    mise_en_page("Exposure average win", Exposure_average_all_win, Exposure_average_long_win, Exposure_average_short_win, true, true);
    
    const double Exposure_median_all_win   = median(all_time_win);
    const double Exposure_median_long_win  = median(long_time_win);
    const double Exposure_median_short_win = median(short_time_win);

    mise_en_page("Exposure median win", Exposure_median_all_win, Exposure_median_long_win, Exposure_median_short_win, true, true);

    const double Exposure_std_all_win   = ecart_type(all_time_win, Exposure_average_all_win);
    const double Exposure_std_long_win  = ecart_type(long_time_win, Exposure_average_long_win);
    const double Exposure_std_short_win = ecart_type(short_time_win, Exposure_average_short_win);

    mise_en_page("Exposure std win", Exposure_std_all_win, Exposure_std_long_win, Exposure_std_short_win, true, true);



    std::cout << "\n\nLosing\n";
    
    //? metrique trade gagnant

    std::vector<double> all_lose;
    std::vector<double> all_time_lose;

    std::vector<double> long_lose;
    std::vector<double> long_time_lose;

    std::vector<double> short_lose;
    std::vector<double> short_time_lose;


    for (int i = 0; i < data.pnl.size(); i++)
    {
        if (data.pnl[i] < 0)
        {
            all_lose.push_back(data.pnl[i]);
            all_time_lose.push_back(data.time_pnl[i]); 
        }
    }

    for (int i = 0; i < data._long.size(); i++)
    {
        if (data._long[i] < 0)
        {
            long_lose.push_back(data._long[i]);
            long_time_lose.push_back(data.time_long[i]);
        }
    }

    for (int i = 0; i < data._short.size(); i++)
    {
        if (data._short[i] < 0)
        {
            short_lose.push_back(data._short[i]);
            short_time_lose.push_back(data.time_short[i]); 
        }
    }


    const double PnL_Cumulative_all_lose   = sum_vector(all_lose);
    const double PnL_Cumulative_long_lose  = sum_vector(long_lose);
    const double PnL_Cumulative_short_lose = sum_vector(short_lose);

    mise_en_page("PnL Cumulative lose", PnL_Cumulative_all_lose, PnL_Cumulative_long_lose, PnL_Cumulative_short_lose);

    const double PnL_average_all_lose   = PnL_Cumulative_all_lose / all_lose.size();
    const double PnL_average_long_lose  = PnL_Cumulative_long_lose / long_lose.size();
    const double PnL_average_short_lose = PnL_Cumulative_short_lose / short_lose.size();

    mise_en_page("PnL average lose", PnL_average_all_lose, PnL_average_long_lose, PnL_average_short_lose);

    const double PnL_median_all_lose   = median(all_lose);
    const double PnL_median_long_lose  = median(long_lose);
    const double PnL_median_short_lose = median(short_lose);

    mise_en_page("Pnl median lose", PnL_median_all_lose, PnL_median_long_lose, PnL_median_short_lose);

    const double PnL_std_all_lose   = ecart_type(all_lose, PnL_average_all_lose);
    const double PnL_std_long_lose  = ecart_type(long_lose, PnL_average_long_lose);
    const double PnL_std_short_lose = ecart_type(short_lose, PnL_average_short_lose);

    mise_en_page("Pnl std lose", PnL_std_all_lose, PnL_std_long_lose, PnL_std_short_lose, true);
    

    const double Exposure_cumulative_all_lose   = sum_vector(all_time_lose);
    const double Exposure_cumulative_long_lose  = sum_vector(long_time_lose);
    const double Exposure_cumulative_short_lose = sum_vector(short_time_lose);

    mise_en_page("Exposure cumulative lose", Exposure_cumulative_all_lose, Exposure_cumulative_long_lose, Exposure_cumulative_short_lose, true, true);

    const double Exposure_average_all_lose   = Exposure_cumulative_all_lose / all_time_lose.size();
    const double Exposure_average_long_lose  = Exposure_cumulative_long_lose / long_time_lose.size();
    const double Exposure_average_short_lose = Exposure_cumulative_short_lose/ short_time_lose.size();

    mise_en_page("Exposure average lose", Exposure_average_all_lose, Exposure_average_long_lose, Exposure_average_short_lose, true, true);
    
    const double Exposure_median_all_lose   = median(all_time_lose);
    const double Exposure_median_long_lose  = median(long_time_lose);
    const double Exposure_median_short_lose = median(short_time_lose);

    mise_en_page("Exposure median lose", Exposure_median_all_lose, Exposure_median_long_lose, Exposure_median_short_lose, true, true);

    const double Exposure_std_all_lose   = ecart_type(all_time_lose, Exposure_average_all_lose);
    const double Exposure_std_long_lose  = ecart_type(long_time_lose, Exposure_average_long_lose);
    const double Exposure_std_short_lose = ecart_type(short_time_lose, Exposure_average_short_lose);

    mise_en_page("Exposure std lose", Exposure_std_all_lose, Exposure_std_long_lose, Exposure_std_short_lose, true, true);
}