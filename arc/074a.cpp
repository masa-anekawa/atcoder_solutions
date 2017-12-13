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
// #define DEBUG

// frequently used macros

#if __cplusplus >= 201103L
#define ALL(v) begin(v),end(v)
#define SORT(v) sort(begin(v), end(v))
#define FIND(v,x) find(begin(v), end(v), (x))
#define SWAP(a, b) do{auto tmp = (a); (a) = (b); (b) = tmp;}while(0)
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
typedef pair<ll, int> pl;
typedef pair<ll, ll> pll;
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


ll N,M,K,A,B,C,D,E;
int dp[NMAX] = {};

string S;
vec v;
int ansi=-1, ansj=-1;
ll ans = INFLL, diff;
ll c1, c2 ,c3;

void F(int i, int j){
  DUMP(i);
  DUMP(j);
  DUMP(c1);
  DUMP(c2);
  DUMP(c3);
  diff = max(abs(c1-c2), max(abs(c2-c3), abs(c3-c1)));
  if(ans > diff){
    ans = diff;
    ansi = i, ansj = j;
  }
  DUMP(ans);
}

void solve(){
  // main algorithm
  for (int i = 1; i < N + M - 2; ++i)
  {
    ll a,b,c,d;
    int j;
    if(i > N-1) {
      j = i + ((N + M - 1) - i) / 2;
      c1 = N * (i - (N - 1));
      c2 = N * (j - i);
      c3 = N * ((N+M-1) - j);
      F(i, j);
    }else{
      j = (N-1) + M / 2;
      a = i, b = N - i, c = j - (N-1), d = M - (j - (N-1));
      // T
      c1 = a * M;
      c2 = b * c;
      c3 = b * d;
      F(i, j);
      // T rot 90
      c1 = N * c;
      c2 = a * d;
      c3 = b * d;
      F(i, j);
      // T rot 180
      c1 = a * c;
      c2 = a * d;
      c3 = b * M;
      F(i, j);
      // T rot 270
      c1 = a * c;
      c2 = b * c;
      c3 = N * d;
      F(i, j);
      // II
      if(i < N - 1)
      {
        j = i + (N - i) / 2;
        c1 = i * M;
        c2 = (j - i) * M;
        c3 = (N - j) * M;
        F(i, j);
      }
    }
  }

}
void solve2(ll h, ll w){
  for (int i = 1; i <= h - 1; ++i)
  {
    int j;
    c1 = w * i;
    // T
    j = w / 2;
    c2 = (h - i) * j, c3 = (h - i) * (w - j);
    F(i, j);
    // =
    if(i == h - 1) continue;
    j = (h + i) / 2;
    c2 = w * (j - i), c3 = w * (h - j);
    F(i, j);
  }
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  scanf("%lld%lld", &N,&M);
  solve2(N, M);
  solve2(M, N);
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}