#include <fir.hpp>

int main()
{
	// Copy on write fluent interface.
	fir::parse_result<int> choice = fir::console::read_line()
		.trim()
		.parse_int()
		.between(0, 3);

	// Implicilty convertible to bool. 
	if (choice)
	{
		fir::console::write_line("You selected %i!", *choice);
	}
}
