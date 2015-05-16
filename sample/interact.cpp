#include"cpp.hs"

int main(){
  std::vector<double> v{1,2,4,7};
  v = hs[map_(x --> x^2) $ v];
  for(auto i : v)std::cout << "[" << i << "]";
  std::cout << std::endl;
  return 0;
}