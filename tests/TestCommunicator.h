//
// Created by Martín García on 24/08/2019.
//

#ifndef TRABAJOPROFESIONAL_TESTRECEIVER_H
#define TRABAJOPROFESIONAL_TESTRECEIVER_H

#include <cppunit/extensions/HelperMacros.h>
#include <QCoreApplication>
#include "../src/connection/communicator.h"

#define PRINT(X) std::cout<<X<<std::endl

class TestCommunicator : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE(TestCommunicator);
    CPPUNIT_TEST_SUITE_END();

    private:

    public:
        void setUp() override {}
        void tearDown() override {}
    protected:


};

#endif //TRABAJOPROFESIONAL_TESTRECEIVER_H
