
CXX=/usr/bin/g++
CXX=/usr/bin/clang++-3.6
CXXTESTGEN=./cxxtest-4.3/bin/cxxtestgen
VALGRIND=/usr/bin/valgrind
TEST_BIN=test_kdtree

all : run_tests

run_tests : get_binary
	$(VALGRIND) ./$(TEST_BIN)

get_binary: src/KDTree.hpp gen_tests
	$(CXX) -I ./src -I ./cxxtest-4.3/ -g -Werror -std=c++11 -o $(TEST_BIN) \
		GenTestKdTree.cc

gen_tests: src/tests/TestKdTree.cc
	$(CXXTESTGEN) --error-printer -o GenTestKdTree.cc src/tests/TestKdTree.cc

clean:
	rm -rf ./$(TEST_BIN)*
	rm GenTest*
