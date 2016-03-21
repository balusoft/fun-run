./cxxtest-4.3/bin/cxxtestgen --error-printer -o ${1}.cc $1
/usr/bin/clang++ -I ./cxxtest-4.3/ -g -Werror -std=c++11 ${1}.cc
valgrind ./a.out
rm -rf ./a.out*
rm ./${1}.cc
