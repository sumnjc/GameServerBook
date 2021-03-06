#include "stdafx.h"
#include <vector>
#include <iostream>
#include <chrono>
#include <mutex>

using namespace std;
const int MaxCount = 15000000;

bool IsPrimeNumber(int number)
{
    if (number == 1)
        return false;
    if (number == 2 || number == 3)
        return true;
    for (int i = 2; i < number - 1; i++)
    {
        if ((number % i) == 0)
            return false;
    }
    return true;
}

void PrintNumbers(const vector<int>& primes)
{
    for (int v : primes)
    {
        cout << v << endl;
    }
}

int main()
{
    vector<int> primes;

    recursive_mutex primes_mutex;

    auto t0 = chrono::system_clock::now();

    #pragma omp parallel for schedule(guided)
    for (int i = 1; i <= MaxCount; i++)
    {
        if (IsPrimeNumber(i))
        {
            lock_guard<recursive_mutex> primes_lock(primes_mutex);
            primes.push_back(i);
        }
    }
    auto t1 = chrono::system_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(t1 - t0).count();
    cout << "Took " << duration << " milliseconds." << endl;

    //    PrintNumbers(primes); 실제로 소수를 출력하면 이 함수의 주석을 해제하세요.

    return 0;
}
