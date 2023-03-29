//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __FT_CONTAINERS_HPP__
# define __FT_CONTAINERS_HPP__

#include <iostream>
#include <memory>
#include <sstream>
#include <stdlib.h>
#include <assert.h>
#include <iterator>
#include <vector>
#include "iterator_traits.hpp"
#include "type_traits.hpp"
#include "random_access_iterator.hpp"
#include "reverse_iterator.hpp"
#include "vector.hpp"
#include "pair.hpp"
#include "map.hpp"
#include "../redblacktree/inc/rbt.hpp"


template <typename T>
std::string to_string(T n) {
	std::ostringstream ostr;
	ostr << n;
	return ostr.str();
}

#endif
