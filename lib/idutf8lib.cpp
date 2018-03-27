#include "idutf8lib.hpp"
#include <iostream>
#include <bitset>
#include <exception>
#include <array>

//* Private functions *

bool Utf8String::is_valid_utf8_string(const std::string &string) const {
	for ( std::size_t pos = 0; pos < string.size(); ++pos ) {
		
		//IMPORTANT: The way you access a bitset object is completely backwards.
 		//EXAMPLE: bitset = 0b10; bitset[0] == 0
		std::bitset<4> bits = string[pos] >> 4;

		//ASCII character
		if ( bits[3] == 0 ) {
			continue;
			
		//Continuation character - should NOT be here
		} else if ( bits[3] == 1 && bits[2] == 0 ){
			return false;

		} else {
			
			//Check number of characters
			while ( (bits <<= 1)[3] ) {
				if ( ++pos >= string.size() ) {
					return false;
				}

				if ( std::bitset<2>(string[pos] >> 6) != 0b10 ) {
					return false;
				}
			}
		}
	}

	return true;
}


std::string Utf8String::remove_initial_BOM_char(const std::string &string) const {
	const std::array<uint8_t, 3> BOM_CHARS {0xEF, 0xBB, 0xBF};
	std::string without_BOMS;
	
	for ( int i = 0; i < 3; ++i ) {
		if ( !(static_cast<uint8_t>(string[i]) == BOM_CHARS[i]) ) {
			without_BOMS = string;
			break;

		} else {
			without_BOMS = string.substr(3, std::string::npos);
		}
	}

	return without_BOMS;
}

//* Constructors *

Utf8String::Utf8String(const std::string &string) {
	const std::string to_parse = Utf8String::remove_initial_BOM_char(string);

	if ( !is_valid_utf8_string(string) ) {
		throw(std::runtime_error("Invalid UTF8 String in constructor")); 
	}
	
	std::string utf8_char;
	for ( const auto &chr : to_parse ) {
		std::bitset<2> start_bits = (chr >> 6);
		
		if ( start_bits[1] == 0 ) {

			//If there is an ASCII character, this means the previous UTF8 char is over and can be pushed
			if ( !utf8_char.empty() ) {
				m_content.push_back(utf8_char);
				utf8_char.clear();
			}
			
			//Pushing an ASCII Character (The std::string constructor needs the size)
			m_content.push_back(std::string(1,chr));
			continue;
			
		//If there's more than one byte	
		} else if ( start_bits == 0b11 ) {

			//Check to see if it has to flush the last character
			if ( !utf8_char.empty() ) {
				m_content.push_back(utf8_char);
				utf8_char.clear();
			}
		}

		utf8_char.push_back(chr);
	}

	//If last character is non-ASCII
	if ( !utf8_char.empty() ) {
		m_content.push_back(utf8_char);
	}
}


Utf8String::Utf8String(Utf8Struct &&temp) {
	m_content = temp;
}


//* Public Interface *

std::string Utf8String::to_string() const {
	std::string temp;

	for ( const auto &chr : m_content ) {
		temp += std::string(chr.begin(), chr.end());
	}

	return temp;
}


std::size_t Utf8String::size_in_chars() const { return m_content.size(); }


std::size_t Utf8String::size_in_bytes() const {
	std::size_t size = 0;

	for ( const auto &chr : m_content ) {
		size += chr.size();
	}

	return size;
}


void Utf8String::clear() { m_content.clear(); }


Utf8String Utf8String::sub_utf8str(const std::size_t &initial_pos, const std::size_t &distance) const {

	const std::size_t end_pos = (distance == std::string::npos) ? m_content.size() : (initial_pos + distance);

	// To be sure we don't try to overflow
	if ( initial_pos >= m_content.size() || end_pos > m_content.size() ){
		throw std::out_of_range("Too big substr access");
	}


	return Utf8String(Utf8Struct(m_content.begin()+initial_pos, m_content.begin()+end_pos));
}


//* Operators *

void Utf8String::operator=(const std::string &string) {
	Utf8String temp(string);
	m_content = temp.m_content;
}


void Utf8String::operator=(const Utf8String &utf8_object) noexcept { m_content = utf8_object.m_content; }


std::string Utf8String::operator[](const std::size_t &pos) const {
	if ( pos >= m_content.size() ) {
		throw std::out_of_range("Bad UTF-8 range access with []");
	}

	return std::string(m_content[pos].begin(), m_content[pos].end());
}


Utf8String Utf8String::operator+(const Utf8String &utf8_structure) const noexcept {
	Utf8Struct temp = m_content;
	temp.insert(std::end(temp), std::begin(utf8_structure.m_content), std::end(utf8_structure.m_content));
	return Utf8String(std::move(temp));
}


void Utf8String::operator+=(const Utf8String &utf8_structure) noexcept {
	m_content.insert(std::end(m_content), std::begin(utf8_structure.m_content), std::end(utf8_structure.m_content));
}


std::ostream& operator<<(std::ostream &out, const Utf8String &utf8_structure) noexcept{
	out << utf8_structure.to_string();
	return out;
}


bool Utf8String::operator==(const Utf8String &utf8_structure) const noexcept {
	return (m_content == utf8_structure.m_content);
}


bool Utf8String::operator==(const std::string &string) const noexcept {
	return (this->to_string() == string);
}

