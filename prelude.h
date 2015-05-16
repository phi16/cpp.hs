#include<iostream>

template <class X> struct IO{
  /*
  X io(){
    //????
  }
  */
};

template <class T> Seq<Value<T>,Null> makeSeq(const T &t){
  return Seq<Value<T>,Null>(Value<T>(t));
}

struct PutStrLn{
  Unit operator ()(const String &s) const {
    std::cout << s.str << std::endl;
    return Unit();
  }
};

struct GetLine{
  String value() const {
    std::string str;
    std::getline(std::cin, str);
    return String(str);
  }
};

struct Print{
  template <class T> Unit operator ()(const T &t) const {
    std::cout << t << std::endl;
    return Unit();
  }
};

struct Id{
  template <class T> T operator ()(const T &t) const {
    return t;
  }
};

struct Head{
  template <class T> T operator()(const List<T> &l) const {
    return *(l.v.end()-1);
  }
};

struct Tail{
  template <class T> List<T> operator()(const List<T> &l) const {
    List<T> t = l;
    t.v.pop_back();
    return t;
  }
  String operator()(const String &l) const {
    return String(l.str.substr(1,l.str.size()-1));
  }
};

struct IsNull{
  template <class T> Bool operator()(const List<T> &l) const {
    return Bool(l.v.empty());
  }
  Bool operator()(const String &l) const {
    return Bool(l.str.empty());
  }
};

struct Length{
  template <class T> Num operator()(const List<T> &l) const {
    return Num(l.v.size());
  }
  Num operator()(const String &l) const {
    return Num(l.str.size());
  }
};

struct TakeI{
  Num i;
  TakeI(const Num &i):i(i){}
  template <class T> List<T> operator ()(const List<T> &l) const {
    auto it = l.v.end(); 
    std::advance(it,-(int)i.x);
    std::vector<T> t(it,l.v.end());
    return List<T>(t);
  }
  String operator ()(const String &l) const {
    return String(l.str.substr(0,(int)i.x));
  }
};
struct Take{
  Function<TakeI> operator ()(const Num &i) const {
    return Function<TakeI>(TakeI(i));
  }
};

template <class F, class T, class X> struct MapII{
  F f;
  List<T> t;
  MapII(const F &f, const List<T> &t):f(f),t(t){}
  List<X> operator ()() const {
    std::vector<X> v;
    for(auto e : t.v)v.push_back(app(f,e));
    return List<X>(v);
  }
};
template <class F> struct MapI{
  F f;
  MapI(const F &f):f(f){}
  template <class T> auto operator ()(const List<T> &l) const -> List<decltype(app(f,std::declval<T>()))> {
    return MapII<F,T,decltype(app(f,std::declval<T>()))>(f,l)();
  }
};
struct Map{
  template <class F> Function<MapI<F>> operator ()(const F &f) const {
    return Function<MapI<F>>(MapI<F>(f));
  }
};

template <class F> struct FilterI{
  F f;
  FilterI(const F &f):f(f){}
  template <class T> List<T> operator ()(const List<T> &l) const {
    std::vector<T> v;
    for(auto e : l.v)if(app(f,e).x)v.push_back(e);
    return List<T>(v);
  }
};  
struct Filter{
  template <class F> Function<FilterI<F>> operator ()(const F &f) const {
    return Function<FilterI<F>>(FilterI<F>(f));
  }
};

auto putStrLn_(makeSeq(Function<PutStrLn>{}));
auto getLine(makeSeq(Function<GetLine>{}));
auto print_(makeSeq(Function<Print>{}));
auto return__(makeSeq(Function<Id>{}));
auto id_(makeSeq(Function<Id>{}));
auto head_(makeSeq(Function<Head>{}));
auto tail_(makeSeq(Function<Tail>{}));
auto null_(makeSeq(Function<IsNull>{}));
auto take_(makeSeq(Function<Take>{}));
auto length_(makeSeq(Function<Length>{}));
auto filter_(makeSeq(Function<Filter>{}));
auto map_(makeSeq(Function<Map>{}));

#define putStrLn &putStrLn_&
#define getLine_ &getLine&
#define print &print_&
#define id &id_&
#define head &head_&
#define tail &tail_&
#define null &null_&
#define map &map_&
#define take &take_&
#define length &length_&
#define filter &filter_&
#define return_ &return__

auto True_(makeSeq(Bool(true)));
auto False_(makeSeq(Bool(false)));

#define True &True_
#define False &False_