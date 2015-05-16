/*
Expr   ::= Expr1 | Expr $ Expr1
Expr1  ::= Expr2 | Expr1 >>= Expr2 | Expr1 >> Expr2
Expr2  ::= Expr3 | Expr2 || Expr3
Expr3  ::= Expr4 | Expr3 && Expr4
Expr4  ::= Expr5 | Expr4 < Expr5 | Expr4 > Expr5 | Expr4 <= Expr5 | Expr4 >= Expr5 | Expr4 == Expr5 | Expr4 /= Expr5
Expr5  ::= Expr6 | Expr5 ++ Expr6 | Expr5 | Expr6
Expr6  ::= Expr7 | Expr6 + Expr7 | Expr6 - Expr7
Expr7  ::= Expr8 | Expr7 * Expr8 | Expr7 / Expr8
Expr8  ::= Expr9 | Expr8 ^ Expr9 | Expr8 ** Expr9
Expr9  ::= let Decl in Expr | if Expr then Expr else Expr | Name --> Expr | Apply
Apply  ::= Factor | Apply Factor
Factor ::= Value | (Expr) | () | [] | [Num__] | [Expr(,Expr)*]
Decl   ::= (Name)+ = Expr
Value  ::= <primitive>
*/
template <class T, class U> struct Pair{
  T t;
  U u;
  Pair(const T &t, const U &u):t(t),u(u){}
};
template <class T, class U> Pair<T,U> ret(const T &t, const U &u){
  return Pair<T,U>(t,u);
}

template <class O, class T, class U> struct Ope{
  O o;
  T t;
  U u;
  Ope(const O &o, const T &t, const U &u):o(o),t(t),u(u){}
};
template <class O, class T, class U> Ope<O,T,U> ope(const O &o, const T &t, const U &u){
  return Ope<O,T,U>(o,t,u);
}
template <class D, class E> struct LetIn{
  D d;
  E e;
  LetIn(const D &d, const E &e):d(d),e(e){}
};
template <class D, class E> LetIn<D,E> letin(const D &d, const E &e){
  return LetIn<D,E>(d,e);
}
template <class I, class T, class E> struct IfTE{
  I i;
  T t;
  E e;
  IfTE(const I &i, const T &t, const E &e):i(i),t(t),e(e){}
};
template <class I, class T, class E> IfTE<I,T,E> ifte(const I &i, const T &t, const E &e){
  return IfTE<I,T,E>(i,t,e);
}
template <int N, class E> struct LambdaA{
  E e;
  LambdaA(const E &e):e(e){}
};
struct Inf{
  int n;
  Inf(int n):n(n){}
};
template <int N> struct Lam{
  template <class E> LambdaA<N,E> bda(const E &e){
    return LambdaA<N,E>(e);
  }
};
template <class O> struct Ret{
  template <class A, class B, class S> Pair<Ope<O,A,B>,S> operator()(const A &a, const Pair<B,S> &t){
    return Pair<Ope<O,A,B>,S>(ope(O(),a,t.t),t.u);
  }
};

template <class T> auto force(const Pair<T,Null> &t){
  return t.t;
}
template <class T> auto parse(const T &t) {
  return leftRec(force(expr(t)));
}

