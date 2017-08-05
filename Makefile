CC=clang++ --std=c++14
WARNINGS=-Wall -Werror -Wpedantic
FILES=lib/*.cpp
CATCH=tests/catch/catch.hpp

idUTF8lib:
	$(CC) $(WARNINGS) $(FILES) main.cpp -O2 -o idUTF8lib

debug:
	$(CC) $(WARNINGS) $(FILES) main.cpp -g -o debug

tests:
	$(CC) $(FILES) $(CATCH) tests/tests.cpp
