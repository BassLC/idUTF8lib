#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "../lib/idutf8lib.hpp"

TEST_CASE("Initialization is correct") {
	Utf8String empty_utf8str;
	REQUIRE(empty_utf8str.to_string().empty() == true);

	Utf8String utf8str("Hello World");
	REQUIRE(utf8str.to_string() == "Hello World");

	Utf8String yet_another_test_str(utf8str);
	REQUIRE(yet_another_test_str.to_string() == "Hello World");
}

TEST_CASE("Public Interface", "[interface]") {
	SECTION("Operators") {
		Utf8String test_str;
		test_str = "ĥéĺĺõ ẃòŕĺd";
		REQUIRE(test_str.to_string() == "ĥéĺĺõ ẃòŕĺd");
	}
	SECTION("to string") {
		Utf8String test_str("hello");
		REQUIRE(test_str.to_string() == "hello");
	}
		
	SECTION("clear") {
		Utf8String test_str("Important API key");
		test_str.clear();
		REQUIRE(test_str.to_string().empty());
	}

	SECTION("size in {chars, bytes}") {
		Utf8String test_str("Heĺĺç");
		REQUIRE(test_str.size_in_chars() == 5);

		test_str = "Not utf8 please";
		REQUIRE(test_str.size_in_bytes() == 15);
	}
		
}
