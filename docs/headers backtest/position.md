# Documentation position.hpp

## Description
This file contain 2 class and 1 struct
- [INFO_POSITION](#INFO_POSITION)
- [Position_long](#Position_long)
- [Position_short](#Position_short)


<a id="INFO_POSITION"></a>
### `struct INFO_POSITION`
This struct is use in return value for close position
This struct countain 3 variables : 
- profit (double) &#8594; profit or lost
- time (__int64) &#8594; time in milliseconde
- fees (double) &#8594; fees of position

## Example

```cpp
#include "position.hpp"

int main()
{
    INFO_POSITION info_position {};
    info_position.profit = 67.6;
    info_position.time = 1705399200000;
    info_position.fees = 1.2;
    return 0;
}
```

<a id="Position_long"></a>
### `class Position_long`
This class is use in backtest for open, manage take profit and stop loss, close postion and return the time of postion, profit and fees for long position.

*fees unvalid*

#### parameter : 
- [constructor](#constructor_long)
- [update](#update_long)
- [fermeture](#fermeture_long)

<a id="constructor_long"></a>
#### `Position_long(double _close, double _tk, double _sl, double _size, __int64 _time)`
The constructor init value for futur calculation.

#### parameter : 
- _close (double) &#8594; current close
- _tk (double) &#8594; take profit
- _sl (double) &#8594; stop loss
- _size (double) &#8594; size of position
- _time (__int64) &#8594; current time

<a id="update_long"></a>
#### `bool update(double close)`
This function check if position touch stop loss or take profit

#### parameter : 
- close (double) &#8594; current close

<a id="fermeture_long"></a>
#### `INFO_POSITION fermeture(double close, __int64 time)`
This function close position, calculate profit and time and return struct INFO_POSITION

#### parameter : 
- close (double) &#8594; current close
- time (__int64) &#8594; current time


## Example

```cpp
#include "position.hpp"

int main()
{
    // close = 1.098, tk = 10, sl = 5 and time = 1705399200000
    Position_long position(1.098, 10, 5, 1, 1705499200000);
    
    if (position.update(1.100)) // update with close
    {
        // tk or sl is enable
        // you can close position here
    }

    // close = 1.110, time = 1706578200000
    INFO_POSITION result = position.fermeture(1.110, 1706578200000);
    return 0;
}
```


<a id="Position_short"></a>
### `class Position_short`
This class is use in backtest for open, manage take profit and stop loss, close postion and return the time of postion, profit and fees for short position.

*fees unvalid*

#### parameter : 
- [constructor](#constructor_short)
- [update](#update_short)
- [fermeture](#fermeture_short)

<a id="constructor_short"></a>
#### `Position_short(double _close, double _tk, double _sl, double _size, __int64 _time)`
The constructor init value for futur calculation.\

#### parameter :  
- _close (double) &#8594; current close
- _tk (double) &#8594; take profit
- _sl (double) &#8594; stop loss
- _size (double) &#8594; size of position
- _time (__int64) &#8594; current time

<a id="update_short"></a>
#### `bool update(double close)`
This function check if position touch stop loss or take profit

#### parameter : 
- close (double) &#8594; current close

<a id="fermeture_short"></a>
#### `INFO_POSITION fermeture(double close, __int64 time)`
This function close position, calculate profit and time and return struct INFO_POSITION

#### parameter : 
- close (double) &#8594; current close
- time (__int64) &#8594; current time


## Example

```cpp
#include "position.hpp"

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
```