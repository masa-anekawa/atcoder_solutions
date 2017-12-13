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
#define NMAX (int)(1e9+5)
#define MMAX 200
#define MOD 100000
using namespace std;

// コメントアウトするとdb_printf()を実行しない
#define DEBUG
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
typedef pair<int, int> p;
typedef long long ll;

ll N,M,K,A,B,C,D,E;
ll dp[NMAX];

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

ll ans = 0;

ll solve(ll t, ll dist){
  // 解答アルゴリズム
  if (dp[dist] != INF)
  {
      return dp[dist];
  }
  if (t == dist)
  {
      return 1;
  }
  ll cand = solve(t+1, dist-t) + 1;
  if()
  return dp[dist] = min(min(solve(t+1, dist-t),
                        solve(1, dist)),
                        dist - t)
                  + 1LL;

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

  Fill(dp, INF);

  scanf("%lld", &N);
  ans = solve(1, N);
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}