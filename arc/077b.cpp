#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 100005;
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
ll BSearch(ll _begin, ll _end, bool (*f)(int)){
  ll mid;
  while(_end - _begin > 1LL) {
  mid = (_begin + _end) / 2LL;
  if(f(mid)) {
    debug("BSearch: f(%d) == true\n", mid);
    _end = mid;
  }
  else
  {
    debug("BSearch: f(%d) == false\n", mid);
    _begin = mid;
  }
  }
  return _end;
}


ll N,M,K,A[NMAX],B[NMAX],C,D,E;
vec dp(NMAX), dp2(NMAX);

int pos[2] = {-1, -1};

ll ans = {};

ll comb(k){
  if(dp[k]) return dp[k];
  for (int i = 0; i <= N; ++i)
  {
    vec ddp(NMAX, 1);
    int j;
    for (j = 1; j < i; ++j)
    {
      ddp[j] = (dp[j] + dp[j-1]) % MOD;
    }
    dp = ddp;
  }
  return dp[k];
}

ll comb2(k){
  if(dp2[k]) return dp2[k];
  for (int i = 0; i <= N - 2; ++i)
  {
    vec ddp2(NMAX, 1);
    int j;
    for (j = 1; j < i; ++j)
    {
      ddp2[j] = (dp2[j] + dp2[j-1]) % MOD;
    }
    dp2 = ddp2;
  }
  return dp2[k];
}

void solve(){
  // main algorithm
  for (int i = 0; i < count; ++i)
  {
    /* code */
  }
  ans = comb(K);
  if(K == 1) return;
  ans = (ans + comb2(K - 2)) % MOD;

}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << ans << endl;
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> N;
  for (int i = 0; i < N; ++i)
  {
    scanf("%lld", &A[i]);
    B[i] = A[i];
  }

  // find double appearance
  ll num;
  sort(B, B + N);
  for (int i = 0; i < N; ++i)
  {
    if(i && B[i] == B[i-1]){
      num = B[i];
    }
  }
  for (int i = 0; i < N; ++i)
  {
    if (A[i] == num)
    {
      if(pos[0] == -1) {
        pos[0] = i;
      }
      else {
        pos[1] = i;
      }
    }
  }

  for (int i = 1; i <= N; ++i)
  {
    K = i;
    solve();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}