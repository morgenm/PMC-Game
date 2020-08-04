/*
    Singleton Test
*/

#include "engine/singleton.h"

#include <iostream>

class PlaceHolderClass {
public:
    int GetData() const;

    bool operator==(const PlaceHolderClass& p) const;
private:
    int m_Data = 52;
    int m_UninitializedData;
};

int PlaceHolderClass::GetData() const {
    return m_Data;
}

bool PlaceHolderClass::operator==(const PlaceHolderClass& p) const {
    if( m_Data == p.m_Data && m_UninitializedData == p.m_UninitializedData ) {
        return true;
    }
    else {
        return false;
    }
}

void TestSingletonGood() {
    Singleton<PlaceHolderClass> placeHolderSingleton;
    PlaceHolderClass& placeHolderClass = placeHolderSingleton.Create();
    PlaceHolderClass& placeHolderClass2 = placeHolderSingleton.Create();

    if( placeHolderClass == placeHolderClass2 ) {
        std::cout << "TestSingleton Good Test: Passed.\n";
    }
    else {
        std::cout << "TestSingleton Good Test: FAILED!.\n";
    }
}

int main() {
    TestSingletonGood();
    return 0;
}
