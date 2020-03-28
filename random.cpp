# include "random.h"
//# include <iostream>


# define LONG_DOUBLE_SIZE sizeof(long double)
# define INT_SIZE  sizeof(int)
 int Rand::random_int(int min,int max) {


    static int is_first = 1;

    if(is_first) {

        srand(time(NULL));
    is_first = 0;
    }

    return min+rand()%(max-min);



}



 long double Rand::random(long double min,long double max){


     assert(max>=min);

     long double result = (max-min)*((long double)(Rand::random_int(0,10000))/(long double )(Rand::random_int(1,10000)));
     //std::memcpy(result,result_arr,LONG_DOUBLE_SIZE);
    //  *result =((long double)random_int(0,1000)/(long double )random_int(1,1000))
     result = min + fmod(result,max-min);
     return  result;// ((long double)random_int(0,1000)/(long double )random_int(1,1000));
 }

 int Rand::random(int min,int max){


return Rand::random_int(min,max);

 }



 
 
