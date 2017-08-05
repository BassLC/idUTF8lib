#include "utf8.hpp"
#include <iostream>
#include <bitset>
#include <exception>

//* Private functions *

bool Utf8String::is_valid_utf8_string(const std::string &string) {

	for ( std::size_t pos = 0; pos < string.size(); ++pos ) {

		//IMPORTANT: The way you access a bitset object is completely backwards.
		//EXAMPLE: bitset = 0b10; bitset[0] == 0
		std::bitset<4> bits = (string[pos] >> 4);

		//ASCII character
		if ( bits[4] == 0 ) { 
			continue;
			
		//Continuation character - should NOT be here
		} else if ( bits[4] == 1 && bits[3] == 0 ) { 
			return false;

		} else {
			//Check number of characters
			while ( (bits <<= 1)[4] ) {
				if ( ++pos > (string.size() - 1) ) {
					return false;
				}

				if ( (string[pos] >> 6) != 0b10 ) {
					return false; 
				}
			}
		}
	}

	return true;
}


//* Constructors and Destructor *

Utf8String::Utf8String() noexcept { content.clear(); }


Utf8String::Utf8String(const std::string &string) {
	std::vector<uint8_t> utf8_char;
 
	if ( !is_valid_utf8_string(string) ) {
		throw(std::runtime_error("Invalid UTF8 String in constructor")); 
	}
	
	for ( auto &&chr : string ) {
		std::bitset<2> start_bits = (chr >> 6);

		//ASCII character can just be pushed in
		if ( start_bits[1] == 0 ) {
			content.push_back(std::vector<uint8_t>(1, chr));
			continue;
			
		//If there's more than one byte	
		} else if ( start_bits == 0b11 ) {

			//Check to see if it has to flush the last character
			if ( !utf8_char.empty() ) {
				content.push_back(utf8_char);
				utf8_char.clear();
			}
		}

		utf8_char.push_back(chr);
	}

	//If last character is non-ASCII
	if ( !utf8_char.empty() ) {
		content.push_back(utf8_char);
	}
}


Utf8String::Utf8String(const Utf8String &utf8_structure) noexcept {
	content = utf8_structure.content;
}


Utf8String::~Utf8String() { content.clear(); }


//* Public Interface *

std::string Utf8String::to_string() const {
	std::string temp;

	for ( auto &&chr : content ) {
		temp += std::string(chr.begin(), chr.end());
	}

	return temp;
}


std::size_t Utf8String::size_in_chars() const { return content.size(); }


std::size_t Utf8String::size_in_bytes() const {
	std::size_t size = 0;

	for ( auto &&chr : content ) {
		size += chr.size();
	}

	return size;
}


void Utf8String::clear() { content.clear(); }


void Utf8String::operator=(const std::string &string) {
	Utf8String temp(string);

	content = temp.content;
}


void Utf8String::operator=(const Utf8String &utf8_object) noexcept { content = utf8_object.content; }
