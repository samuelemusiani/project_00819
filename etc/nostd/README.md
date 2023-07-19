# Use of `std` instead of `nostd`
In your code you should always put `nostd::` before a string or a vector declaration. If you want to use the `std` implementation of vectors and strings you have to recompile with `cmake` specifying a custom value for the `STD` variable. The command should look like this:
```
cmake -DSTD=ON ..
```
**NOTE 1:** If you compile simply with `cmake ..` the default value for the `STD` variable is `false`. In other words if you DO NOT specify the custom value for the variable , `cmake` will assume that **you want to use the `nostd` implementation.**

Please note that if you specified that you want to use the `std` version of vectors and strings some methods are not available and something might not work properly, even though the container behind the class is in fact a `std::` container.
