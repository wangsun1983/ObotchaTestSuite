#include "StringBuffer.hpp"

using namespace obotcha;


void testAppend() {
    while(1) {
      StringBuffer buffer = createStringBuffer(1);
      buffer->append("abc","abc2","abc3");
      if(!buffer->toString()->equals("abcabc2abc3")) {
        printf("StringBuffer append test1-------[FAILED] \n");
      }
      break;
    }

    while(1) {
      StringBuffer buffer = createStringBuffer(1);
      buffer->append('a','b','c');
      if(!buffer->toString()->equals("abc")) {
        printf("StringBuffer append test2-------[FAILED] \n");
      }
      break;
    }

    printf("StringBuffer append test100-------[OK] \n");
}