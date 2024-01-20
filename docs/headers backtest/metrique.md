# Documentation metrique.hpp

## Description
This file contain 1 function 
- [_metrique](#metrique)

<a id="metrique"></a>
### `void _metrique(MEMORY_BACKTEST positions);`
This function print simple metrique of a backtest
#### parameter : 
- MEMORY_BACKTEST

## Example

```cpp
#include "metrique.hpp"

int main()
{
    MEMORY_BACKTEST my_data {}; // result of a backtest, position etc
    _metrique(my_data);
}
```
