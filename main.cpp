#include <random>
#include <iostream>
#include <algorithm>
#include <chrono>
#include <climits>

using namespace std;

int rand_int()
{
	static std::mt19937 gen(std::random_device{}());
	std::uniform_int_distribution<int> dist(0, INT_MAX);
	return std::clamp((int)dist(gen), 0, INT_MAX);
}

void FastSquareRoot(float *number)
{
	uint32_t* number_I = reinterpret_cast<uint32_t*>(number);

	*number_I = 1598029824 - (*number_I >> 1);
}

float FastSquareRoot_I(float number)
{
	uint32_t* number_I = reinterpret_cast<uint32_t*>(&number);

	*number_I = 1598029824 - (*number_I >> 1);

	return number;
}


int main()
{
	chrono::steady_clock::time_point begin = chrono::steady_clock::now();

	int temp;

	chrono::steady_clock::time_point end = chrono::steady_clock::now();
	auto duration = chrono::duration_cast<chrono::nanoseconds>(end - begin);

	vector<int> vec;

	while (true)
	{
		vec.clear();

		for (int i = 0; i < 100000001; i++)
		{
			vec.emplace_back(rand_int());//
		}

		begin = chrono::steady_clock::now();

		for (int i = 0; i < 100000000; i++)
		{
			temp = FastSquareRoot_I(vec[i]);
		}

		end = chrono::steady_clock::now();
		duration = chrono::duration_cast<chrono::nanoseconds>(end - begin);

		cout << "MOYENNE 1 : " << duration.count() / 100000000 << " ns" << endl;

		begin = chrono::steady_clock::now();

		for (int i = 0; i < 100000000; i++)
		{
			temp = sqrt(vec[i]);
		}

		end = chrono::steady_clock::now();
		duration = chrono::duration_cast<chrono::nanoseconds>(end - begin);

		cout << "MOYENNE 2 : " << duration.count() / 100000000 << " ns" << endl;

		cout << endl;
	}

}
