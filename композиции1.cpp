// H:\___Tst\VS\VariadTemplTests\Compose\LambdaAndFuncObj\LambdaAndFuncObj\LambdaView.cpp
//--------------------------------------------------------------------------------------------
// 1. C помощью лямбда-выражений строим композицию h=f*g функций f и g по правилу h(x)=f(g(x)) 
// 2. Строим композицию с помощью функциональных обектов
// 3. Комбинации, в которых смешиваются функциональные обекты и лямбда выражения
//--------------------------------------------------------------------------------------------

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <iterator>
#include <type_traits> 
#include <vector>
#include <numbers>
#include <iomanip>


#define _USE_MATH_DEFINES // for C++  
//#include <cmath>  
#include <math.h>  

using namespace std;
using namespace std::numbers;

// Композиция h(x) = f(g(x))
template <typename _F, typename _G, typename _G1, typename _G2, typename _G3>
	class AppFtoG
{
public:
	AppFtoG(_F _f, _G _g, _G1 _g1, _G2 _g2, _G3 _g3) : f(_f), g(_g), g1(_g1), g2(_g2), g3(_g3) { }

	template <typename T>
	auto operator () (T x, T y, T z) { return f(x, g(g1(y), g2(z)), g3(y)); }

private:
	_F f;
	_G g;
	_G1 g1;
	_G2 g2;
	_G3 g3;
};
// + сделать еще выриант адаптируемого функционального обекта

class HisFxGx1
{
public:
	
	template <typename _F, typename _G, typename _G1, typename _G2, typename _G3>
	auto operator () (_F _f, _G _g, _G1 _g1, _G2 _g2, _G3 _g3) { return AppFtoG<_F, _G, _G1, _G2, _G3>(_f, _g, _g1, _g2, _g3); }

};

struct F0_f
{
	template <typename T>
	T operator () (T x, T y, T z) const { return x + y + z; }
};
struct F0_g
{
	template <typename T>
	T operator () (T y, T z) const { return y*z; }
};
struct F0_g1
{
	template <typename T>
	T operator () (T y) const { return 2*y; }
};

struct F0_g2
{
	template <typename T>
	T operator () (T z) const { return z; }
};

struct F0_g3
{
	template <typename T>
	T operator () (T y) const { return 3*y; }
};

int main() {
	




	{//--------------------------------------------------------------------------------------------
	 // 1. C помощью лямбда-выражений строим композицию h=f*g функций f и g по правилу h(x)=f(g(x)) 
	 // 2. Строим композицию с помощью функциональных обектов
	 // 3. Комбинации, в которых смешиваются функциональные обекты и лямбда выражения
	 //--------------------------------------------------------------------------------------------

		////==========================================================================================
		//// 1. composeHisFxGx строит композицию h=f*g функций f и g по правилу h(x)=f(g(x))
		////==========================================================================================
		
		auto composeHisFxGx1 = [](auto _f, auto _g, auto _g1, auto _g2, auto _g3)->auto
			{ return [_f, _g, _g1, _g2, _g3](auto x, auto y, auto z) { return _f(x, _g(_g1(y), _g2(z)), _g3(y)); };
			};


		cout << typeid(composeHisFxGx1).name() << endl;

		auto f = [](auto x, auto y, auto z) { return x+y+z; };
		auto g = [](auto y, auto z) { return y*z; };
		auto g1 = [](auto y) { return 2*y; };
		 auto g2 = [](auto z) { return z; };
		 auto g3 = [](auto y) { return 3*y; };
		
		//// 1.1. Строим композицию лямбда-функций fsin и fsquare
		auto hd = composeHisFxGx1(f, g, g1, g2, g3); 
		

		
		////// Результатом композиции тоже будет универсальная лямбда-функция hi
		auto hi = composeHisFxGx1(f, g, F0_g1(), g2, g3);

		////// 1.2.1. Приеняем hi к значению типа int. В результате получаем значение типа int.
		cout << "a1(1, 2, 3)=" << hi(1.0 , 1.0 , 1.0) << endl;   // hi(x) = (x+x+x)^2
		auto a = hi(1, 1, 1);
		cout << "typeid(a1).name()=" << typeid(hi(1, 1, 1)).name() << endl;   // hi(x) = (x+x+x)^2

		//// 1.2.2. Приеняем hi к значению типа double. В результате получаем значение типа double.
		cout << "a2=" << hi(1.0, 1.0, 1.0) << endl;   // hi(x) = (x+x+x)^2

		cout << "typeid(a2).name()=" << typeid(hi(1.0, 1.0, 1.0)).name() << endl;   // hi(x) = (x+x+x)^2

		//==========================================================================================
		// 2. Строим композицию с помощью функциональных обектов
		//==========================================================================================
		
		HisFxGx1 xHisFxGx;   // xHisFxGx - функциональный объект, operator () которого создаёт другой
		// функциональный объект, представляющий композицию функций

	  // 2.1. Строим композицию лямбда-функций fsin и fsquare, т.е. применяем наш композитор xHisFxGx
	  //      к двум лямбда-функциям fsin и fsquare, и получаем функциональный объект, представляющий 
	  //      композицию функций fsin и fsquare
		auto hdx = xHisFxGx(F0_f(),F0_g(),F0_g1(),F0_g2(), F0_g3());
		auto b = hdx(1.0, 1.0, 1.0);
		cout << "b=" << b;

		

		return 0;
	}
}; 