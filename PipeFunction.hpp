#pragma once

#include <functional>

template<typename T, typename FirstArg, typename... Args>
class PipeFunction
{
private:
	std::function<T(FirstArg, Args... )> func;
public:
	PipeFunction()
		:func( []{} ) {}

	PipeFunction(std::function<T(FirstArg, Args...)> func_in)
		:func(func_in) {}

	T operator ()(FirstArg arg, Args... ex_args) {
		return func(arg, ex_args...);
	}

	PipeFunction<T,FirstArg> operator ()(Args... ex_args){
		std::function<T(FirstArg)>fn = [=](FirstArg arg) { return func(arg, ex_args...); };
		PipeFunction<T,FirstArg> p_fn(fn);
		return p_fn;
	}

	PipeFunction<T,FirstArg, Args...> operator = (PipeFunction p_func) {
		PipeFunction fn(
			[](FirstArg arg, Args... args) { return p_func(arg, args...); }
		);
		return fn;
	}
};

template<typename T, typename FirstArg, typename... Args>
T operator |(const FirstArg& t, PipeFunction<T,FirstArg, Args... > func){ return func(t); }
