#include<iostream>
#include<typeinfo>
#include<cxxabi.h>

template <class T> void demangle(T t){
  int s;
  std::cout << abi::__cxa_demangle(typeid(t).name(),0,0,&s) << std::endl;
}

template <class T> auto unwrap(const T &t){
  return t;
}
auto unwrap(const Num &t){
  return t.x;
}
auto unwrap(const String &t){
  return t.str;
}
template <class T> auto unwrap(const List<T> &t){
  std::vector<decltype(unwrap(std::declval<T>()))> v;
  for(auto e : t.v)v.push_back(unwrap(e));
  std::reverse(v.begin(),v.end());
  return v;
}
template <class T> auto unwrap(const Value<T> &t){
  return unwrap(t.t);
}


struct Hs{
  /*template <class T> auto operator[](const T &t) -> decltype(unwrap(eval(desugar(parse(tokenize(listify(t))))))) {
    auto e = eval(desugar(parse(tokenize(listify(t)))));
    return unwrap(e);
  }*/
  template <class T> int operator[](const T &t){
    auto e = eval(desugar(parse(tokenize(listify(t)))));
    demangle(e);
    return 0;
  }
}hs; 
