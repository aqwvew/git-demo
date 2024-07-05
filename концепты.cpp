#include <iostream>
#include <concepts>
#include <string>
using namespace std;
template <typename T>
class Reg {
public:
	Reg(T _value) {
		value = _value;
	}
	void display() {
		cout << "value:" << value << endl;
	}
private:
	T value;
};



template <std::integral T>
class Reg<T> {
public:
	Reg(T _value) {
		value = _value;

	}
	T display(T a, T b, T c) {
		cout << "compos:" << value << endl;
		return a * b * c;
	}
private:
	T value;
};
	
	
	
	template <std::floating_point T>
	class Reg<T> {
	public:
		Reg(T _value) {
			value = _value;

		}
		T display(T a, T b, T c) {
			cout << "sum:" << value << endl;
			return a + b + c;
		}
private:
	T value;
};
	int main()
	{
		Reg<int> reg(10);
		Reg<float> reg2(3.14);
		Reg<string> reg3("concepts");
		auto a1 = reg.display(1, 1, 1);
		auto a2 = reg2.display(2.1, 2.1, 2.1);
		reg3.display();
		cout << "a1=" << a1 << endl;
		cout << "a2=" << a2 << endl;
	};
	