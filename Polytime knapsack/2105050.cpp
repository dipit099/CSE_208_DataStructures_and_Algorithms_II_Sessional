#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

void reduced_instance(double eps, ll n, ll w, ll maxvalue, vector<ll> &prevvalue, vector<ll> &weight, ll total_prev_value)
{
    cout << "Rounded Instance with Eps: " << eps << endl;
    double theta = (double)(maxvalue * eps) / (2.0 * n);
    cout << "Theta: " << setprecision(16) << theta << endl;

    ll maxi = 0;
    vector<ll> value(n + 1);
    value[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        value[i] = ceil(prevvalue[i] / theta);
        if (prevvalue[i] == maxvalue)
        {
            value[i]++;
        }

        // value[i] = (floor)((double)prevvalue[i] / theta) + 1;
        // value[i] = (ll)ceil((double)prevvalue[i] / theta);

        maxi = max(maxi, value[i]);
    }
    // for (int i = 1; i <= n; i++)
    // {
    //     cout << value[i] << " " << weight[i] << endl;
    // }

    vector<vector<ll>> dp(n + 1, vector<ll>(maxi * n + 1, INT_MAX));
    for (ll v = 0; v <= maxi * n; v++)
    {
        dp[0][v] = INT_MAX;
    }
    for (int i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }

    for (ll i = 1; i <= n; i++)
    {
        for (ll v = 1; v <= maxi * n; v++)
        {
            if (v >= value[i])
            {
                dp[i][v] = min(dp[i - 1][v], weight[i] + dp[i - 1][v - value[i]]);
            }
            else
            {
                dp[i][v] = dp[i - 1][v];
            }
        }
    }

    ll total_value = 0;
    ll weight_used = 0;
    ll total_red_value = 0;
    for (ll v = 0; v <= maxi * n; v++)
    {
        if (dp[n][v] <= w)
        {
            total_value = v;
            weight_used = dp[n][v];
        }
    }
    cout << "Answer of reduced instance: " << total_value << endl;
    cout << "Answer of reduced instance multiplied by theta: " << total_value * theta << endl;
    cout << "Indices: ";
    for (int i = n; i > 0; i--)
    {
        if (dp[i][total_value] != dp[i - 1][total_value])
        {
            cout << i << " ";
            total_red_value += prevvalue[i];
            total_value -= value[i];
        }
    }
    cout << endl;
    cout << "Answer of original instance (rounded up): " << total_red_value << endl;
    cout << "Used weight: " << weight_used << endl;

    cout << "Ratio: " << (double)total_prev_value / (double)total_red_value << endl;

    cout << "-----------------------\n";
    cout << endl;
}

int main()
{
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    ll n, w;
    cin >> n >> w;

    ll maxvalue = 0;
    vector<ll> weight(n + 1), value(n + 1);
    weight[0] = 0;
    value[0] = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> value[i] >> weight[i];
        maxvalue = max(maxvalue, value[i]);
    }

    vector<vector<ll>> dp(n + 1, vector<ll>(maxvalue * n + 1, INT_MAX));

    for (ll v = 0; v <= maxvalue * n; v++)
    {
        dp[0][v] = INT_MAX;
    }
    for (ll i = 0; i <= n; i++)
    {
        dp[i][0] = 0;
    }

    for (ll i = 1; i <= n; i++)
    {
        for (ll v = 1; v <= maxvalue * n; v++)
        {
            if (v >= value[i])
            {
                dp[i][v] = min(dp[i - 1][v], weight[i] + dp[i - 1][v - value[i]]);
            }
            else
            {
                dp[i][v] = dp[i - 1][v];
            }
        }
    }

    // for(int v=0;v<=maxvalue*n;v++){
    //     cout<<dp[n][v]<<" ";
    // }

    ll total_value = 0;
    ll weight_used = 0;
    for (ll v = 0; v <= maxvalue * n; v++)
    {
        if (dp[n][v] <= w)
        {
            total_value = v;
            weight_used = dp[n][v];
        }
    }
    ll temp = total_value;
    cout << "Original Instance:" << endl;
    cout << "Answer: " << total_value << endl;
    cout << "Used Weight: " << weight_used << endl;
    cout << "Indices: ";
    for (ll i = n; i > 0; i--)
    {
        if (dp[i][total_value] != dp[i - 1][total_value])
        {
            cout << i << " ";
            total_value -= value[i];
        }
    }
    cout << endl;
    cout << endl;
    reduced_instance(0.5, n, w, maxvalue, value, weight, temp);
    reduced_instance(0.2, n, w, maxvalue, value, weight, temp);
    reduced_instance(0.1, n, w, maxvalue, value, weight, temp);
    reduced_instance(0.05, n, w, maxvalue, value, weight, temp);
}