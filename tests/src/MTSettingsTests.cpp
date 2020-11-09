#include <catch2/catch.hpp>
//#include "MuseTargetingSettings.cpp"
//
//
//TEST_CASE("Settings.constructors", "[settings]")
//{
//    // check constructor
//    MuseTargetingSettings S1;
//    CHECK(S1.getNumSettings() == 0);
//}
////
//////void addSetting(std::string name, double min, double max, double value);
//////void addSetting(std::string name, double min, double max);
//////void setValue(std::string settingName, double val);
//////std::vector<MuseDegreeOfFreedom> getSettings();
//////double getSettingMin(std::string settingName);
//////double getSettingMax(std::string settingName);
//////double getSettingValue(std::string settingName);
////TEST_CASE("Settings.setget", "[settings]")
////{
////    MuseTargetingSettings S2;
////    S2.addSetting("A", 0, 10, 5);
////    CHECK(S2.getNumSettings() == 1);
////    CHECK(S2.getSettingMin("A") == 0);
////    CHECK(S2.getSettingMax("A") == 10);
////    CHECK(S2.getSettingValue("A") == 5);
////
////    S2.addSetting("B", -10, 100); // default value == 0
////    CHECK(S2.getNumSettings() == 2);
////    CHECK(S2.getSettingMin("B") == -10);
////    CHECK(S2.getSettingMax("B") == 100);
////    CHECK(S2.getSettingValue("B") == 0);
////
////    S2.setValue("B", 12);
////    CHECK(S2.getSettingValue("B") == 12);
////
////    std::vector<MuseDegreeOfFreedom> allSettings = S2.getSettings();
////    CHECK(allSettings.size() == 2);
////}
//
//
