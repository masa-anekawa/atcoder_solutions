#include <iostream>
#include <cstdio>
using namespace std;

int main(){
  int N, Y;
  cin >> N >> Y;
  Y /= 1000;
  int x,y,z;
  for(y = 0; y <= N; ++y){
    int z_9 = 10 * N - Y - 5 * y;
    if(z_9 >= 0 && z_9 % 9 == 0 && z_9 / 9 <= N){
      z = z_9 / 9;
      x = N - y - z;
      if(x < 0 || x > N || 10 * x + 5 * y + z != Y) continue;
      printf("%d %d %d\n", x, y, z);
      return 0;
    }
  }
  cout << "-1 -1 -1\n";
  return 0;
}