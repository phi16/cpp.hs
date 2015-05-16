#include"cpp.hs"

int main(){
  //std::cout << hs[map_(x --> length x) $_ _["test"_,"ta","asd"]] << std::endl;
  std::cout << hs[filter_(x --> x /= 0) [1_,3,0,4,2,5,0,0,0,7]] << std::endl;
  return 0;
}
