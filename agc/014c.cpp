#include <algorithm>
#include <bitset>
#include <deque>
#include <iostream>
#include <cfloat>
#include <cmath>
#include <cstdarg>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <utility>
#include <vector>
// #include "ane.cpp"

const long long INFLL = 1e18;
const int INF  = 1e9;
const int NMAX = 805;
const int MMAX = 805;
const int MOD  = 1e9 + 7;
using namespace std;

// comment to disable debug functions
#define DEBUG





//
//  library begin
//

// frequently used macros
#define SORT(v) sort(begin(v), end(v))
#define FIND(v,x) find(begin(v), end(v), (x))
#define MEMNEXT(from, to) do{ memmove((to), (from), sizeof(from)); \
                          memset((from), 0, sizeof(from)); } while(0)
#ifdef DEBUG
#define DUMP(x) do{ std::cerr << "(DUMP) " << (#x) << ": " << x << std::endl; }while(0)
#else
#define DUMP(x) do{}while(0)
#endif

// frequent used aliases
typedef long long ll;
typedef pair<int, int> p;
typedef pair<ll, int> lp;
typedef pair<ll, ll> llp;
typedef vector<int> vec;
typedef vector<vec> mat;

// frequently used constants
static const int di[] = {-1, 0, 1, 0};
static const int dj[] = {0, 1, 0, -1};

// freawuently used structs
struct edge{
  int to,cost;
};

// printf for debug
void debug(const char* format, ...){
  #ifndef DEBUG
  return;
  #else
  va_list arg;
  va_start(arg, format);
  vprintf(format, arg);
  va_end(arg);
  #endif
}

// fill of multi dimensions
template<typename A, size_t N, typename T>
void Fill(A (&array)[N], const T &val){
  std::fill( (T*)array, (T*)(array+N), val );
}

// Union-Find Tree
class UnionFindTree{
  struct node{
      int par;
  };
  std::vector<node> T;

