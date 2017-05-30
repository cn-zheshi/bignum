#include "bignum.hpp"
#include <iostream>
int main()
{
	std::cout<<1234.56_bignum<<std::endl;
	zheshi::bignum a=28;
	zheshi::bignum b=-24;
	std::cout<<a-b<<std::endl;
	std::cout<<a+b<<std::endl;
	std::cout<<a*b<<std::endl;
	std::cout<<a/b<<std::endl;
	return 0;
}
