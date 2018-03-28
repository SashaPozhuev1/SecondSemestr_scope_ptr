#include <catch.hpp>
#include <sstream>

#include "tree.hpp"

TEST_CASE("creating tree")
{
	tree_t<int> tree;
	REQUIRE( tree.root() == nullptr );
}

TEST_CASE("insert")
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

TEST_CASE("find")
{
	tree_t<int> tree;
	
	tree.insert(5);
	tree.insert(7);
	tree.insert(4);
	
	REQUIRE( tree.find(5) == true );
	REQUIRE( tree.find(7) == true );
	REQUIRE( tree.find(0) == false );
}
