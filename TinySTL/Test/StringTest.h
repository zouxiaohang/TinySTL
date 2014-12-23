#ifndef _STRING_TEST_H_
#define _STRING_TEST_H_

#include "TestUtil.h"

#include "../String.h"
#include <string>

#include <cassert>
#include <iterator>

namespace TinySTL{
	namespace StringTest{
		using stdStr = std::string;
		using tsStr = TinySTL::string;
	}
}

#endif