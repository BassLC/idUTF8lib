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
	Utf8String(Utf8Struct &&content);
	Utf8String(const std::string &string);
	~Utf8String() = default;
	
	std::string to_string() const;
	std::size_t size_in_chars() const;
	std::size_t size_in_bytes() const;
	void clear();
	Utf8String sub_utf8str(const std::size_t &initial_pos, const std::size_t &distance = std::string::npos) const;

	void operator=(const std::string &string);
	void operator=(const Utf8String &utf8_structure) noexcept;
	
	Utf8String operator+(const Utf8String &utf8_structure) const noexcept;
	void operator+=(const Utf8String &utf8_structure) noexcept;
	
	std::string operator[](const std::size_t &pos) const;

	friend std::ostream& operator<<(std::ostream &out, const Utf8String &utf8_structure) noexcept;

	bool operator==(const Utf8String &utf8_structure) const noexcept;
	bool operator==(const std::string &string) const noexcept;
};

#endif
