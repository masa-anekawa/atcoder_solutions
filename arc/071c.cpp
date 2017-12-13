#define SORT(v) sort(v.begin(), v.end())
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <algorithm>
#include <cstdlib>
#include <cstdarg>
#include <cstdio>
#include <cmath>
#include <numeric>
#include <utility>

// #include "ane.cpp"

#define INF (int)1e9
#define INFLL (long long)1e18
#define NMAX 100005
#define MMAX 100005
#define MOD 100000
using namespace std;

// コメントアウトするとdebug()を実行しない
// #define DEBUG





//
//  ライブラリ
//

// frequent used aliases
typedef long long ll;
typedef pair<int, int> p;
typedef pair<ll, int> lp;
typedef pair<ll, ll> llp;
typedef vector<int> vec;
typedef vector<vec> mat;

// frequent used constants
static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

// デバッグ用printf
void debug(const char* format, ...){
  #ifndef DEBUG
  return;
  #endif
  va_list arg;
  va_start(arg, format);
  vprintf(format, arg);  // コンソールに出力
  va_end(arg);
}

// n次元配列の初期化。第２引数の型のサイズごとに初期化していく。
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
  // *** important: NMAX must be power of 2. ***
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
// ライブラリ終了
//







int N,M,K,A[NMAX],B[NMAX],C[NMAX],D[NMAX],E;
int dp[NMAX] = {};
string S,T;
ll ans = 0;

void solve(){
  // 解答アルゴリズム
  for (int i = 0; i < N; ++i)
  {
      string s = S.substr(A[i] - 1, B[i] - A[i] + 1);
      string t = T.substr(C[i] - 1, D[i] - C[i] + 1);

      int c;
      do
      {
          c = s.size();
          // cout << "s_first: " << s << endl;
          string nex = "";
          int i;
          for (i = 0; i + 2 < s.size(); ++i)
          {
              debug("i = %d\n", i);
              string cdn = s.substr(i, 3);
              if (cdn == string("BBB") || cdn == string("AAA"))
              {
                  i += 2;
              }else if(cdn == string("ABA") || cdn == string("ABB")
                      || cdn == string("BAB") || cdn == string("BAA") ){
                  i += 1;
              }else if(cdn == "AAB"){
                  nex += "B";
                  i += 1;
              }else{ // cdn == "BBA"
                  nex += "A";
                  i += 1;
              }
          }
          debug("last i = %d\n", i);
          string cdn = s.substr(i, s.size() - i);
          if (cdn == string("BA") || cdn == string("AB"))
          {
              cdn = "";
          }else if (cdn == string("BB"))
          {
              cdn = "A";
          }else if(cdn == string("AA")){
              cdn = "B";
          }
          nex += cdn;
          s = nex;
          // cout << "s: " << s << endl;
      } while (c != s.size());

      do
      {
          c = t.size();
          // cout << "t_first: " << t << endl;
          string nex = "";
          int i;
          for (i = 0; i + 2 < t.size(); ++i)
          {
              debug("i = %d\n", i);
              string cdn = t.substr(i, 3);
              if (cdn == string("BBB") || cdn == string("AAA"))
              {
                  i += 2;
              }else if(cdn == string("ABA") || cdn == string("ABB")
                      || cdn == string("BAB") || cdn == string("BAA") ){
                  i += 1;
              }else if(cdn == "AAB"){
                  nex += "B";
                  i += 1;
              }else{ // cdn == "BBA"
                  nex += "A";
                  i += 1;
              }
          }
          debug("last i = %d\n", i);
          string cdn = t.substr(i, t.size() - i);
          if (cdn == string("BA") || cdn == string("AB"))
          {
              cdn = "";
          }else if (cdn == string("BB"))
          {
              cdn = "A";
          }else if(cdn == string("AA")){
              cdn = "B";
          }
          nex += cdn;
          t = nex;
          // cout << "t: " << t << endl;
      } while (c != t.size());

      if (s == t)
      {
          printf("YES\n");
      }else{
          printf("NO\n");
      }
  }
}
void debug(){
  // デバッグ用出力
}
void answer(){
  // 解答出力
  printf("%lld\n", ans);
}
int main(int argc, char const *argv[])
{
  // 入力の読み込み，番兵法

  // Fill(dp, -1);
  cin >> S >> T >> N;
  for (int i = 0; i < N; ++i)
  {
      scanf("%d%d%d%d", &A[i], &B[i], &C[i], &D[i]);
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  // answer();

  return 0;
}