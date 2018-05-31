#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 1000005;
const int MMAX = 100005;
const int KMAX = 1005;
const int MOD  = 1e9 + 7;
using namespace std;

// comment to disable debug functions
#define DEBUG

// frequently used macros

#if __cplusplus >= 201103L
#define ALL(v) begin(v),end(v)
#define SORT(v) sort(begin(v), end(v))
#define FIND(v,x) find(begin(v), end(v), (x))
#else
#define ALL(v) (v).begin(),(v).end()
#define SORT(v) sort(v.begin(), v.end())
#define FIND(v,x) find(v.begin(), v.end(), (x))
#endif

#define fi first
#define se second

#define MEMNEXT(from, to) do{ memmove((to), (from), sizeof(from)); \
memset((from), 0, sizeof(from)); } while(0)
#ifdef DEBUG
#define DUMP(x) do{ std::cerr << (#x) << ": " << x << std::endl; }while(0)
#else
#define DUMP(x) do{}while(0)
#endif

// frequent used aliases
typedef long long ll;
typedef pair<int, int> p;
typedef pair<ll, int> lp;
typedef pair<ll, ll> llp;
typedef vector<int> vec;
typedef vector<ll> vecll;
typedef vector<vec> mat;
typedef vector<vecll> matll;
typedef unordered_map<ll, ll> umap;

// frequently used constants
static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

// frequently used structs
struct edge{
  int to,cost;
};

// printf for debug
#ifndef DEBUG
void debug(const char* format, ...){}
#else
void debug(const char* format, ...){
  va_list arg;
  va_start(arg, format);
  vprintf(format, arg);
  va_end(arg);
}
#endif

// dump vector
#ifdef DEBUG
#define DUMPV(v, c) do{       \
  printf("%s: ", #v);         \
  for (int i = 0; i < (c); ++i) \
  {                           \
  cout << (v)[i] << " ";      \
  }                           \
  cout << endl;               \
} while(0)
#else
#define DUMPV(v,c)
#endif

// std::fill of multi dimensions
template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
  std::fill( (T*)array, (T*)(array+N), val );
}

// binary search
ll BSearch(ll ok, ll ng, bool (*f)(ll)){
  ll mid;
  while(abs(ok - ng) > 1LL) {
    mid =  (ok + ng) / 2LL;
    if(f(mid)) {
      debug("BSearch: f(%d) == true\n", mid);
      ok = mid;
    }
    else
    {
      debug("BSearch: f(%d) == false\n", mid);
      ng = mid;
    }
  }
  return ok;
}

ll NUM_TEST_CASE = 1;

ll N,M,K,A,B,C,D,E;
int dp[NMAX] = {};

string S;
vec v;

ll ans = {};

ll facto[NMAX], inv[NMAX];

ll biExp(ll x, int power){
  if(power == 0) return 1;
  ll xx = biExp(x, power / 2);
  xx = xx * xx % MOD;
  if(power % 2) xx = xx * x % MOD;
  return xx;
}

ll calcComb(int n, int r){
  if(r > n || r < 0) return 0;
  if(n == r || r == 0) return 1;
  return facto[n] * inv[r] % MOD * inv[n-r] % MOD;
}

ll solve(){
  // main algorithm
  if(N == 2) return 1;
  if(N == 3) return 4;
  if(N == 4) return 16;
  // calc facto
  facto[0] = 1;
  for (int i = 1; i <= N; ++i)
  {
    facto[i] = facto[i - 1] * i % MOD;
  }
  // calc inv
  inv[N] = biExp(facto[N], MOD - 2);
  for (int i = N; i > 0; --i)
  {
    inv[i - 1] = inv[i] * i % MOD;
  }

  // calc sum for all k
  ll sum = 0, preCount = 0, count = 0;
  for (int k = (N + 1) / 2; k < N; ++k)
  {
    count = calcComb(k - 1, N - 1 - k) * facto[k] % MOD
          * facto[N - 1 - k] % MOD;
    sum = (sum + (count - preCount) * k % MOD) % MOD;
    preCount = count;
  }
  return sum;
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << ans << endl;
}
void init(){
  // initialize for each test case
  // Fill(dp, -1);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // cin >> NUM_TEST_CASE;

  for (int test_case = 0; test_case < NUM_TEST_CASE; ++test_case)
  {
    init();

    cin >> N;
    ans = solve();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}