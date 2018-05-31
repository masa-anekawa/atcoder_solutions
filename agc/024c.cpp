#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 200005;
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
  std::fill( reinterpret_cast<T*>(array),
             reinterpret_cast<T*>(array+N),
             val );
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

ll N,M,K,A[NMAX],B,C,D,E;
int dp[NMAX] = {};

string S;
vec zeros;

ll ans = {};

ll _solve(int begin, int end){
  // calc minimum opes in [begin, end)
  int pre_a = -1;
  ll ret = 0;
  for (int i = end - 1; i >= begin; --i)
  {
    if(pre_a == -1){
      ret += A[i];
    }
    else if(A[i] > pre_a - 1){
      ret += A[i];
    }
    else if(A[i] < pre_a - 1){
      // impossible
      return -1;
    }else if(A[i] == pre_a - 1){
      // do nothing
    }
    pre_a = A[i];
  }
  return ret;
}

void solve(){
  // main algorithm
  if(A[0] != 0){
    ans = -1;
    return;
  }
  for(int i = 0; i < zeros.size() - 1; ++i) {
    ll part = _solve(zeros[i], zeros[i + 1]);
    if(part == -1){
      ans = -1;
      return;
    }
    else ans += part;
  }
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
    for (int i = 0; i < N ; ++i)
    {
      scanf("%lld", &A[i]);
      if(A[i] == 0)zeros.push_back(i);
    }
    zeros.push_back(N);
    solve();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}