CC=clang++ --std=c++14
WARNINGS=-Wall -Werror -Wpedantic
FILES=lib/*.cpp
CATCH=tests/catch/catch.hpp

test: $(FILES)
	$(CC) $(FILES) $(CATCH) tests/tests.cpp 

clean:
	rm a.out
