#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 200010;
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
  // Binary Indexed Tree for Range Sum Query
  // *******************************************
  // *** important: all functions' variable, ***
  // *** such as "i", must be 1-origin.    ***
  // *******************************************
  template<typename T>
  class BinaryIndexedTree{
  private:
  ll N;
  T dat[NMAX + 1]; // 1 origin, A[i] = sum(i) - sum(i-1)

  public:
  void init(ll _N){
    N = _N;
    Fill(dat, 0);
  }
  void add(int i, T val){
    while(i <= N) {
      dat[i] += val;
      i += i & -i;
    }
  }
  T sum(ll i){
    T ret = 0;
    while(i > 0) {
      ret += dat[i];
      i -= i & -i; // set last HIGH bit to LOW
    }
    return ret;
  }
  T sum(ll left, ll right){
    return sum(right) - sum(left - 1);
  }
  void dump(){
    cout << "*** BITree dump begin ***\n";
    cout << "N = " << N << endl;
    for (int i = 1; i <= N; i *= 2)
    {
      cout << dat[i] << " ";
    }
    cout << "*** BITree dump end ***\n";
  }
  };

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


ll N,M,K,A[NMAX],B[NMAX],BB[NMAX],B_comp[NMAX] = {},C,D,E;
int dp[NMAX] = {};
ll S[NMAX] = {};
BinaryIndexedTree<int> bit;

ll ans = 0;

void solve(){
  // main algorithm
    debug("B[0] : 0\n");
  for (int i = 1; i <= N; ++i)
  {
    B[i] = B[i-1] + A[i-1] - M;
    BB[i] = B[i];
    DUMP(B[i]);
  }
  sort(BB, BB + 1 + N);
  int uni = distance(BB, unique(BB, BB + 1 + N));
  bit.init(N+1);
  for (int i = 0; i <= N  ; ++i)
  {
    int lb = distance(BB, lower_bound(BB, BB + uni, B[i])) + 1;
    debug("lb for B[%d] (%lld) == %d\n", i, B[i], lb);
    ans += bit.sum(lb);
    debug("ans += %d\n", bit.sum(lb));
    bit.add(lb, 1);
  }
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
  cin >> N >> M;
  for (int i = 0; i < N; ++i)
  {
    scanf("%lld", &A[i]);
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}