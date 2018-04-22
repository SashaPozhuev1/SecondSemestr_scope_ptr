#include <catch.hpp>
#include <sstream>

#include "scope.hpp"

TEST_CASE("creating scope_ptr and get ptr")
{
	int * p = new int;
	scoped_ptr <int> scope ( p );
	
	REQUIRE( scope.get() == p );
}

TEST_CASE("operator *")
{
	double * p = new double;
	*p = 6.1;
	scoped_ptr <double> scope ( p );
	
	REQUIRE( *scope == 6.1 );
}

TEST_CASE("operator ->")
{
	int * p = new int;
	*p = 6;
	scoped_ptr <int> scope ( p );
	
	REQUIRE( scope.operator->() == 6 );
}

TEST_CASE("reset")
{
	int * p = new int;
	int * a = new int;
	scoped_ptr<int> scope ( p );
	
	scope.reset(a);
	
	REQUIRE( scope.get() == a );
}

TEST_CASE("swap")
{
	int * p = new int;
	int * a = new int;
	scoped_ptr<int> scope1 ( p );
	scoped_ptr<int> scope2 ( a );
	
	scope1.swap(scope2);
	
	REQUIRE( scope1.get() == a );
	REQUIRE( scope2.get() == p );
}

TEST_CASE("isEmpty")
{
	int * p = new int;
	scoped_ptr<int> scope1 ( p );
	scoped_ptr<int> scope2 ( nullptr );
	
	REQUIRE( scope1.isEmpty() == false );
	REQUIRE( scope2.isEmpty() == true );
}
