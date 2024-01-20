# Documentation structure.hpp

## Description
This file contain 4 struct
- [OHLCV](#ohlcv)
- [default_vector](#default_vector)
- [MEMORY_BACKTEST](#MEMORY_BACKTEST)
- [POSITION_INDICE](#POSITION_INDICE)


<a id="ohlcv"></a>
### `OHLCV`
This struct countain 6 vectors : 
- open (double)
- high (double)
- low (double)
- close (double)
- volume (double)
- time (__int64)

## Example

```cpp
#include "structure.hpp"

int main()
{
    OHLCV data {};
    data.open = {1, 2, 3, 4};
    data.high = {2, 3, 5, 5};
    data.low = {0, 1, 2, 3};
    data.close = {2, 3, 4, 5};
    data.volume = {2, 2, 4, 4};
    return 0;
}
```

<a id="default_vector"></a>
### `default_vector`
This is a vector who accept None value and double.
None value is equal to std::nullopt

## Example
```cpp
#include "structure.hpp"

int main()
{
    default_vector my_vector {std::nullopt, std::nullopt, 1, 2, 3, 4};
    return 0;
}
```

<a id="MEMORY_BACKTEST"></a>
### `MEMORY_BACKTEST`
This struct is create for save other position during backtest.
The struct countain a lot of vector for all type of position : 
long, short and all.
And countains : profit, time and evolution

```cpp
#include "structure.hpp"

int main()
{
    MEMORY_BACKTEST memory_backtest {};  // add real example
    return 0;
}
```

<a id="POSITION_INDICE"></a>
### `void POSITION_INDICE(bool exporte = true);`
This struct is creat dor save other close and open position, the struct save position in iteration of struct

```cpp
#include "structure.hpp"

int main()
{
    POSITION_INDICE position_indice {}; // add real example
    return 0;
}
```