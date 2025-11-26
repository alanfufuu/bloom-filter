#pragma once
#include <random>

class HashOne { // basic hash
    public:
        HashOne(long long tableSize, long long prime);

        long long hash (long long x) const;

    private:
        long long a;
        long long b;
        long long m;
        long long p;

};


class HashTwo { // rng seed hash
    public:
        HashTwo(long long tableSize);
        long long hash(long long x) const;
    private:
        long long seed;
        long long m;
    
};

















