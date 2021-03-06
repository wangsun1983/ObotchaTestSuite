#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <functional>

#include "Integer.hpp"
#include "String.hpp"

using namespace obotcha;

extern void testImport();
extern void testReflect();
extern void testHashMapStringString();
extern void testArrayListString();
extern void testUserDataReflect();
extern void testInnerClassReflect();
extern void testArrayListInteger();
extern void testArrayListUint8();
extern void testArrayListUint16();
extern void testArrayListUint32();
extern void testArrayListUint64();
extern void testArrayListLong();
extern void testArrayListDouble();
extern void testArrayListFloat();
extern void testArrayUserData();
extern void testHashMapIntegerInteger();
extern void testHashMapUint8Uint8();
extern void testHashMapUint16Uint16();
extern void testHashMapUint32Uint32();
extern void testHashMapUint64Uint64();
extern void testHashMapByteByte();
extern void testHashMapLongLong();
extern void testHashMapUserdata();
extern void testHashMapList();
extern void testArrayListMap();
extern void testMapList();
extern void testReflectNullItems();

int main() {
    //testReflect();
    //testImport();

    testMapList();
    testArrayListMap();
    testHashMapList();
    testHashMapUserdata();
    testHashMapUint8Uint8();
    testHashMapUint16Uint16();
    testHashMapUint32Uint32();
    testHashMapUint64Uint64();
    testHashMapByteByte();
    testHashMapLongLong();
    testHashMapIntegerInteger();
    testHashMapIntegerInteger();
    testArrayUserData();
    testArrayListFloat();
    testArrayListDouble();
    testArrayListLong();

    testArrayListUint8();
    testArrayListUint16();
    testArrayListUint32();
    testArrayListUint64();

    testArrayListInteger();
    testInnerClassReflect();
    testUserDataReflect();
    testHashMapStringString();
    testArrayListString();
    testReflectNullItems();
}
