#ifndef UTF8_CPP
#define UTF8_CPP

#include <string>
#include <vector>


class Utf8String {

private:
	using Utf8Struct = std::vector<std::vector<uint8_t>>;
	
	Utf8Struct content;

	bool is_valid_utf8_string(const std::string &string) const;

public:
	Utf8String() = default;
	Utf8String(const Utf8String &) = default;
	Utf8String(const std::string &string);
	~Utf8String() = default;
	
	std::string to_string() const;
	std::size_t size_in_chars() const;
	std::size_t size_in_bytes() const;
	void clear();

	void operator=(const std::string &string);
	void operator=(const Utf8String &utf8_structure) noexcept;
};

#endif
