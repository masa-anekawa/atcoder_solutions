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
  int from, to,cost;
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

class UnionFindTree{
  struct node{
    int par;
  };
  std::vector<node> T;

  public:
  void init(int num){
    T.resize(num+1);  // ignore T[0]
    for (int i = 1; i <= num; ++i)
    {
    T[i].par = i;
    }
  }
  void unite(int x, int y){
    T[find(y)].par = find(x);
  }
  int find(int x){
    if (T[x].par == x) return x;
    else return T[x].par = find(T[x].par);
  }
  bool same(int x, int y){
    return find(x) == find(y);
  }
};

ll N,M,K,A[NMAX],B[NMAX],C,D;
int dp[NMAX] = {};


std::vector<edge> E;
std::vector<p> VX,VY;
UnionFindTree uft;
#define FI first
#define SE second
ll ans = {};

inline bool comp(const edge& lhs, const edge& rhs){
  return lhs.cost < rhs.cost;
}

void solve(){
  // main algorithm
  M = (N-1) * 2;
  sort(E.begin(), E.begin() + M, comp);
  for (int i = 0; i < M; ++i)
  {
    edge e = E[i];
    if(uft.same(e.from, e.to)) continue;
    ans += e.cost;
    uft.unite(e.from, e.to);
  }
}
void debug(){
  // output debug information
  cout << "E:\n";
  for(auto&& e : E) {
    debug("%d -> %d : %d\n", e.from, e.to, e.cost);
  }
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
  uft.init(N);
  for (int i = 1; i <= N; ++i)
    {
      int x,y;
      scanf("%d%d", &x, &y);
      VX.push_back(p{x,i});
      VY.push_back(p{y,i});
    }
  SORT(VX);
  SORT(VY);
  for (int i = 0; i < N-1; ++i)
  {
    E.push_back(edge{VX[i].second, VX[i+1].second,
      VX[i+1].first - VX[i].first});
    // E.push_back(edge{VX[i+1].second, VX[i].second,
    //   VX[i+1].first - VX[i].first});
  }
  for (int i = 0; i < N-1; ++i)
  {
    E.push_back(edge{VY[i].second, VY[i+1].second,
      VY[i+1].first - VY[i].first});
    // E.push_back(edge{VY[i+1].second, VY[i].second,
    //   VY[i+1].first - VY[i].first});
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}