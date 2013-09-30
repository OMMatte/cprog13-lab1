/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#define _CXXTEST_HAVE_EH
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/ErrorPrinter.h>

int main() {
 return CxxTest::ErrorPrinter().run();
}
#include "../test_must_follow_a.cpp"

static MyTestSuite suite_MyTestSuite;

static CxxTest::List Tests_MyTestSuite = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_MyTestSuite( "../test_must_follow_a.cpp", 5, "MyTestSuite", suite_MyTestSuite, Tests_MyTestSuite );

static class TestDescription_MyTestSuite_test_a_is_second_to_last : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test_a_is_second_to_last() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 17, "test_a_is_second_to_last" ) {}
 void runTest() { suite_MyTestSuite.test_a_is_second_to_last(); }
} testDescription_MyTestSuite_test_a_is_second_to_last;

static class TestDescription_MyTestSuite_test1 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test1() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 24, "test1" ) {}
 void runTest() { suite_MyTestSuite.test1(); }
} testDescription_MyTestSuite_test1;

static class TestDescription_MyTestSuite_test2 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test2() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 30, "test2" ) {}
 void runTest() { suite_MyTestSuite.test2(); }
} testDescription_MyTestSuite_test2;

static class TestDescription_MyTestSuite_test3 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test3() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 36, "test3" ) {}
 void runTest() { suite_MyTestSuite.test3(); }
} testDescription_MyTestSuite_test3;

static class TestDescription_MyTestSuite_test4 : public CxxTest::RealTestDescription {
public:
 TestDescription_MyTestSuite_test4() : CxxTest::RealTestDescription( Tests_MyTestSuite, suiteDescription_MyTestSuite, 42, "test4" ) {}
 void runTest() { suite_MyTestSuite.test4(); }
} testDescription_MyTestSuite_test4;

#include <cxxtest/Root.cpp>
