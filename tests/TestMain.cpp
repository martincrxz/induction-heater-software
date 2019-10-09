//
// Created by Martín García on 24/08/2019.
//

#include <cppunit/extensions/TestFactoryRegistry.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/ui/text/TestRunner.h>

CPPUNIT_TEST_SUITE_REGISTRATION(TestCommunicator);

using CppUnit::TestFactoryRegistry;

int main( int argc, char **argv) {
    CppUnit::TextUi::TestRunner runner;
    TestFactoryRegistry &registry = TestFactoryRegistry::getRegistry();
    runner.addTest( registry.makeTest() );
    runner.run();
    return EXIT_SUCCESS;
}

