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
#define NMAX 200
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

ll N,M,K,A,B,C,E;
std::vector<int> D;
int dp[NMAX][MMAX] = {};

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

ll ans = 0;

bool check(int p){
  while(p) {
      int digit = p % 10;
      p /= 10;

      if (find(D.begin(), D.end(), digit) != D.end())
      {
          return false;
      }
  }
  return true;
}
void solve(){
  // 解答アルゴリズム
  for (int price = N; ; ++price)
  {
      if (check(price))
      {
          ans = price;
          break;
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

  Fill(dp, -1);

  scanf("%lld%lld", &N, &M);
  for (int i = 0; i < M; ++i)
  {
      int x; scanf("%d", &x);
      D.push_back(x);
  }
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}