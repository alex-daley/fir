# :evergreen_tree: fir
A single header, C++ 17 library designed to simplify console input parsing.

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
