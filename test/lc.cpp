//#include <math.h>
#include <iostream>


int reverse(int x)
{
	if (x == INT_MIN) return 0;

	bool negative = false;
	if (x < 0) negative = true;

	x = abs(x);
	int j = 1;
	while (true)
	{
		if (x - pow(10, j) < 0) break;
		j++;
	}

	//x为j位整数

	int num = x;
	long long result = 0;

	for (int i = 0; i < j; i++)
	{
		unsigned int ratio = pow(10, (j - i - 1));
		float n = (float)num / ratio;
		unsigned int m = floor(n);
		num = num - ratio * m;
		result += pow(10,i) * m;
	}


	if (negative && result > pow(2, 31)) return 0;
	if (!negative && result > INT_MAX) return 0;

	int r = result;
	if (negative) r *= -1;
	return r;
}


bool isPalindrome(int x) {
	if (x < 0) return false;

	int result = 0;
	int k = x;
	while (k != 0)
	{
		int pop = k % 10;
		k /= 10;
		if (result > INT_MAX / 10 || (result == INT_MAX / 10 && pop > 7)) return 0;
		result = result * 10 + pop;
	}

	if (result == x) return true;
	return false;
}

int main(int argc, char *argv[])
{
	
	//int a = reverse(1534236469);
	//std::cout << a << std::endl;
	bool b = isPalindrome(12220);
	std::cout << b << std::endl;

	system("pause");
	return 0;
};