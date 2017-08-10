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

		SECTION("=") {
			REQUIRE(test_str.to_string() == "ĥéĺĺõ ẃòŕĺd");
		}

		SECTION("[]") {
			REQUIRE( (test_str[0] == "ĥ" && test_str[test_str.size_in_chars() - 1] == "d") );

			bool flag1 = false;
			bool flag2 = false;
			try { test_str[-1]; } catch (std::out_of_range) { flag1 = true; }
			try { test_str[test_str.size_in_chars()]; } catch (std::out_of_range) { flag2 = true; }
			REQUIRE( (flag1 && flag2) );
		}
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

	SECTION("sub utf8str") {
		Utf8String test_string("ççppçç");

		REQUIRE(test_string.sub_utf8str(0,3).to_string() == "ççp");
		REQUIRE(test_string.sub_utf8str(3).to_string() == "pçç");

		bool flag1 = false;
		bool flag2 = false;

		try { test_string.sub_utf8str(test_string.size_in_chars()); } catch (std::out_of_range) { flag1 = true;}
		try { test_string.sub_utf8str(0, 7);} catch (std::out_of_range) { flag2 = true; }

		REQUIRE( (flag1 && flag2 ));
	}
		
}
