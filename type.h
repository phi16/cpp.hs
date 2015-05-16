#include<functional>

template <int I> struct Variable{};
Seq<Variable<0>,Null> a(Variable<0>{});
Seq<Variable<1>,Null> b(Variable<1>{});
Seq<Variable<2>,Null> c(Variable<2>{});
Seq<Variable<3>,Null> d(Variable<3>{});
Seq<Variable<4>,Null> e(Variable<4>{});
Seq<Variable<5>,Null> f_(Variable<5>{});
Seq<Variable<6>,Null> g_(Variable<6>{});
Seq<Variable<7>,Null> h_(Variable<7>{});
Seq<Variable<22>,Null> w(Variable<22>{});
Seq<Variable<23>,Null> x(Variable<23>{});
Seq<Variable<24>,Null> y(Variable<24>{});
Seq<Variable<25>,Null> z(Variable<25>{});

template <class X> struct Function{
  X x;
  Function(){}
  Function(const X &x):x(x){}
};
