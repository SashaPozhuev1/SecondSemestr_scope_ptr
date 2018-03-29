#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("insert and print tree")
{
	std::string input{
		"        ----9\n"
		"                ----8\n"
		"            ----7\n"
		"    ----7\n"
		"        ----6\n"
		"----5\n"
		"        ----4\n"
		"    ----4\n"
		"        ----3\n"};
	
	tree_t<int> tree;
	
	tree.insert(5);
	tree.insert(7);
	tree.insert(4);
	tree.insert(6);
	tree.insert(9);
	tree.insert(7);
	tree.insert(8);
	tree.insert(3);
	tree.insert(4);
	
	std::ostringstream ostream;
	tree.print(ostream);
	REQUIRE( input == ostream.str() );
}

TEST_CASE("find tree")
{
	tree_t<int> tree;
	
	tree.insert(5);
	tree.insert(7);
	tree.insert(4);
	
	REQUIRE( tree.find(5) == true );
	REQUIRE( tree.find(7) == true );
	REQUIRE( tree.find(0) == false );
}

TEST_CASE("read tree")
{
	tree_t<double> tree;
	
	bool success = true;
	for(std::size_t i = 0; i < 5; ++i) {
		if (i == 0) {
			std::string input{"+9.8"};
			
			std::istringstream istream(input);
			std::ostringstream ostream;
		
			success = tree.read(istream, ostream);
			REQUIRE( success == true );
		}
		else if (i == 1) {
			std::string input{"="};
			std::string output{"----9.8\n"};
			std::istringstream istream(input);
			std::ostringstream ostream;
		
			success = tree.read(istream, ostream);
			REQUIRE( success == true );
			REQUIRE( output == ostream.str() );
		}
		else if (i == 2) {
			std::string input{"?1"};
			std::string output{"false"};
			std::istringstream istream(input);
		
			success = tree.read(istream, ostream);
			REQUIRE( success == true );
		}
		else if (i == 3) {
			std::string input{"d"};
			std::istringstream istream(input);
			std::ostringstream ostream;
		
			success = tree.read(istream, ostream);
			REQUIRE( success == true );
		}
		else if (i == 4) {
			std::string input{"q"};
			std::istringstream istream(input);
			std::ostringstream ostream;
		
			success = tree.read(istream, ostream);
			REQUIRE( success == false );
		}
	}
}
