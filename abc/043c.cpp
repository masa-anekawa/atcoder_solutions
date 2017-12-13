#define SORT(v) sort(v.begin(), v.end())
#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <stack>
#include <cstdlib>
#include <algorithm>
#include <cstdarg>
#include <cstdio>
#include <numeric>

// #include "ane.cpp"

#define INF (int)1e9
#define INFLL (long long)1e18
#define NMAX 103
#define MMAX 200
#define MOD 100000
using namespace std;

// コメントアウトするとdb_printf()を実行しない
#define DEBUG

//
//  ライブラリ
//

// よく使う型のエイリアス
typedef pair<int, int> p;
typedef long long ll;

// よく使う定数[配列]
static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

// デバッグ用printf
void db_printf(const char* format, ...){
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

//
// ライブラリ終了
//


ll N,M,K,A[NMAX],B,C,D,E;
int dp[NMAX][MMAX] = {};

ll ans = INFLL;

void solve(){
  // 解答アルゴリズム
  for (int t = -100; t <= 100; ++t)
  {
      ll cand = 0;
      for (int i = 0; i < N; ++i)
      {
          cand += (A[i] - t) * (A[i] - t);
      }
      ans = min(ans, cand);
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
  scanf("%lld", &N);
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