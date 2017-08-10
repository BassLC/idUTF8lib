# Idiot's UTF-8 Library
A very (too much really) simple Utf8 library for C++

## Usage

```cpp
#include "lib/idutf8lib.hpp"

Utf8String text; //Empty UTF8 object
Utf8String utf8_text("Héĺĺò Ẃórld"); //std::string compatible constructor
text = "Jello!"; //Supports assignment with std::string AND Utf8String objects
text.to_string(); // == std::string("Jello!")

utf8_text.size_in_chars(); // == 11
utf8_text.size_in_bytes(); // == 18 

utf8_text[0]; // == std::string("H")
utf8_text.sub_utf8str(1,3); // == Utf8String("éĺĺ")

```

## Features
* Decodes and parses UTF-8 strings correctly (at least until now)
* Very lightweight and small: less than 200 newlines total (*without counting tests)


## Requirements
* A C++14 compatible compiler


## Notes
Makefile serves only for testing purposes.

Uses the [Catch](https://github.com/philsquared/Catch) framework for tests.

## Thanks
[UTF8-CPP](http://utfcpp.sourceforge.net/)

[tiny-utf8](https://sourceforge.net/projects/tiny-utf8/)