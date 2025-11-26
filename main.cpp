/*Global Parameters:
for step 1: 
N = 2^31 - 1
p = N = 2^31 - 1
m << N = 1000
numItems = 2m = 2000

for step 2:
N = 2^31-1
p = N
n = 100,000
numQueries = n
numTrials = 10
c = [8, 10, 12]
k = {[3, 4, 5, 6, 7, 8, 9], [4, 5, 6, 7, 8, 9, 10, 11], [5, 6, 7, 8, 9, 10, 11, 12]}
*/

#include <iostream>
#include "hash.h"
#include <vector>
#include <fstream>
#include <random>
#include <sstream>
#include <cmath>
#include "bloomfilter.h"
#include <algorithm>
using namespace std;

double theoretical_fpr(int k, int c) {
    double e = -static_cast<double>(k) / c;
    return pow(1.0 - exp(e), k);
}

vector<int> k_ranges(int c) {
    if(c == 8) return {3, 4, 5, 6, 7, 8, 9};
    if(c == 10) return {5, 6, 7, 8, 9, 10, 11, 12};
    if(c == 12) return {6, 7, 8, 9, 10, 11, 12, 13};
    return {};
}


int main() {
    long long N = 2147483647;

    long long m_one = 1000;
    long long numItems = 2000;

    HashOne hash_one(m_one, N);
    HashTwo hash_two(m_one);
    vector<int> bins(m_one, 0);

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<long long> dist(0, N - 1);

    //one, random
    for(int i = 0; i < numItems; i++) {
        long long num = dist(gen);
        long long index = hash_one.hash(num);
        bins[index]++;
    }
    ofstream data_file1("hashOne_random.csv");
    data_file1 << "bin_id,load\n";
    for (long long i = 0; i < m_one; ++i) {
        data_file1 << i << "," << bins[i] << "\n";
        bins[i] = 0;
    }
    data_file1.close();

    //one, correlated
    for(long long i =0; i < numItems; i++) {
        long long num = i * 2;
        long long index = hash_one.hash(num);
        bins[index]++;
    }
    ofstream data_file2("hashOne_correlated.csv");
    data_file2 << "bin_id,load\n";
    for (long long i = 0; i < m_one; ++i) {
        data_file2 << i << "," << bins[i] << "\n";
        bins[i] = 0;
    }
    data_file2.close();

    //two, random
    for(int i = 0; i < numItems; i++) {
        long long num = dist(gen);
        long long index = hash_two.hash(num);
        bins[index]++;
    }
    ofstream data_file3("hashTwo_random.csv");
    data_file3 << "bin_id,load\n";
    for (long long i = 0; i < m_one; ++i) {
        data_file3 << i << "," << bins[i] << "\n";
        bins[i] = 0;
    }
    data_file3.close();

    //two, correlated
    for(long long i =0; i < numItems; i++) {
        long long num = i * 2;
        long long index = hash_two.hash(num);
        bins[index]++;
    }
    ofstream data_file4("hashTwo_correlated.csv");
    data_file4 << "bin_id,load\n";
    for (long long i = 0; i < m_one; ++i) {
        data_file4 << i << "," << bins[i] << "\n";
        bins[i] = 0;
    }
    data_file4.close();

    long long n = 100000;
    long long p = N;
    long long numQueries = 100000;
    int numTrials = 10;
    vector<int> cvals = {8, 10, 12};

    ofstream data_file5("hashOne_false_positive_experiment.csv");
    data_file5 << "hash_type, c, k, median, theoretical\n";

    for(int c : cvals) {
        long long m = c * n;
        vector<int> kvals = k_ranges(c);

        for(int k : kvals) {
            vector<double> trial_fprs;
            for(int i = 0; i < numTrials; i++) {
                long long fp = 0;
                BloomFilterOne filterOne(m, k, p);

                for(long long ii = 0; ii < n; ii++) {
                    filterOne.add(ii);
                }
                for(long long ii = n; ii < n + numQueries; ii++) {
                    if(filterOne.contains(ii)) {
                        fp++;
                    }

                }
                double fpr = static_cast<double>(fp) / numQueries;
                trial_fprs.push_back(fpr);
            }
            sort(trial_fprs.begin(), trial_fprs.end());
            double median = trial_fprs[numTrials / 2];
            double t_fpr = theoretical_fpr(k, c);

            data_file5 << "HashOne" << "," << c << "," << k << "," << median << "," << t_fpr << endl;
        }
    }
    data_file5.close();

    ofstream data_file6("hashTwo_false_positive_experiment.csv");
    data_file6 << "hash_type, c, k, median, theoretical\n";

    for(int c : cvals) {
        long long m = c * n;
        vector<int> kvals = k_ranges(c);

        for(int k : kvals) {
            vector<double> trial_fprs;
            for(int i = 0; i < numTrials; i++) {
                long long fp = 0;
                BloomFilterTwo filterTwo(m, k, p);

                for(long long ii = 0; ii < n; ii++) {
                    filterTwo.add(ii);
                }
                for(long long ii = n; ii < n + numQueries; ii++) {
                    if(filterTwo.contains(ii)) {
                        fp++;
                    }

                }
                double fpr = static_cast<double>(fp) / numQueries;
                trial_fprs.push_back(fpr);
            }
            sort(trial_fprs.begin(), trial_fprs.end());
            double median = trial_fprs[numTrials / 2];
            double t_fpr = theoretical_fpr(k, c);

            data_file6 << "HashTwo" << "," << c << "," << k << "," << median << "," << t_fpr << endl;
        }
    }
    data_file6.close();

    cout << "success";







    return 0;
}













