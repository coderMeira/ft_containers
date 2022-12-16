#include "ft_containers.hpp"

int	main(void)
{
	ft::vector<int>		a;
	std::vector<int>	b;

	b.push_back(0);
	b.push_back(1);
	b.push_back(2);
	b.push_back(3);


	// std::vector<int>::iterator it = b.begin();

	std::cout << b.at(12);

	return (0);
}
