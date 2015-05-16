#include<iostream>
#include<functional>
#include<vector>

template <int N, class D, class E> auto replace(const D &d, const E &e){
  return e;
}
template <int N, class D, class O, class T, class U> auto replace(const D &d, const Ope<O,T,U> &e){
  return ope(e.o,replace<N>(d,e.t),replace<N>(d,e.u));
}
template <int N, class D, int M, class S, class E> auto replace(const D &d, const LetIn<Ope<Define,NumList<M,Null>,S>,E> &e){
  return letin(ope(Define(),e.d.t,replace<N>(d,e.d.u)),replace<N>(d,e.e));
}
template <int N, class D, class S, class E> auto replace(const D &d, const LetIn<Ope<Define,NumList<N,Null>,S>,E> &e){
  return e; //shadowing
}
template <int N, class D, class I, class T, class E> auto replace(const D &d, const IfTE<I,T,E> &t){
  return ifte(replace<N>(d,t.i),replace<N>(d,t.t),replace<N>(d,t.e));
}
template <int N, class D, class E> auto replace(const D &d, const LambdaA<N,E> &e){
  return e; //shadowing
}
template <int N, class D, int M, class E> auto replace(const D &d, const LambdaA<M,E> &e, typename std::enable_if<N != M>::type* = nullptr){
  return Lam<M>().bda(replace<N>(d,e.e));
}
template <int N, class D> auto replace(const D &d, const Variable<N> &v){
  return d;
}

#define OPE(e,ope) \
  template <class T, class U> auto eval(const Ope<e,T,U> &t, const decltype(eval(t.t) ope eval(t.u))* = nullptr){ \
    return eval(t.t) ope eval(t.u); \
  }
OPE(Plus,+);
OPE(Minus,-);
OPE(Multiply,*);
OPE(Divide,/);
OPE(Less,<);
OPE(Greater,>);
OPE(LessEq,<=);
OPE(GreaterEq,>=);
OPE(Equal,==);
OPE(Neq,!=);
OPE(And,&&);
OPE(Or,||);
OPE(Power,^);
OPE(Cons, |);
#undef OPE
template <class T> auto eval(const Value<Function<T>> &t, const decltype(t.t.x.value())* = nullptr){
  return eval(t.t.x.value());
}
template <class T> auto eval(const Value<T> &t){
  return t.t;
}
template <class T> auto eval(const T &t){
//  static_assert(false,"No matching function");
  return t;
}
template <int N> auto eval(const Variable<N> &t){
//  static_assert(false,"Not in scope");
  return t;
}
template <class T, class U> auto eval(const Ope<Append,T,U> &t){
  return append(eval(t.t),eval(t.u));
}
auto append(const String &t, const String &u){
  return String(t.str+u.str);
}
template <class T> auto append(const List<T> &t, const List<T> &u){
  List<T> l = t;
  l.v.insert(l.v.begin(),u.v.begin(),u.v.end());
  return l;
}
template <int N, class D, class E> auto eval(const LetIn<Ope<Define,NumList<N,Null>,D>,E> &t){
  return eval(replace<N>(t.d.u,t.e));
}
template <class A, class B> auto eval(const Ope<Apply,A,B> &t){
  return app(eval(t.t),t.u);
}
template <int N, class E> auto eval(const LambdaA<N,E> &f){
  return f;
}
template <int N, class E, class B> auto app(const LambdaA<N,E> &f, const B &t){
  return eval(replace<N>(t,f.e));
}
template <class F, class X> auto app(const Function<F> &f, const X &x){
  return f.x(eval(x));
}
template <class T, class X> auto app(const T &t, const X &x){
  return ope(Apply(),t,x);
}
template <class I, class T, class E> auto eval(const IfTE<I,T,E> &t){
  return cond(eval(t.i),t.t,t.e);
}
auto eval(const Inf &t){
  std::vector<Num> l;
  for(int i=100;i>-1;i--)l.push_back(t.n + i);
  return List<Num>(l);
}
template <class T, class U> auto cond(const Bool &i, const T &t, const U &u, const decltype(i.x?eval(t):eval(u))* = nullptr){
  return i.x?eval(t):eval(u);
}
template <class I, class T, class E> auto cond(const I &i, const T &t, const E &e){
  return ifte(i,t,e);
}


template <class T, class U> auto eval(const Ope<Sequencial,T,U> &t) -> decltype(eval(t.u)) {
  eval(t.t);
  return eval(t.u);
}
template <class T, class U> auto eval(const Ope<Bind,T,U> &t){
  return eval(ope(Apply(),t.u,eval(t.t)));
}

