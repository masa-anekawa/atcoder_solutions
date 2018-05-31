#include <iostream>
#include <set>
using namespace std;

int N;
set<int> ans{2,5,63};
void answer(){
  auto itr = ans.begin();
  for(; itr != --ans.end(); ++itr){
    printf("%d ", *itr);
  }
  printf("%d\n", *itr);
}
int main(){
  cin >> N;
  while(N > ans.size()){
    cout << "add something\n";
  }
  answer();
  return 0;
}