#include"cpp.hs"

int main(){
  std::cout << hs[let f x =_(x + 1) * x in f 6] << std::endl;
  std::cout << hs[
/* Recursion does not work
    let 
        y_ f_= _(x --> f x_ x) (x --> f x_ x)
      in let
          g f x = if_ x == 1 
            then 1 
            else_ x * f (x-1) 
        in y g 5
*/
        let
          g f x = if_ x == 1
            then  1 
            else_ x * f_(x-1) 
        in g_ (x --> x + 1) $ 1
  ] << std::endl;
  std::cout << hs[let f x = x +++ x in f $ f "a"] << std::endl;
  std::cout << hs[tail $ 1 | _[2_,3,4] +++ _[5]] << std::endl;
  std::cout << hs[take 10 $ _[5__]] << std::endl;
  return 0;
}
