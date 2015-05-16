#include"cpp.hs"

main_= getLine >>= x -->
 _(putStrLn $ if_ x == "C++"
                then  "No more C++"
                else_ "Hello, "_+++ x) >>
 _(print $ let f x = 2 * x in f 5) >>
 _(print $ take 10 $ map_(x --> 2*x) [1__]) >>
 _(print $ filter_(x --> x /= 0) [1_,0,8,0,0]) >>
   return_()

-- End Haskell
