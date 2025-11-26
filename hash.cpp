#include "hash.h"
#include <stdexcept>
using namespace std;

HashOne::HashOne(long long tableSize, long long prime): m(tableSize), p(prime){
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> a_func(1, p - 1);
    uniform_int_distribution<long long> b_func(0, p - 1);
    a = a_func(gen);
    b = b_func(gen);

}

long long HashOne::hash(long long x) const {
    long long val = a;
    val *= x;
    val += b;
    return (val % p) % m;
}

HashTwo::HashTwo(long long tableSize): m(tableSize) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(0, 0xFFFFFFF);
    seed = dist(gen);
}

long long HashTwo::hash(long long x) const {
    mt19937 gen(seed + x);
    return gen() % m;
}


