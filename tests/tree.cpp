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
	
	tree_t<int> tree { 5, 7, 4, 6, 9, 7, 8, 3, 4 };
	
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

TEST_CASE("remove tree")
{
	tree_t<int> tree { 5, 7, 4 };
	
	REQUIRE( tree.remove(6) == false );
	REQUIRE( tree.remove(7) == true );
	REQUIRE( tree.remove(5) == true );
	REQUIRE( tree.remove(4) == true );
}

TEST_CASE("compare tree")
{
	tree_t<int> A { 5, 7, 4 };
	tree_t<int> B { 5, 7, 4 };
	tree_t<int> C { 5, 7, 4, 4 };
	
	REQUIRE( (A == B) == true );
	REQUIRE( (C == B) == false );
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
			std::ostringstream ostream;
			
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

SCENARIO("BST delete non inserted element", "[delete]") {
    tree_t<int> tree = {8};
    REQUIRE( !tree.remove(4) );
    REQUIRE( !tree.isEmpty() );
}

SCENARIO("BST delete root without children", "[delete]") {
    tree_t<int> tree = {8};
    REQUIRE( tree.remove(8) );
    REQUIRE( tree.isEmpty() );
}

SCENARIO("BST delete root with one child", "[delete]") {
    tree_t<int> tree = {8, 4, 3};
    REQUIRE( tree.remove(8) );
    REQUIRE( tree == tree_t<int>({4, 3}) );
}

SCENARIO("BST delete root with children", "[delete]") {
    tree_t<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(8) );
    REQUIRE( tree == tree_t<int>({10, 9, 4, 3, 13, 11, 12}) );
}

SCENARIO("BST delete non root without children", "[delete]") {
    tree_t<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(3) );
    REQUIRE( tree == tree_t<int>({8, 4, 10, 9, 13, 11, 12}) );
}

SCENARIO("BST delete non root with one child", "[delete]") {
    tree_t<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(11) );
    REQUIRE( tree == tree_t<int>({8, 4, 3, 10, 9, 13, 12}) );
}

SCENARIO("BST delete non root with children", "[delete]") {
    tree_t<int> tree = {8, 4, 3, 10, 9, 13, 11, 12};
    REQUIRE( tree.remove(10) );
    REQUIRE( tree == tree_t<int>({8, 4, 3, 13, 11, 12, 9}) );
}
