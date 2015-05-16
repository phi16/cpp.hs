template <class T> auto desugar(const T &t){
  return t;
}
template <class T, class U> auto desugar(const Ope<ApplyP,T,U> &t){
  return ope(Apply(),desugar(t.t),desugar(t.u));
}
template <class O, class T, class U> auto desugar(const Ope<O,T,U> &t){
  return ope(t.o,desugar(t.t),desugar(t.u));
}
template <int N, class D, class E> auto desugar(const LetIn<Ope<Define,NumList<N,Null>,D>,E> &t){
  return letin(t.d,desugar(t.e));
}
template <int N, class S, class D, class E> auto desugar(const LetIn<Ope<Define,NumList<N,S>,D>,E> &t){
  return letin(lambdify(t.d.t,t.d.u),desugar(t.e));
}
template <class I, class T, class E> auto desugar(const IfTE<I,T,E> &t){
  return ifte(desugar(t.i),desugar(t.t),desugar(t.e));
}
template <int N, class E> auto desugar(const LambdaA<N,E> &t){
  return Lam<N>().bda(desugar(t.e));
}
//auto desugar(const Inf &v){
//  letin(ope(Define(),NumList<0,Null>(),ope(Cons(),Value<Int>(Int(v.n)), ope(Apply(),map_, ));
//}

template <int N, class D, class E> auto lambdify(const NumList<N,D> &d, const E &e){
  return lambdify(d.t, Lam<N>().bda(e));
}
template <int N, class E> auto lambdify(const NumList<N,Null> &n, const E &e){
  return ope(Define(),n,desugar(e));
}