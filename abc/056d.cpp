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
#define NMAX 5005
#define MMAX 5005
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

ll N,M,K,A[NMAX],B,C,D,E;
int dp[NMAX][MMAX] = {};

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

ll ans = 0;

void solve(){
  // 解答アルゴリズム
  sort(A, A+N);
  ll sum = 0;
  for (int i = 0; i < N && sum < M; ++i)
  {
      sum += A[i];
  }
  if (sum < M)
  {
      ans = N;
      return;
  }
  ll dup=0;
  for (int i = 0; i < N; ++i)
  {
      sum -= A[i];
      if (i && A[i] == A[i-1])
      {
          dup++;
      }else{
          dup = 0;
      }
      if(sum >= M)ans++;
      else break;
  }
  ans = std::max(0LL, ans-dup);
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

  scanf("%lld%lld", &N,&M);
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