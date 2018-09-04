Use like this.
```C++
#include <functional>
#include <tuple>
#include <iostream>
#include "PipeFunction.hpp"

int main()
{
	PipeFunction<int,int> print_out( [](int a) { printf("%d\n", a); return a; } );
	
	PipeFunction<int,int,int> mul( [](int a, int b) { return a * b; } );

	PipeFunction<int,std::tuple<int,int> > add(
		[](std::tuple<int, int> t){
			return std::get<0>(t) + std::get<1>(t); }
	);

	std::tuple<int, int> x = std::make_tuple(3, 5);

	int y = mul(2)(3);	//OK
	PipeFunction<int,int> mul_2 = mul(2);   //OK
	y | print_out;  //OK
	x | add | print_out | mul_2 | print_out;    //OK
	//x | add | print_out | mul(2) | print_out;	//NG...
	while (1) {}

	return 0;
}

```