template <class T> auto expr(const T &t) { 
  return expr_i(expr1(t));
}
template <class R, class S> auto expr_i(const Pair<R,Seq<Apply,S>> &t) {
  return Ret<Apply>()(t.t, expr(t.u.u));
}
template <class R, class S> auto expr_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr1(const T &t) { 
  return expr1_i(expr2(t));
}
template <class R, class S> auto expr1_i(const Pair<R,Seq<Bind,S>> &t) {
  return Ret<Bind>()(t.t, expr1(t.u.u));
}
template <class R, class S> auto expr1_i(const Pair<R,Seq<Sequencial,S>> &t) {
  return Ret<Sequencial>()(t.t, expr1(t.u.u));
}
template <class R, class S> auto expr1_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr2(const T &t) { 
  return expr2_i(expr3(t));
}
template <class R, class S> auto expr2_i(const Pair<R,Seq<Or,S>> &t) {
  return Ret<Or>()(t.t, expr2(t.u.u));
}
template <class R, class S> auto expr2_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr3(const T &t) { 
  return expr3_i(expr4(t));
}
template <class R, class S> auto expr3_i(const Pair<R,Seq<And,S>> &t) {
  return Ret<And>()(t.t, expr3(t.u.u));
}
template <class R, class S> auto expr3_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr4(const T &t) { 
  return expr4_i(expr5(t));
}
template <class R, class S> auto expr4_i(const Pair<R,Seq<Less,S>> &t) {
  return Ret<Less>()(t.t, expr4(t.u.u));
}
template <class R, class S> auto expr4_i(const Pair<R,Seq<Greater,S>> &t) {
  return Ret<Greater>()(t.t, expr4(t.u.u));
}
template <class R, class S> auto expr4_i(const Pair<R,Seq<LessEq,S>> &t) {
  return Ret<LessEq>()(t.t, expr4(t.u.u));
}
template <class R, class S> auto expr4_i(const Pair<R,Seq<GreaterEq,S>> &t) {
  return Ret<GreaterEq>()(t.t, expr4(t.u.u));
}
template <class R, class S> auto expr4_i(const Pair<R,Seq<Equal,S>> &t) {
  return Ret<Equal>()(t.t, expr4(t.u.u));
}
template <class R, class S> auto expr4_i(const Pair<R,Seq<Neq,S>> &t) {
  return Ret<Neq>()(t.t, expr4(t.u.u));
}
template <class R, class S> auto expr4_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr5(const T &t) { 
  return expr5_i(expr6(t));
}
template <class R, class S> auto expr5_i(const Pair<R,Seq<Append,S>> &t) {
  return Ret<Append>()(t.t, expr5(t.u.u));
}
template <class R, class S> auto expr5_i(const Pair<R,Seq<Cons,S>> &t) {
  return Ret<Cons>()(t.t, expr5(t.u.u));
}
template <class R, class S> auto expr5_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr6(const T &t) { 
  return expr6_i(expr7(t));
}
template <class R, class S> auto expr6_i(const Pair<R,Seq<Plus,S>> &t) {
  return Ret<Plus>()(t.t, expr6(t.u.u));
}
template <class R, class S> auto expr6_i(const Pair<R,Seq<Minus,S>> &t) {
  return Ret<Minus>()(t.t, expr6(t.u.u));
}
template <class R, class S> auto expr6_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr7(const T &t) { 
  return expr7_i(expr8(t));
}
template <class R, class S> auto expr7_i(const Pair<R,Seq<Multiply,S>> &t) {
  return Ret<Multiply>()(t.t, expr7(t.u.u));
}
template <class R, class S> auto expr7_i(const Pair<R,Seq<Divide,S>> &t) {
  return Ret<Divide>()(t.t, expr7(t.u.u));
}
template <class R, class S> auto expr7_i(const Pair<R,S> &t) {
  return t;
}

template <class T> auto expr8(const T &t) { 
  return expr8_i(expr9(t));
}
template <class R, class S> auto expr8_i(const Pair<R,Seq<Power,S>> &t) {
  return Ret<Power>()(t.t, expr8(t.u.u));
}
template <class R, class S> auto expr8_i(const Pair<R,S> &t) {
  return t;
}

template <class S> auto expr9(const Seq<Let,S> &t) {
  return expr9_let(decl(t.u));
}
template <class R, class S> auto expr9_let(const Pair<R,Seq<In,S>> &t) {
  return expr9_in(t.t,expr(t.u.u));
}
template <class D, class E, class S> auto expr9_in(const D &d, const Pair<E,S> &t) {
  return ret(LetIn<D,E>(d,t.t),t.u);
}
template <class S> auto expr9(const Seq<If,S> &t) {
  return expr9_if(expr(t.u));
}
template <class I, class S> auto expr9_if(const Pair<I,Seq<Then,S>> &t) {
  return expr9_then(t.t,expr(t.u.u));
}
template <class I, class T, class S> auto expr9_then(const I &i, const Pair<T,Seq<Else,S>> &t) {
  return expr9_else(i,t.t,expr(t.u.u));
}
template <class I, class T, class E, class S> auto expr9_else(const I &i, const T &t, const Pair<E,S> &e) { 
  return ret(IfTE<I,T,E>(i,t,e.t),e.u);
}
template <int N, class S> auto expr9(const Seq<Variable<N>,Seq<Lambda,S>> &t) {
  return expr9_lambda(t.t,expr(t.u.u));
}
template <int N, class E, class S> auto expr9_lambda(const Variable<N> &n, const Pair<E,S> &t) {
  return ret(LambdaA<N,E>(t.t),t.u);
}
template <class T> auto expr9(const T &t) {
  return applyP(t);
}

