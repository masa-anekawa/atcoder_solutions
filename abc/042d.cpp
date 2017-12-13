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
#define NMAX 100004
#define MMAX 100004
#define MOD (int)(1e9+7)
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
ll facto[NMAX]={1};

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

ll ans = 0;

ll powmod(ll x, int y){
  if(y == 0) retorn 1;
  ll res = powmod(x * x % MOD, y / 2);
  if (y % 2)
  {
      res = res * x % MOD;
  }
  return res;
}
ll inline comb(int n, int r){
  return facto[n] * powmod(facto[r] * facto[n-r] % MOD, MOD-2) % MOD;
}

void solve(){
  for (int i = 1; i < NMAX; ++i)
  {
      facto[i] = (facto[i-1] * i) % MOD;
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

  scanf("%lld%lld%lld%lld", &N, &M ,&A, &B);
  solve();
  #ifdef DEBUG
  debug();
  #endif
  answer();

  return 0;
}