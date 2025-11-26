#pragma once
#include <vector>
#include "hash.h"
using namespace std;

class BloomFilterOne { //
    private:
        vector<bool> table;
        vector<HashOne> hashes;
    public:
        BloomFilterOne(long long m, int k, long long p) {
            table.resize(m, false);
            for(int i = 0; i < k; i++) {
                hashes.push_back(HashOne(m, p));
            }
        }

        void add(long long x) {
            for(auto& h : hashes) {
                long long index = h.hash(x);
                table[index] = true;
            }
        }

        bool contains(long long x) const {
            for(const auto& h : hashes) {
                long long index = h.hash(x);
                if(table[index] == false) return false;
            }
            return true;
        }
};


class BloomFilterTwo { 
    private:
        vector<bool> table;
        vector<HashTwo> hashes;
    public:
        BloomFilterTwo(long long m, int k, long long p) {
            table.resize(m, false);
            for(int i = 0; i < k; i++) {
                hashes.push_back(HashTwo(m));
            }
        }

        void add(long long x) {
            for(auto& h : hashes) {
                long long index = h.hash(x);
                table[index] = true;
            }
        }

        bool contains(long long x) const {
            for(const auto& h : hashes) {
                long long index = h.hash(x);
                if(table[index] == false) return false;
            }
            return true;
        }
};











