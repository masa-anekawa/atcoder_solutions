#include <bits/stdc++.h>
// #include "ane.cpp"

const int INF  = 2e9;
const long long INFLL = 1e18;
const int NMAX = 100005;
const int MMAX = 200005;
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
  int to,num;
};
struct node
{
  int root, par,
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


int N,M,K,L[MMAX], R[MMAX], D[MMAX],pos[NMAX] = {};
bool used[MMAX] = {};
vector<edge> G[NMAX];
bool ans = true;

inline bool check(int num){
  assert(num > 0);
  assert(num <= M);
  return pos[R[num]] - pos[L[num]] = D[num];
}

bool bfs(int s){
  queue<int> que;
  que.push(s);
  while(!que.empty()) {
    int i = que.front();
    que.pop();
    for(auto&& e : G[i]) {
      if(pos[e.to] != INF){
        pos[e.to] = pos[i] + D[e.num];
        used[e.to] = true;
      }else {
        if(!check(e.num)) return false;
      }

      if(i > 0){
        used[i] = true;

      }else{

      }
      que.push(e.to);
    }
  }
  return true;
}

bool solve(){
  // main algorithm
  fill(ALL(pos), INF);
  for (int num = 1; num <= M; ++num)
  {
    if(used[num]) continue;
    used[num] = true;
    pos[L[num]] = 0;
    if(!bfs(L[num])) return false;
  }
  return true;
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  cout << (ans ? "Yes" : "No") << endl;
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> N >> M;
  for (int i = 1; i <= M; ++i)
  {
    scanf("%lld%lld%lld", &L[i], &R[i], &D[i]);
    G[L[i]].push_back(edge{R[i], i});
    G[R[i]].push_back(edge{L[i], -i});
  }
  ans = solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}