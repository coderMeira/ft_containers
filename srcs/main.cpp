#include "ft_containers.hpp"

int	main(void)
{
	ft::vector<int>		a;
	std::vector<int>	b;

	a.push_back(111);
	a.push_back(222);
	a.push_back(333);
	a.push_back(444);

	b.push_back(111);
	b.push_back(222);
	b.push_back(333);
	b.push_back(444);


	ft::vector<int>::iterator ita = a.begin();
	std::vector<int>::iterator itb = b.begin();

	for(; ita != a.end(); ita++) {
		std::cout << *ita << "\n";
	}
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	for(; itb != b.end(); itb++) {
		std::cout << *itb << "\n";
	}

	std::cout << "+++++++++++++++++++++++" << "\n";

	std::cout << "a.size() :" << a.size() << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	std::cout << "b.size() :" << b.size() << "\n";

	std::cout << "+++++++++++++++++++++++" << "\n";

	std::cout << "a.capacity() :" << a.capacity() << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	std::cout << "b.capacity() :" << b.capacity() << "\n";

	std::cout << "+++++++++++++++++++++++" << "\n";

	std::cout << "a.empty() :" << a.empty() << "\n";
	std::cout << "~~~~~~~~~~~~~~~~~~~~~~~" << "\n";
	std::cout << "b.empty() :" << b.empty() << "\n";

	return (0);
}
