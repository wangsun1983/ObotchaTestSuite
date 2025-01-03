#include <stdio.h>
#include <unistd.h>
#include "Math.hpp"
#include "Random.hpp"
#include "TestLog.hpp"
#include "Integer.hpp"
#include "Double.hpp"

using namespace obotcha;

int main() {

    //int next<int>()
    while(1) {
        int array[1000];
        bool isOk = true;
        Random rand = Random::New();
        for(int index = 0;index < 1000;index++) {
            int v1 = rand->next<int>();
            for(int ckindex = 0;ckindex < index;ckindex++) {
                if(v1 == array[ckindex]) {
                    isOk = false;
                    break;
                }
            }

            array[index] = v1;

            if(!isOk) {
                TEST_FAIL("[TestRandom Test {next<int>(int)} case1]");
                break;
            }
        }

        if(isOk) {
            TEST_OK("[TestRandom Test {next<int>(int)} case2]");
            break;
        }

        break;
    }

    //static int next<int>(int min,int max);
    while(1) {
        int max = 100;
        int min = 10;
        Random rand = Random::New();
        for(int index = 0;index < 100000;index++) {
            int v = rand->next<int>(min,max);
            if(v > max || v < min) {
                TEST_FAIL("[TestRandom Test {next<int>(int,int)} case1] [FAIL] ");
                break;
            }
        }

        TEST_OK("[TestRandom Test {next<int>(int,int)} case2]");
        break;
    }

    //static int next<int>(int min);
    while(1) {
        int min = 10;
        Random rand = Random::New();
        for(int index = 0;index < 100000;index++) {
            int v = rand->next<int>(min,st(Integer)::kMaxValue);
            if(v < min) {
                TEST_FAIL("[TestRandom Test {next<int>(int)} case1] [FAIL] ");
                break;
            }
        }

        TEST_OK("[TestRandom Test {next<int>(int)} case2]");
        break;
    }

    //static double next<double>();
    while(1) {
        double array[1000];
        bool isOk = true;
        Random rand = Random::New();
        for(int index = 0;index < 1000;index++) {
            double v1 = rand->next<double>();
            //std::cout<<"v1 is "<<v1;
            for(int ckindex = 0;ckindex < index;ckindex++) {
                //if(v1 == array[ckindex]) {
                if(st(Double)::Compare(v1,array[ckindex]) == 0) {
                    //std::cout<<"v1 is "<<v1<<";array["<<ckindex<<"] = "<<array[ckindex]<<std::endl;
                    isOk = false;
                    break;
                }
            }

            array[index] = v1;

            if(!isOk) {
                TEST_FAIL("[TestRandom Test {next<double>()} case1]");
                break;
            }
        }

        if(isOk) {
            TEST_OK("[TestRandom Test {next<double>()} case2]");
            break;
        }

        break;
    }



    //static double next<double>(double min,double max);
    while(1) {
        Random rand = Random::New();
        for(int index = 0;index < 1000;index++) {
            double min = 10.0001;
            double max = 15.00001;
            double t = rand->next<double>(min,max);
            if(st(Double)::Compare(t,min) !=  1|| st(Double)::Compare(t,max) != -1) {
                TEST_FAIL("[TestRandom Test {next<double>(double,double)} case1]");
                break;
            }
        }

        TEST_OK("[TestRandom Test {next<double>(double,double)} case2]");
        break;
    }

    //static double next<double>(double min);
    while(1) {
        Random rand = Random::New();
        for(int index = 0;index < 1000;index++) {
            double min = 10.0001;
            double t = rand->next<double>(min,st(Double)::kMaxValue);
            if(st(Double)::Compare(t,min) != 1) {
                TEST_FAIL("[TestRandom Test {next<double>(double)} case1]");
                break;
            }
        }

        TEST_OK("[TestRandom Test {next<double>(double)} case2]");
        break;
    }

    //static void nextBytes(ByteArray);
    while(1) {
        Random rand = Random::New();
		for(int i = 0;i < 16;i++) {
			ByteArray data = ByteArray::New(32);
			rand->nextBytes(data);
			int maxHit = 4;
			
			for(int i = 0; i < data->size();i++) {
				auto vv = data->at(i);
				int hit_num = 0;
				for(int j = i;j < data->size();j++) {
					if(vv == data->at(j)) {
						hit_num++;
					}
				}
				//data->dump("data:");
				if(hit_num >= maxHit) {
					TEST_FAIL("[TestRandom Test {nextBytes(double)} case3,hit_num is %x]",hit_num);
				}
			}
		}

        TEST_OK("[TestRandom Test {next<double>(double)} case2]");
        break;
    }
}
