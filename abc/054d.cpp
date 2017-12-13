#define SORT(v) sort(v.begin(), v.end())
#include "iostream"
#include "map"
#include "vector"
#include <stack>
#include "cstdlib"
#include <algorithm>
#include <cstdarg>
// #include "ane.cpp"

#define INF 5000
#define NMAX 45
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
typedef pair<int, int> P;

int N,M,Ma, Mb, A[NMAX]={}, B[NMAX] = {}, C[NMAX] = {}, dp[NMAX][500][500] = {};

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int ans = 0;

int  solve(int i, int ma, int mb){
  // printf("solve(%d, %d, %d)\n", i, ma, mb);
  if(dp[i][ma][mb]) return dp[i][ma][mb];
  // 解答アルゴリズム
  if (i >= N)
  {
      return INF;
  }
  if ((ma+A[i]) * Mb == (mb+B[i]) * Ma)
  {
      return dp[i][ma][mb] = min(C[i], solve(i+1, ma, mb));
  }

  return dp[i][ma][mb] = min(solve(i+1, ma, mb), solve(i+1, ma+A[i], mb+B[i]) + C[i]);

}
void debug(){
  // デバッグ用出力
}
void answer(){
  // 解答出力
  if(ans >= INF)cout << "-1\n";
  else cout << ans << endl;
}
int main(int argc, char const *argv[])
{
  // 入力の読み込み，番兵法
  ios::sync_with_stdio(false);

  // Fill(dp, INF);

  cin >> N >> Ma >> Mb;
  for (int i = 0; i < N; ++i)
  {
      cin >> A[i] >> B[i] >> C[i];
  }
  ans = solve(0,0,0);
  #ifdef DEBUG
  // debug();
  #endif
  answer();

  return 0;
}