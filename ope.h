#include<iostream>
#include<cmath>

Num operator +(const Num &x, const Num &y){
  return Num(x.x+y.x);
}
Num operator -(const Num &x, const Num &y){
  return Num(x.x-y.x);
}
Num operator *(const Num &x, const Num &y){
  return Num(x.x*y.x);
}
Num operator /(const Num &x, const Num &y){
  return Num(x.x/y.x);
}

Bool operator <(const Num &x, const Num &y){
  return Bool(x.x<y.x);
}
Bool operator >(const Num &x, const Num &y){
  return Bool(x.x>y.x);
}
Bool operator <=(const Num &x, const Num &y){
  return Bool(x.x<=y.x);
}
Bool operator >=(const Num &x, const Num &y){
  return Bool(x.x>=y.x);
}

Bool operator <(const Bool &x, const Bool &y){
  return Bool(x.x<y.x);
}
Bool operator >(const Bool &x, const Bool &y){
  return Bool(x.x>y.x);
}
Bool operator <=(const Bool &x, const Bool &y){
  return Bool(x.x<=y.x);
}
Bool operator >=(const Bool &x, const Bool &y){
  return Bool(x.x>=y.x);
}

Bool operator <(const String &x, const String &y){
  return x.str < y.str;
}
Bool operator >(const String &x, const String &y){
  return x.str > y.str;
}
Bool operator <=(const String &x, const String &y){
  return x.str <= y.str;
}
Bool operator >=(const String &x, const String &y){
  return x.str >= y.str;
}

template <class T> Bool operator <(const List<T> &x, const List<T> &y){
  return Bool(x.v<y.v);
}
template <class T> Bool operator >(const List<T> &x, const List<T> &y){
  return Bool(x.v>y.v);
}
template <class T> Bool operator <=(const List<T> &x, const List<T> &y){
  return Bool(x.v<=y.v);
}
template <class T> Bool operator >=(const List<T> &x, const List<T> &y){
  return Bool(x.v>=y.v);
}

Bool operator ==(const Num &x, const Num &y){
  return Bool(std::abs(x.x-y.x)<0.001);
}
Bool operator !=(const Num &x, const Num &y){
  return Bool(!(x == y).x);
}
Bool operator ==(const Bool &x, const Bool &y){
  return x.x == y.x;
}
Bool operator !=(const Bool &x, const Bool &y){
  return x.x != y.x;
}
Bool operator ==(const String &x, const String &y){
  return x.str == y.str;
}
Bool operator !=(const String &x, const String &y){
  return x.str != y.str;
}
template <class T> Bool operator ==(const List<T> &x, const List<T> &y){
  return x.v == y.v;
}
template <class T> Bool operator !=(const List<T> &x, const List<T> &y){
  return x.v != y.v;
}

Bool operator &&(const Bool &x, const Bool &y){
  return x.x && y.x;
}
Bool operator ||(const Bool &x, const Bool &y){
  return x.x || y.x;
}

Num operator ^(const Num &x, const Num &y){
  return std::pow(x.x,y.x);
}

template <class T> List<T> operator |(const T &t, const List<T> &ls){
  List<T> l = ls;
  l.v.push_back(t);
  return l;
}
template <class T> List<T> operator |(const T &t, const Nil &n){
  List<T> l;
  l.v.push_back(t);
  return l;
}

std::ostream& operator <<(std::ostream& os, const Unit &x){
  os << "()" << std::flush;
  return os;
}
std::ostream& operator <<(std::ostream& os, const Bool &x){
  if(x.x)os << "True" << std::flush;
  else os << "False" << std::flush;
  return os;
}
std::ostream& operator <<(std::ostream& os, const Num &x){
  os << x.x << std::flush;
  return os;
}
std::ostream& operator <<(std::ostream& os, const String &x){
  os << "\"" << x.str << "\"" << std::flush;
  return os;
}
template <class T> std::ostream& operator <<(std::ostream& os, const List<T> &x){
  os << "[";
  if(!x.v.empty()){
    for(auto it=x.v.rbegin();it!=x.v.rend();it++){
      os << *it;
      auto jt = it;
      jt++;
      if(jt!=x.v.rend())os << ",";
    }
  }
  os << "]";
  return os;
}
std::ostream& operator <<(std::ostream& os, const Nil &x){
  os << "[]";
  return os;
}
