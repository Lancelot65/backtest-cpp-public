#ifndef POSITION_HPP
#define POSITION_HPP

#include <iostream>


/// @brief struct for stock info of short and long position
struct INFO_POSITION
{
    double profit;
    __int64 time;
    double fees;
};


/// @brief class use in backtest who taking care of calculations of long position
class Position_long
{
private:
    double close;
    double tk;
    double sl;
    double size;
    __int64 time;
    bool etat = true;
public:

    /// @brief Create long position
    /// @param _close close
    /// @param _tk take profit in %
    /// @param _sl stop loss in %
    /// @param _size size of position
    /// @param _time time in milliseconde
    Position_long(double _close, double _tk, double _sl, double _size, __int64 _time);

    
    /// @brief check if position touch sl or tk
    /// @param close 
    /// @return if touch one of the two return true
    bool update(double close);


    /// @brief close position and take calcul
    /// @param close close
    /// @param time time in milliseconde
    /// @return struct INFO_POSITION
    INFO_POSITION fermeture(double close, __int64 time);

};

/// @brief class use in backtest who taking care of calculations of short position
class Position_short
{
private:
    double close;
    double tk;
    double sl;
    double size;
    __int64 time;
    bool etat = true;
public:

    /// @brief Create short position
    /// @param _close close
    /// @param _tk take profit in %
    /// @param _sl stop loss in %
    /// @param _size size of position
    /// @param _time time in milliseconde
    Position_short(double _close, double _tk, double _sl, double _size, __int64 _time);

    /// @brief check if position touch sl or tk
    /// @param close 
    /// @return if touch one of the two return true
    bool update(double close);

    /// @brief close position and take calcul
    /// @param close close
    /// @param time time in milliseconde
    /// @return struct INFO_POSITION
    INFO_POSITION fermeture(double close, __int64 time);
};

#endif