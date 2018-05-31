#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 1e9;
const long long INFLL = 1e18;
const int NMAX = 105;
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
typedef pair<int, int> P;
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
  ll to,rev, cap;
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
ll BSearch(ll _begin, ll _end, bool (*f)(ll)){
  ll mid;
  while(_end - _begin > 1LL) {
    mid = _begin + (_end - _begin) / 2LL;
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

ll NUM_TEST_CASE = 1;

ll N,M,K,A[NMAX],B[NMAX],C[NMAX],D[NMAX],E;
bool used[NMAX];
vector<llp> Rs, Bs;
vector<edge> G[2 * NMAX];

ll ans = {};

void add_edge(int from, int to, int cap){
  G[from].push_back(edge{to, (ll)G[to].size(), cap});
  G[to].push_back(edge{from, (ll)G[from].size() - 1, 0});
}
ll dfs(ll i, ll t, ll f){
  debug("dfs(%d, %d, %d)\n" ,i, t, f);
  used[i] = true;
  if (i == t) return f;
  for(auto&& e : G[i]) {
    ll ff;
    if(!used[e.to] && e.cap > 0 && (ff = dfs(e.to, t, min(f, e.cap))) > 0)
    {
      e.cap -= ff;
      G[e.to][e.rev].cap += ff;
      return ff;
    }
  }
  return 0;
}

ll max_flow(ll s, ll t){
  ll ret = 0;
  while(true) {
    memset(used,false, NMAX);
    ll f = dfs(s, t, INF);
    if(f == 0){
      return ret;
    }
    ret += f;
  }
}

void solve(){
  // main algorithm
  for (int i = 0; i < N; ++i)
  {
    for (int j = 0; j < N; ++j)
    {
      llp r = Rs[i], b = Bs[j];
      if(r.fi < b.fi && r.se < b.se){
        add_edge(i, j + N, 1);
      }
    }
  }
  for(int i = 0; i < N; ++i)add_edge(2 * N, i, 1);
  for(int i = 0; i < N; ++i)add_edge(i + N, 2 * N + 1, 1);

  ans = max_flow(2 * N, 2 * N + 1);
}
void debug(){
  // output debug information
  for (int i = 0; i < 2 * N + 2; ++i)
  {
    printf("G[%d]: ", i);
    for(auto&& e : G[i]) {
      printf("%lld(<->G[%lld][%lld]):%lld) ", e.to, e.to, e.rev, e.cap);
    }
    cout << endl;
  }
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
    for (int i = 0; i < N; ++i)
    {
      scanf("%lld%lld", &A[i], &B[i]);
      Rs.push_back(llp{A[i], B[i]});
    }
    for (int i = 0; i < N; ++i)
    {
      scanf("%lld%lld", &C[i], &D[i]);
      Bs.push_back(llp{C[i], D[i]});
    }
    solve();
    #ifdef DEBUG
    debug();
    #endif
    answer();
  }

  return 0;
}