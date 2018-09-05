Use like this.
```C++
#include <functional>
#include <iostream>
#include <string>
#include <vector>
#include "PipeFunction.hpp"

int main()
{
	PipeFunction<int,int,std::string> print_out(
		[](int a, std::string str) { std::cout << str << ":" << a << std::endl; return a; }
	);
	
	PipeFunction<int,int,int> add( [](int a, int b) { return a + b; } );
	PipeFunction<int,int,int> mul( [](int a, int b) { return a * b; } );

	PipeFunction<int, std::vector<int> >sum(
		[](std::vector<int> vec){
		int sum = 0;
		for (auto i : vec) {
			sum += i;
			}
		return sum;
		}
	);

	PipeFunction<std::vector<int>, std::vector<int>, std::function<bool(int)> >filter(
		[](std::vector<int> vec, std::function<bool(int)> fn){
		std::vector<int> result;
		for (auto i: vec) {
			if (fn(i)) { result.push_back(i); }
		}
		return result;
		}
	);

	std::vector<int>v{ 0,1,2,3,4,5,6,7,8,9 };

	v
	| filter( [](int i) {return i % 2; } )
	| sum
	| print_out("sum")
	| add(3)
	| print_out("add 3")
	| mul(2)
	| print_out("mul 2");

	return 0;
}

```