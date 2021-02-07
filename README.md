# :evergreen_tree: fir
A single header, C++ 17 library designed to simplify console input parsing.

**Please note that fir is currently a work in progress and is likely to be subject to breaking changes!**

# example
```c++
// Copy on write fluent interface.
fir::parse_result<int> choice = fir::console::readln()
	.trim()
	.parse_int()
	.between(0, 3);

// Implicilty convertible to bool. 
if (choice)
{
    fir::console::writeln("You selected %i!", *choice);
}

```
