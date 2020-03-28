#ifndef RANDOM_H
#define RANDOM_H

# include <ctime>
# include <cstdlib>
# include <cmath>
# include <cassert>
# include <cstring>


typedef char byte  ;
namespace Rand {
int random_int(int min,int max) ;

long double random(long double min,long double max);
int         random(int min,int max);
}
#endif // RANDOM_H
