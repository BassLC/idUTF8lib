#define CATCH_CONFIG_MAIN
#include "catch/catch.hpp"
#include "../lib/idutf8lib.hpp"

TEST_CASE("Initialization is correct") {
	Utf8String empty_utf8str;
	REQUIRE(empty_utf8str == "");

	Utf8String utf8str("Hello World");
	REQUIRE(utf8str == "Hello World");

	Utf8String yet_another_test_str(utf8str);
	REQUIRE(yet_another_test_str == "Hello World");
}

TEST_CASE("Public Interface", "[interface]") {
	SECTION("Operators") {

		Utf8String test_str;
		test_str = "ĥéĺĺõ ẃòŕĺd";

		SECTION("[]") {
			REQUIRE( (test_str[0] == "ĥ" && test_str[test_str.size_in_chars() - 1] == "d") );

			bool flag1 = false;
			bool flag2 = false;
			try { test_str[-1]; } catch (std::out_of_range) { flag1 = true; }
			try { test_str[test_str.size_in_chars()]; } catch (std::out_of_range) { flag2 = true; }
			REQUIRE( (flag1 && flag2) );
		}

		SECTION("+") {
			Utf8String other_test_str("sup");
			REQUIRE( (test_str + other_test_str) == "ĥéĺĺõ ẃòŕĺdsup");

		}

		SECTION("<<") { 
			std::stringstream os;
			os << test_str;

			REQUIRE( test_str == os.str() );
		}
	}
	
	SECTION("to string") {
		Utf8String test_str("hello");
		REQUIRE(test_str == "hello");
	}
		
	SECTION("clear") {
		Utf8String test_str("Important API key");
		test_str.clear();
		REQUIRE(test_str == "");
	}

	SECTION("size in {chars, bytes}") {
		Utf8String test_str("Heĺĺç");
		REQUIRE(test_str.size_in_chars() == 5);

		test_str = "Not utf8 please";
		REQUIRE(test_str.size_in_bytes() == 15);
	}

	SECTION("sub utf8str") {
		Utf8String test_string("ççppçç");

		REQUIRE(test_string.sub_utf8str(0,3) == "ççp");
		REQUIRE(test_string.sub_utf8str(3) == "pçç");

		bool flag1 = false;
		bool flag2 = false;

		try { test_string.sub_utf8str(test_string.size_in_chars()); } catch (std::out_of_range) { flag1 = true;}
		try { test_string.sub_utf8str(0, 7);} catch (std::out_of_range) { flag2 = true; }

		REQUIRE( (flag1 && flag2 ));
	}
}
