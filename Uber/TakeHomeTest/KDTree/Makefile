
CXX=/usr/bin/g++
CXXTESTGEN=./cxxtest-4.3/bin/cxxtestgen
VALGRIND=/usr/local/bin/valgrind
TEST_BIN=test_kdtree

all : run_tests

run_tests : get_binary
		$(VALGRIND) ./$(TEST_BIN)

get_binary: src/KdTree.hpp gen_tests
		$(CXX) -I ./src -I ./cxxtest-4.3/ -g -Werror -std=c++11 -o $(TEST_BIN) \
			GenTestKdTree.cc

gen_tests:
		$(CXXTESTGEN) --error-printer -o GenTestKdTree.cc src/tests/TestKdTree.cc

clean:
		rm -rf ./$(TEST_BIN)*
		rm GenTest*
