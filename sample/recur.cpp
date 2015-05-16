#include"cpp.hs"

int main(){
  // Does not work
  std::cout << hs[
    let
        g f x = if_ x == 1
          then  1 
          else_ x * f_(x-1) 
    in fix g $ 1
  ] << std::endl;
  return 0;
}