template <class T> auto applyP(const T &t) {
  return apply_i(factor(t));
}
template <class R, int N, class S> auto apply_i(const Pair<R,Seq<Variable<N>, S>> &t) {
  return Ret<ApplyP>()(t.t,applyP(t.u));
}
template <class R, class V, class S> auto apply_i(const Pair<R,Seq<Value<V>,S>> &t) {
  return Ret<ApplyP>()(t.t,applyP(t.u));
}
template <class R, class S> auto apply_i(const Pair<R,Seq<Open,S>> &t) {
  return Ret<ApplyP>()(t.t,applyP(t.u));
}
template <class R, class S> auto apply_i(const Pair<R,Seq<Bra,S>> &t) {
  return Ret<ApplyP>()(t.t,applyP(t.u));
}
template <class R, class S> auto apply_i(const Pair<R,S> &t) {
  return t;
}

template <class T, class S> auto factor(const Seq<Value<T>,S> &t) {
  return ret(t.t,t.u);
}
template <int N, class S> auto factor(const Seq<Variable<N>,S> &t) {
  return ret(t.t,t.u);
}
template <class S> auto factor(const Seq<Open,S> &t) {
  return factor_i(expr(t.u));
}
template <class S> auto factor(const Seq<Open,Seq<Close,S>> &t) {
  return ret(Unit(),t.u.u);
}
template <class E, class S> auto factor_i(const Pair<E,Seq<Close,S>> &t) {
  return ret(t.t,t.u.u);
}
template <class S> auto factor(const Seq<Bra,Seq<Num,Seq<Infinite,Seq<Ket,S>>>> &t){
  return ret(Inf(t.u.t.x),t.u.u.u.u);
}
template <class S> auto factor(const Seq<Bra,S> &t){
  return factor_b(expr(t.u));
}
template <class S> auto factor(const Seq<Bra,Seq<Ket,S>> &t){
  return ret(Nil(),t.u.u);
}
template <class R, class S> auto factor_b(const Pair<R,Seq<Ket,S>> &t){
  return ret(ope(Cons(),t.t,Nil()),t.u.u);
}
template <class R, class S> auto factor_b(const Pair<R,Seq<Comma,S>> &t){
  return Ret<Cons>()(t.t,factor_b(expr(t.u.u)));
}

template <int N, class T> struct NumList{
  T t;
  NumList(const T &t):t(t){}
};
template <int N, class S> auto decl(const Seq<Variable<N>,S> &t) {
  return decl_i(NumList<N,Null>(Null()),t.u);
}
template <int M, class T, class S> auto decl_i(const T &a, const Seq<Variable<M>,S> &t) {
  return decl_i(NumList<M,T>(a),t.u);
}
template <class T, class S> auto decl_i(const T &a, const Seq<Define,S> &t) {
  return Ret<Define>()(a,expr(t.u));
}


template <class T> auto leftRec(const T &t){
  return t;
}
template <class O, class T, class U> auto leftRec(const Ope<O,T,U> &t){
  return ope(t.o,leftRec(t.t),leftRec(t.u));
}
template <class D, class E> auto leftRec(const LetIn<D,E> &t){
  return letin(leftRec(t.d),leftRec(t.e));
}
template <class I, class T, class E> auto leftRec(const IfTE<I,T,E> &t){
  return ifte(leftRec(t.i),leftRec(t.t),leftRec(t.e));
}
template <int N, class E> auto leftRec(const LambdaA<N,E> &t){
  return Lam<N>().bda(leftRec(t.e));
}
template <class T, class U, class V> auto leftRec(const Ope<Bind,T,Ope<Bind,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}
template <class T, class U, class V> auto leftRec(const Ope<Sequencial,T,Ope<Sequencial,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}
template <class T, class U, class V> auto leftRec(const Ope<Plus,T,Ope<Plus,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}
template <class T, class U, class V> auto leftRec(const Ope<Minus,T,Ope<Minus,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}
template <class T, class U, class V> auto leftRec(const Ope<Multiply,T,Ope<Multiply,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}
template <class T, class U, class V> auto leftRec(const Ope<Divide,T,Ope<Divide,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}
template <class T, class U, class V> auto leftRec(const Ope<ApplyP,T,Ope<ApplyP,U,V>> &t){
  return leftApply(t.o,leftRec(t.t),t.u);
}

template <class O, class T, class U, class V> auto leftApply(const O &o, const T &t, const Ope<O,U,V> &v){
  return leftApply(o,ope(o,t,leftRec(v.t)),v.u);
}
template <class O, class T, class U> auto leftApply(const O &o, const T &t, const U &u){
  return ope(o,t,leftRec(u));
}
