#ifndef _GRAPH_TEST_H_
#define _GRAPH_TEST_H_

#include "TestUtil.h"

#include "../Graph.h"

#include <cassert>

namespace TinySTL{
	namespace GraphTest{
		template<class Index, class Value>
		using dGraph = TinySTL::directed_graph < Index, Value > ;

		void testCase1();
		void testCase2();
		void testCase3();
		void testCase4();

		void testAllCases();
	}
}

#endif