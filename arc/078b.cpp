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


int N,M,K,A,B,C,D,E;
vec G[NMAX];
string S;
int dist[NMAX], frm[NMAX];

bool ans = {};

pair<int, vector<int> > dijkstra(int s){
  Fill(dist, INF);
  Fill(frm, INF);
  queue<p> que;
  que.push(p(0, s));
  dist[s] = 0;
  int cnt = 0;
  while(!que.empty()) {
    int d = que.front().first;
    int i = que.front().second;
    debug("d: %d, i: %d\n", d, i);
    que.pop();
    cnt++;
    for(auto&& j : G[i]) {
      if(dist[j] == INF) {
        que.push(p(d + 1, j));
        dist[j] = d + 1;
        frm[j] = i;
      }
    }
  }
  vec path;
  int i = N;
  while(i != INF) {
    path.push_back(i);
    i = frm[i];
  }
  reverse(ALL(path));
  return make_pair(cnt, path);
}

void solve(){
  // main algorithm
  auto ret = dijkstra(1);
  auto path = ret.second;
  #ifdef DEBUG
  cout << "path: \n";
  for(auto&& i : path) {
    cout << i << " -> ";
  }
  cout << endl;
  #endif
  int i, j;
  if(path.size() % 2) {
    i  = path[path.size() / 2];
    j = path[path.size() / 2 + 1];
    G[i].erase(find(ALL(G[i]), j));
    G[j].erase(find(ALL(G[j]), i));
  }
  else {
    i = path[path.size() / 2 - 1];
    j = path[path.size() / 2];
    G[i].erase(find(ALL(G[i]), j));
    G[j].erase(find(ALL(G[j]), i));
  }
  debug("remove edge between %d nad %d\n", i, j);
  int fc = dijkstra(1).first, sc = dijkstra(N).first;

  ans = fc > sc;
}
void debug(){
  // output debug information

}
void answer(){
  // output answer
  if(ans) {
    cout << "Fennec\n";
  }
  else {
    cout << "Snuke\n";
  }
}
int main(int argc, char const *argv[])
{
  // operate inputs

  // Fill(dp, -1);
  cin >> N;
  for (int i = 0; i < N - 1; ++i)
  {
    int x,y;
    scanf("%d%d", &x, &y);
    G[x].push_back(y);
    G[y].push_back(x);
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}