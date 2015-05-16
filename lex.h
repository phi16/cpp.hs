template <class T, class U> auto listify(const Seq<T,U> &s) -> decltype(listifyI(s,Null())){
  return listifyI(s,Null());
}

template <class T, class U, class V> auto listifyI(const Seq<T,U> &s, const V &v) -> decltype(listifyI(s.t,listifyI(s.u,v))){
  return listifyI(s.t,listifyI(s.u,v));
}
template <class T, class V> auto listifyI(const Seq<T,Null> &s, const V &v) -> decltype(listifyI(s.t,v)){
  return listifyI(s.t,v);
}
template <class T, class V> auto listifyI(const Seq<Null,T> &s, const V &v) -> decltype(listifyI(s.u,v)){
  return listifyI(s.u,v);
}
template <class T, class V> Seq<T,V> listifyI(const T &t, const V &v){
  return Seq<T,V>(t,v);
}
Null listifyI(const Decrease &,const Null &v){
  return v;
}


template <class T, class U> auto tokenize(const Seq<T,U> &s) -> Seq<T,decltype(tokenize(s.u))>{
  return Seq<T,decltype(tokenize(s.u))>(s.t,tokenize(s.u));
}
template <class T> auto tokenize(const Seq<Decrease,Seq<Greater,T>> &s) -> Seq<Lambda,decltype(tokenize(s.u.u))>{
  return Seq<Lambda,decltype(tokenize(s.u.u))>(Lambda(),tokenize(s.u.u));
}
template <class T> auto tokenize(const Seq<Plus,Seq<Plus,T>> &s) -> Seq<Append,decltype(tokenize(s.u.u))>{
  return Seq<Append,decltype(tokenize(s.u.u))>(Append(),tokenize(s.u.u));
}
template <class T> auto tokenize(const Seq<Increase,Seq<Plus,T>> &s) -> Seq<Append,decltype(tokenize(s.u.u))>{
  return Seq<Append,decltype(tokenize(s.u.u))>(Append(),tokenize(s.u.u));
}
template <class T> auto tokenize(const Seq<Multiply,Seq<Multiply,T>> &s) -> Seq<Power,decltype(tokenize(s.u.u))>{
  return Seq<Power,decltype(tokenize(s.u.u))>(Power(),tokenize(s.u.u));
}
template <class T> auto tokenize(const Seq<Void,T> &s) -> decltype(tokenize(s.u)){
  return tokenize(s.u);
}
template <class T> T tokenize(const T &t){
  return t;
}
