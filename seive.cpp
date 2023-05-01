#include <bits/stdc++.h>
using namespace std;

/////*********************   ALL THESE CAN AT MOST PASS N=1e7  **************************/////////

const int N = 1e6 + 1;
vector<vector<int>> factors(N);
vector<bool> prime(N, 1);
vector<int> primes;
vector<int> pref(N,0);
void seive()
{
    prime[0] = prime[1] = 0;
    int i;
    for (i = 2; i * i < N; i++)
    {
        if (prime[i])
        {
            primes.push_back(i);
            for (int j = i * i; j < N; j += i)
            {
                prime[j] = 0;
            }
        }
    }
    for (i; i < N; i++)
    {
        if (prime[i])
            primes.push_back(i);
    }
    for(int i=2;i<N;i++){
        if(prime[i]){
            pref[i]=1+pref[i-1];
        }else pref[i]=pref[i-1];
    }
}
vector<int> factorize(int x)
{
    vector<int> fact;
    int s = primes.size();
    for (int i = 0; i < s && primes[i] * primes[i] <= x; i++)
    {
        if (x % primes[i] == 0)
        {
            fact.push_back(primes[i]);
            while (x % primes[i] == 0)
            {
                x = x / primes[i];
            }
        }
    }
    if (x != 1)
    {
        fact.push_back(x);
    }
    return fact;
}
void INITIALIZE_PRIME_FACTORS()
{
    seive();
    for (int i = 1; i < N; i++)
    {
        factors[i] = factorize(i);
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
vector<vector<int>> primefactors(N);
vector<bool> isprime(N, 1);
vector<int> primenums;
vector<int> hp(N, 0), lp(N, 0);

void seive2()
{
    isprime[0] = isprime[1] = 0;
    for (int i = 2; i < N; i++)
    {
        if (isprime[i])
        {
            lp[i] = hp[i] = i;
            for (int j = 2 * i; j < N; j += i)
            {
                isprime[j] = 0;
                hp[j] = i;
                if (lp[j] == 0)
                    lp[j] = i;
            }
        }
    }
    for (int i = 2; i < N; i++)
    {
        if (isprime[i])
            primenums.push_back(i);
    }
}
vector<int> primefactorize(int x)
{
    vector<int> temp;
    while (x > 1)
    {
        int y = lp[x];
        temp.push_back(y);
        while (x % y == 0)
        {
            x /= y;
        }
    }
    return temp;
}

void initializeprimefactors()
{
    seive2();
    for (int i = 1; i < N; i++)
    {
        primefactors[i] = primefactorize(i);
    }
}
vector<vector<int>> divisors(N);
void initializedivisors()
{
    for (int i = 2; i < N; i++)
    {
        for (int j = i; j < N; j += i)
        {
            divisors[j].push_back(i);
        }
    }
}


int main()
{
    initializeprimefactors();
    INITIALIZE_PRIME_FACTORS();
    initializedivisors();
    cout<<primes.size()<<endl;
    // seive--> fastest
    // seive2-->fast enough and versatile
    /*seive(){     // faster than NloglogN
       prime[]----->boolean (whether prime or not);
       primes[]------>prime numbers in range
       factors[[]]----->prime factors of i;
       factorize()----->fastest prime factorization(can make changes to function as we need);
       INITIALIZE_PRIME_FACTORS();---> for intitializing all of these at once;
    }
    */
    /*seive2(){    //NloglogN
       isprime[]----->boolean (whether prime or not);
       primenums[]------>prime numbers in range
       primefactors[[]]----->prime factors of i;
       primefactorize()----->fastest prime factorization(can make changes to function as we need);
       lp[]----->lowerst prime factor of i;
       hp[]----->highest prime factor of i;
       initializeprimefactors();---> for intitializing all of these at once;
    }
    */
    /*initializedivisors();   //NlogN
       divisors[[]]------>all factors/divisors of i;
       initializedivisors()------->seive variation to find divisors;
    */

    /////*********************     ALL THESE CAN AT MOST PASS N=1e7  **************************/////////

    return 0;
}
