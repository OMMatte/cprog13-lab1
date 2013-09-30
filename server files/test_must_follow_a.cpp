#include <cxxtest/TestSuite.h>

#include "must_follow_a.h"

class MyTestSuite : public CxxTest::TestSuite 
{
public:

    // Testcase 1

    // This testcase sets up a 5 sized array (precondition). Note that
    // the second argument (length) to must_follow_a is 4. The
    // expected result is successs.

    // Do make additional tests of your own and try it out. 

    void test_a_is_second_to_last( void )
    {
        char vek[] = {'x', 'x', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 4, 'a', 'b');
        TS_ASSERT_EQUALS( result, 1);
    }

    void test1( void ) {
        char vek[] = {'x', 'x', 'a', 'b', 'x'};
        int result = must_follow_a(vek, 3, 'a', 'b');
        TS_ASSERT_EQUALS( result, 0);
    }

    void test2( void ) {
        char test[] = {'b', 'a', 'n', 'a', 'n' };
        int result = must_follow_a(test, 4, 'a', 'n');
        TS_ASSERT_EQUALS(result, 0);
    }

    void test3( void ) {
        char test[] = { 'H', 'A', 'N', 'A', ' ', 'B', 'A', 'N', 'A', 'N', 'A', 'N' };
        int result = must_follow_a(test, strlen(test), 'A', 'N');
        TS_ASSERT_EQUALS(result, 4);
    }

    void test4( void ) {
        char test[] = { 'h', 'a', 'b', 'A', 'n', 'A', ' ', 'n', 'a', 'b', 'a', 'N' };
        int result = must_follow_a(test, strlen(test), 'n', 'A');
        TS_ASSERT_EQUALS(result, 1);
    }
};
