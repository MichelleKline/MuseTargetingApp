#include <catch2/catch.hpp>
#include "MuseTargetingDOF.cpp"


TEST_CASE("DOF.constructors", "[DOF]")
{
//    // check arg constructors
//    // name, min, max, value
//    MuseTargetingDOF DOF_A;
//    DOF_A.setName("A");
////    MuseTargetingDOF DOF_A("A", 0, 100, 50);
//    CHECK(DOF_A.getName() == "hello");
//    CHECK(DOF_A.getMin() == 0);
//    CHECK(DOF_A.getMax() == 100);
//    CHECK(DOF_A.getValue() == 50);

//    // name, min, max (default value == 0)
//    MuseTargetingDOF DOF_B("B", 0, 100);
//    CHECK(DOF_B.getName() == "B");
//    CHECK(DOF_B.getMin() == 0);
//    CHECK(DOF_B.getMax() == 100);
//    CHECK(DOF_B.getValue() == 0);

    // default constructor
    MuseTargetingDOF DOF_C;
    CHECK(DOF_C.getName() == "undefined");
    CHECK(DOF_C.getMin() == 0);
    CHECK(DOF_C.getMax() == 0);
    CHECK(DOF_C.getValue() == 0);
}

//void define(std::string name, double lowerLimit, double upperLimit);
TEST_CASE("DOF.define", "[DOF]")
{
    MuseTargetingDOF DOF_D;
    DOF_D.define("D", -50, 50);
    CHECK(DOF_D.getName() == "D");
    CHECK(DOF_D.getMin() == -50);
    CHECK(DOF_D.getMax() == 50);
}

//void setName(std::string name);
//void setMax(double upperLimit);
//void setMin(double lowerLimit);
//bool setValue(double value);
TEST_CASE("DOF.setget", "[DOF]")
{
    MuseTargetingDOF DOF_E;
    DOF_E.setName("E");
    CHECK(DOF_E.getName() == "E");
    DOF_E.setMin(25);
    CHECK(DOF_E.getMin() == 25);
    DOF_E.setMax(100);
    CHECK(DOF_E.getMax() == 100);
    DOF_E.setValue(50);
    CHECK(DOF_E.getValue() == 50);
}

