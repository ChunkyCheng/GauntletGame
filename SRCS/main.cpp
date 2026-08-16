#include <string>
#include <iostream>

#include "MinkowskiCoord.hpp"

int	main(void)
{
	MinkowskiCoord	c(123, -48);

	std::cout << "minkowski: " << c << "\n";
	std::cout << "poincare:  " << c.toPoincare() << "\n";
}
