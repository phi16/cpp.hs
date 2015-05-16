#include<string>
#include<vector>
#include<algorithm>

template <class T> struct Value{
  T t;
  Value(const T &t):t(t){}
};

struct Unit{};
struct Bool{
  bool x;
  Bool(bool x):x(x){}
};
struct Num{
  double x;
  Num(double x):x(x){}
};
struct String{
  std::string str;
  String(const char *str):str(str){}
  String(std::string str):str(str){}
};
template <class T> struct List{
  std::vector<T> v;
  List<T>(){}
  List<T>(const std::vector<T> &v):v(v){}
};

struct Plus{};
struct Minus{};
struct Multiply{};
struct Divide{};
struct Power{};
struct Equal{};
struct Neq{}; // /= 
struct And{};
struct Or{};
struct Cons{}; // |
struct Decrease{};
struct Increase{};
struct Sequencial{};
struct Less{};
struct Greater{};
struct LessEq{};
struct GreaterEq{};
struct Lambda{}; // -->
struct Bind{}; // >>=
struct Append{}; // +++
struct Apply{}; // $
struct ApplyP{}; // f x
struct Open{}; // (
struct Close{}; // )
struct Bra{}; // [
struct Ket{}; // ]
struct Define{}; // =
struct Infinite{}; // __
struct Comma{}; // ,
struct Nil{}; // []

struct Null{};

struct Let{};
struct In{};
struct If{};
struct Then{};
struct Else{};

struct True{};
struct False{};

template <class T, class U> struct Seq{
  T t;
  U u;
  Seq(const T &t, const U &u):t(t),u(u){}
  auto operator()() -> Seq<Seq<T,U>,Value<Unit>>{
    return Seq<Seq<T,U>,Value<Unit>>(*this,Value<Unit>(Unit()));
  }
  template <class V> auto operator ()(const V &v) -> Seq<Seq<T,U>,Seq<Seq<Open,V>,Close>>{
    return Seq<Seq<T,U>,Seq<Seq<Open,V>,Close>>(*this,Seq<Seq<Open,V>,Close>(Seq<Open,V>(Open(),v),Close()));
  }
  template <class V> auto operator =(const V &v) -> Seq<Seq<T,U>,Seq<Define,V>>{
    return Seq<Seq<T,U>,Seq<Define,V>>(*this,Seq<Define,V>(Define(),v));
  }
  template <class V> auto operator [](const V &v) -> Seq<Seq<T,U>,Seq<Seq<Bra,V>,Ket>>{
    return Seq<Seq<T,U>,Seq<Seq<Bra,V>,Ket>>(*this,Seq<Seq<Bra,V>,Ket>(Seq<Bra,V>(Bra(),v),Ket()));
  }
};  
template <class T> struct Seq<T,Null>{
  T t;
  Null u;
  Seq(const T &t):t(t){}
  Seq(const T &t, const Null &u):t(t),u(u){}
  auto operator()() -> Seq<Seq<T,Null>,Value<Unit>>{
    return Seq<Seq<T,Null>,Value<Unit>>(*this,Value<Unit>(Unit()));
  }
  template <class V> auto operator ()(const V &v) -> Seq<Seq<T,Null>,Seq<Seq<Open,V>,Close>>{
    return Seq<Seq<T,Null>,Seq<Seq<Open,V>,Close>>(*this,Seq<Seq<Open,V>,Close>(Seq<Open,V>(Open(),v),Close()));
  }
  template <class V> auto operator =(const V &v) -> Seq<Seq<T,Null>,Seq<Define,V>>{
    return Seq<Seq<T,Null>,Seq<Define,V>>(*this,Seq<Define,V>(Define(),v));
  }
  template <class V> auto operator [](const V &v) -> Seq<Seq<T,Null>,Seq<Seq<Bra,V>,Ket>>{
    return Seq<Seq<T,Null>,Seq<Seq<Bra,V>,Ket>>(*this,Seq<Seq<Bra,V>,Ket>(Seq<Bra,V>(Bra(),v),Ket()));
  }
};

template <class T> auto fit(const T &t) -> Value<T>{
  return Value<T>(t);
}
Value<String> fit(const char* str){
  return Value<String>(String(str));
}
Value<Num> fit(int x){
  return Value<Num>(Num(x));
}
Value<Num> fit(double x){
  return Value<Num>(Num(x));
}
template <class T> auto val_l(const List<T> &t){
  return Value<List<T>>(t);
}
template <class T> auto fit(std::vector<T> v) -> Value<List<decltype(fit(std::declval<T>()))>> {
  std::vector<decltype(fit(std::declval<T>()))> r;
  for(auto e : v)r.push_back(fit(e));
  std::reverse(r.begin(),r.end());
  return val_l(List<decltype(fit(std::declval<T>()))>(r));
}

