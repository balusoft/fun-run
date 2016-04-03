
CXX=/usr/bin/g++
CXX=/usr/bin/clang++-3.6
CXXTESTGEN=./cxxtest-4.3/bin/cxxtestgen
VALGRIND=/usr/bin/valgrind
TEST_BIN=bin/test_kdtree
BUILD_APP_BIN=bin/build_kdtree
QUERY_APP_BIN=bin/query_kdtree

all : run_tests

run_tests : get_test_binary
	$(VALGRIND) ./$(TEST_BIN)

get_test_binary: src/lib/KDTree.hpp gen_tests
	mkdir -p ./bin
	$(CXX) -I ./src/lib -I ./cxxtest-4.3/ -g -Werror -std=c++11 -o $(TEST_BIN) \
		gen/GenTestKdTree.cc

gen_tests: src/tests/lib/TestKdTree.cc
	mkdir -p ./gen
	$(CXXTESTGEN) --error-printer -o gen/GenTestKdTree.cc src/tests/TestKdTree.cc

clean:
	rm -rf ./bin
	rm -rf ./gen
