
CXX=/usr/bin/g++
CXX=/usr/bin/clang++-3.6
CXXTESTGEN=./cxxtest-4.3/bin/cxxtestgen
VALGRIND=/usr/bin/valgrind
TEST_BIN=bin/test_kdtree
TEST_BUILD_KDTREE_BIN=bin/test_build_kdtree
TEST_QUERY_KDTREE_BIN=bin/test_query_kdtree
BUILD_APP_BIN=bin/build_kdtree
QUERY_APP_BIN=bin/query_kdtree

all : run_tests build_kdtree

run_tests : get_lib_test_binary get_build_kdtree_test_binary
	$(VALGRIND) ./$(TEST_BIN)
	$(VALGRIND) ./$(TEST_BUILD_KDTREE_BIN)

get_lib_test_binary: src/lib/KDTree.hpp gen_tests
	mkdir -p ./bin
	$(CXX) -I ./src -I ./cxxtest-4.3/ -g -Werror -std=c++11 -o $(TEST_BIN) \
		gen/GenTestKdTree.cc

gen_tests: src/tests/lib/TestKdTree.cc
	mkdir -p ./gen
	$(CXXTESTGEN) --error-printer -o gen/GenTestKdTree.cc src/tests/lib/TestKdTree.cc

get_build_kdtree_test_binary: get_lib_test_binary gen_build_kdtree_tests
	mkdir -p ./bin
	$(CXX) -I ./src -I ./cxxtest-4.3/ -g -Werror -std=c++11 -o $(TEST_BUILD_KDTREE_BIN) \
		gen/GenTestBuildKdTree.cc src/build_kdtree/BuildKdTree.cc

gen_build_kdtree_tests: src/tests/build_kdtree/TestBuildKdTree.cc
	mkdir -p ./gen
	$(CXXTESTGEN) --error-printer -o gen/GenTestBuildKdTree.cc src/tests/build_kdtree/TestBuildKdTree.cc

build_kdtree: get_lib_test_binary gen_build_kdtree_tests
	mkdir -p ./bin
	$(CXX) -I ./src -I ./cxxtest-4.3/ -g -Werror -std=c++11 -o $(BUILD_APP_BIN) \
		 src/build_kdtree/BuildKdTree.cc src/build_kdtree/BuildKdTreeMain.cc

clean:
	rm -rf ./bin
	rm -rf ./gen
