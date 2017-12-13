#define SORT(v) sort(v.begin(), v.end())
#include "iostream"
#include "map"
#include "vector"
#include "cstdlib"
#include <algorithm>
#include <numeric>


#define NMAX 100005
#define MMAX 200

using namespace std;

int N,x;
int lower[NMAX], upper[NMAX];

static const int di[] = {-1, 0, 1, -1, 1, -1, 0, 1};
static const int dj[] = {-1, -1, -1, 0, 0, 1, 1, 1};

int ans = 0;

void solve(){
  vector<int> v(2*N-1);
  iota(v.begin(), v.end(), 1);       // v に 1, 2, ... N を設定
  do {
      std::vector<int> pyr(2*N-1);
      for (int i = 0; i < 2*N-1; ++i)
      {
          pyr[i] = v[i];
          cout << v[i] << " ";
      }
      cout << endl;
      for (int i = N-1; i > 0; --i)
      {
          std::vector<int> tmp(2*i-1);

          for (int j = 0; j < 2*i-1; ++j)
          {
              std::vector<int> med(3);
              med[0]=pyr[j];
              med[1]=pyr[j+1];
              med[2]=pyr[j+2];
              sort(med.begin(), med.end());
              tmp[j] = med[1];
              // cout << med[1] << " ";
              med.clear();
          }
          // cout << endl;
          pyr = tmp;
      }
      if (pyr[0] == x)
      {
          cout << "Yes" <<endl;
          for(auto x : v) cout << x << "\n";
          return;
      }
  } while( next_permutation(v.begin(), v.end()) );     // 次の順列を生成
  cout << "No" << endl;
}

int main(int argc, char const *argv[])
{
  ios::sync_with_stdio(false);

  cin >> N >> x;
  solve();

  return 0;
}