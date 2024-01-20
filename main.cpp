#include "backtest/include/position.hpp"

int main()
{
    // close = 1.110, tk = 10, sl = 5 and time = 1705399200000
    Position_short position(1.110, 10, 5, 1, 1705499200000);
    
    if (position.update(1.100)) // update with close
    {
        // tk or sl is enable
        // you can close position here
    }

    // close = 1.098, time = 1706578200000
    INFO_POSITION result = position.fermeture(1.098, 1706578200000);
    return 0;
}