  public:
  void init(int num){
      T.resize(num+1);    // ignore T[0]
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

// Segment Tree for Range Minimum Query
  // **********************************************************
  // *** important: all functions' variable,                ***
  // *** such as "index", "l", "r", etc., must be 0-origin. ***
  // **********************************************************
  // ********************************************
  // *** important: NMAX must be a power of 2.***
  // ********************************************
template<typename T>
class SegmentTree{
  private:
  ll N;
  T INF_VAL;
  T dat[NMAX * 2]; // 0 origin, A[i] = dat[i + N]

  T _query(ll l, ll r, ll l_resp, ll r_resp, ll i_dat){
      debug("query(%lld, %lld, %lld, %lld, %lld) called\n",
          l, r, l_resp, r_resp, i_dat);
      if (r < l_resp || r_resp < l) return INF_VAL;
      else if(l <= l_resp && r_resp <= r) return dat[i_dat];
      else return min(_query(l ,r, l_resp, (l_resp + r_resp) / 2, i_dat * 2),
                      _query(l, r, (l_resp + r_resp) / 2 + 1, r_resp, i_dat * 2 + 1));
  }

  public:
  void init(ll _N, T _inf_val){
      N = 1; while(N < _N) N *= 2;
      INF_VAL = _inf_val;
      Fill(dat, _inf_val);
  }
  T get(ll index){
      return dat[index + N];
  }
  void set(int index, T val){
      int i_dat = index + N;
      dat[i_dat] = val;
      for (i_dat /= 2; i_dat > 0; i_dat /= 2)
      {
          dat[i_dat] = min(dat[i_dat * 2], dat[i_dat * 2 + 1]);
      }
  }
  T query(ll l, ll r){
      return _query(l, r, 0, N - 1, 1);
  }
  void dump(){
      cout << "*** SegTree dump begin ***\n";
      cout << "N = " << N << ", INF_VAL = " << INF_VAL << endl;
      for (int i = 1; i < N * 2; i *= 2)
      {
          for (int j = i; j < i * 2; ++j)
          {
              if(dat[j] == INF_VAL) cout << "INF ";
              else cout << dat[j] << " ";
          }
          cout << endl;
      }
      cout << "*** SegTree dump end ***\n";
  }
};

// Binary Indexed Tree for Range Sum Query
  // *******************************************
  // *** important: all functions' variable, ***
  // *** such as "i", must be 1-origin.      ***
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

//
// library end
//




struct state
{
  p coord;
  int walls;
  int dist;
};

ll N,M,K,A,B,C,D,E;
int fromS[NMAX][MMAX][2 * (NMAX + MMAX) ] = {};
// int toG[NMAX][MMAX] = {};
int walls[NMAX][MMAX];
char dat[NMAX][MMAX] = {};
// vector<p> dots;
set<p> exits;
p S;

ll ans = 0;

bool b_search(int x){
  for(auto&& p : exits) {
      if (p.first < (x - 1) * K && p.second < x * K)
      {
          return true;
      }
  }
  return false;
}

void solve(){
  // main algorithm
  // calc fromS
  queue<state> que;
  que.push(state{S, 0, 0});
  vector<state> states[NMAX][MMAX];
  while(!que.empty()) {
      int i = que.front().coord.first;
      int j = que.front().coord.second;
      int walls = que.front().walls;
      int dist = que.front().dist;
      que.pop();
      if(fromS[i][j][walls] <= dist) continue;

      fromS[i][j][walls] = dist;
      if(i == 1 || i == N || j == 1 || j == M)
          exits.insert(p(walls, dist));
      // dots.push_back(p(i, j));
      for (int k = 0; k < 4; ++k)
      {
          int ii = i + di[k];
          int jj = j + dj[k];
          int ww = walls + (dat[ii][jj] == '#' ? 1 : 0);
          if (fromS[ii][jj][ww] > dist && ww < min(M, N))
          {
              que.push(state{p(ii, jj), ww, dist + 1});
          }
      }
  }
  // calc toG
  // for (int i = 1; i <= N; ++i)
  // {
  //     for (int j = 1; j <= M; ++j)
  //     {
  //         toG[i][j] = min(min(i - 1, (int)N - i), min(j - 1, (int)M - j));
  //     }
  // }
  // calc walls

  // binary search
  int ans_upper = min(N ,M);
  int ans_lower = 1;
  while(ans_lower != ans_upper) {
      int ans_mid = (ans_upper + ans_lower) / 2;
      if (!b_search(ans_mid))
      {
          debug("b_search(%d) false\n", ans_mid);
          ans_lower = (ans_mid != ans_lower ? ans_mid : ans_mid + 1);
      }else{
          debug("b_search(%d) true\n", ans_mid);
          ans_upper = ans_mid;
      }
  }
  ans = ans_lower;
}
void debug(){
  // output debug information
  cout << "fromS:\n";
  for (int i = 1; i <= N; ++i)
  {
      for (int j = 1; j <= M; ++j)
      {
          if(dat[i][j] == '#') {
              cout << '#';
          }
          else {
              cout << fromS[i][j][0];
          }
      }
      cout << endl;
  }
  // cout << "toG:\n";
  // for (int i = 1; i <= N; ++i)
  // {
  //     for (int j = 1; j <= M; ++j)
  //     {
  //         cout << toG[i][j];
  //     }
  //     cout << endl;
  // }
}
void answer(){
  // output answer
  printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // operate inputs

  Fill(dat, '#');
  Fill(fromS, INF);
  // FIll(walls, INF;)
  scanf("%lld%lld%lld", &N,&M, &K);
  // dots.reserve(N*M);
  for (int i = 0; i < N; ++i)
  {
      for (int j = 0; j < M; ++j)
      {
          scanf(" %c", &dat[i+1][j+1]);
          if (dat[i+1][j+1] == 'S')
          {
              S = p(i+1, j+1);
              dat[i+1][j+1] = '.';
          }
      }
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}