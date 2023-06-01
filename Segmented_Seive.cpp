    auto SegmentedSeive = [&](ll l, ll r)
    {
       ll N = sqrtl(r);
        vector<bool> isprime(N + 1, false);
        vector<ll> primes;
        for (int i = 2; i <= N; i++)
        {
            isprime[i] = true;
        }

        for (ll i = 2; i <= N; i++)
        {
            if (isprime[i] == true)
            {
                primes.push_back(i);
                for (ll j = i * i; j <= N; j += i)
                {
                    isprime[j] = false;
                }
            }
        }

        vector<bool> rangePrime(r - l + 1, true);
        if (l == 1)
            rangePrime[0] = false;

        for (auto &i : primes)
        {
            ll start = (l / i) * i;
            if (start < l)
                start += i;
            start = max(i * i, start);
            for (ll j = start; j <= r; j += i)
            {
                rangePrime[j - l] = false;
            }
        }
        return rangePrime;
    };