template <class T, class U> Seq<T,U> operator &(const Seq<T,U> &t){
  return t;
}
template <class T, class U, class V, class W> auto operator &(const Seq<T,U> &t, const Seq<V,W> &v) -> Seq<Seq<T,U>,Seq<V,W>>{
  return Seq<Seq<T,U>,Seq<V,W>>(t,v);
}
template <class T, class U, class V> auto operator &(const V &v, const Seq<T,U> &t) -> Seq<decltype(fit(v)),Seq<T,U>>{
  return Seq<decltype(fit(v)),Seq<T,U>>(fit(v),t);
}
template <class T, class U, class V> auto operator &(const Seq<T,U> &t, const V &v) -> Seq<Seq<T,U>,decltype(fit(v))>{
  return Seq<Seq<T,U>,decltype(fit(v))>(t,fit(v));
}
#define DECL_BIOPE(ope, tag) \
  template <class T, class U, class V, class W> auto operator ope(const Seq<T,U> &t, const Seq<V,W> &v) -> Seq<Seq<Seq<T,U>,tag>,Seq<V,W>>{ \
    return Seq<Seq<Seq<T,U>,tag>,Seq<V,W>>(Seq<Seq<T,U>,tag>(t,tag()),v); \
  } \
  template <class T, class U, class V> auto operator ope(const V &v, const Seq<T,U> &t) -> Seq<decltype(fit(v)),Seq<tag,Seq<T,U>>>{ \
    return Seq<decltype(fit(v)),Seq<tag,Seq<T,U>>>(fit(v),Seq<tag,Seq<T,U>>(tag(),t)); \
  } \
  template <class T, class U, class V> auto operator ope(const Seq<T,U> &t, const V &v) -> Seq<Seq<Seq<T,U>,tag>,decltype(fit(v))>{ \
    return Seq<Seq<Seq<T,U>,tag>,decltype(fit(v))>(Seq<Seq<T,U>,tag>(t,tag()),fit(v)); \
  }
DECL_BIOPE(+, Plus)
DECL_BIOPE(-, Minus)
DECL_BIOPE(*, Multiply)
DECL_BIOPE(/, Divide)
DECL_BIOPE(^, Power)
DECL_BIOPE(==, Equal)
DECL_BIOPE(/=, Neq)
DECL_BIOPE(&&, And)
DECL_BIOPE(||, Or)
DECL_BIOPE(<, Less)
DECL_BIOPE(>, Greater)
DECL_BIOPE(<=, LessEq)
DECL_BIOPE(>=, GreaterEq)
DECL_BIOPE(>>, Sequencial)
DECL_BIOPE(>>=, Bind)
DECL_BIOPE(|, Cons)
#define COMMA ,
DECL_BIOPE(COMMA, Comma)
#undef COMMA
#undef DECL_BIOPE
template <class T, class U> auto operator --(const Seq<T,U> &t, int x) -> Seq<Seq<T,U>,Decrease>{ // Lambda or End Haskell
  return Seq<Seq<T,U>,Decrease>(t,Decrease());
}
template <class T, class U> auto operator ++(const Seq<T,U> &t, int x) -> Seq<Seq<T,U>,Increase>{
  return Seq<Seq<T,U>,Increase>(t,Increase());
}
template <class T, class U> auto operator +(const Seq<T,U> &t) -> Seq<Plus,Seq<T,U>>{
  return Seq<Plus,Seq<T,U>>(Plus(),t);
}
template <class T, class U> auto operator -(const Seq<T,U> &t) -> Seq<Minus,Seq<T,U>>{
  return Seq<Minus,Seq<T,U>>(Minus(),t);
}
template <class T, class U> auto operator *(const Seq<T,U> &t) -> Seq<Multiply,Seq<T,U>>{
  return Seq<Multiply,Seq<T,U>>(Multiply(),t);
}

struct Void{
  template <class T, class U> auto operator =(const Seq<T,U> &t) -> Seq<T,U>{
    return t;
  }
  template <class V> auto operator ()(const V &v) -> Seq<Open,Seq<V,Close>>{
    return Seq<Open,Seq<V,Close>>(Open(),Seq<V,Close>(v,Close()));
  }
  template <class V> auto operator [](const V &v) -> Seq<Bra,Seq<V,Ket>>{
    return Seq<Bra,Seq<V,Ket>>(Bra(),Seq<V,Ket>(v,Ket()));
  }
  auto operator [](const int &v) -> Seq<Bra,Seq<Value<Num>,Ket>>{
    return Seq<Bra,Seq<Value<Num>,Ket>>(Bra(),Seq<Value<Num>,Ket>(Value<Num>(Num(v)),Ket()));
  }
  auto operator [](const double &v) -> Seq<Bra,Seq<Value<Num>,Ket>>{
    return Seq<Bra,Seq<Value<Num>,Ket>>(Bra(),Seq<Value<Num>,Ket>(Value<Num>(Num(v)),Ket()));
  }
}_;

Seq<Let,Null> let_(Let{});
Seq<In,Null> in_(In{});
Seq<If,Null> if__(If{});
Seq<Then,Null> then_(Then{});
Seq<Else,Null> else__(Else{});
Seq<Apply,Null> apply(Apply{});

Seq<Value<String>,Null> operator "" _(const char* str,std::size_t){
  return Seq<Value<String>,Null>(Value<String>(String(str)));
}
Seq<Value<Num>,Null> operator "" _(unsigned long long int x){
  return Seq<Value<Num>,Null>(Value<Num>(Num(x)));
}

Seq<Num,Seq<Infinite,Null>> operator "" __(unsigned long long int x){
  return Seq<Num,Seq<Infinite,Null>>(Num(x),Seq<Infinite,Null>(Infinite()));
}
