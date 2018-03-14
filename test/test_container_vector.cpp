
#include<ccdk/container/vector.h>
#include<stdio.h>

using namespace ccdk;
using namespace ccdk::mpl;
using namespace ccdk::ct;

struct no_trivial {
	int a = 0;

	no_trivial() { DebugValue("no_trivial construct"); }
	~no_trivial() { DebugValue("no_trivial destruct"); }
};

template<typename T1, typename T2>
struct has_swap
{
	template<typename P1, typename P2,
		typename = decltype(makeval<P1>().swap(makeval<P2>()))>
		constexpr static bool sfinae(int) { return true; }

	template<typename P1, typename P2>
	constexpr static bool sfinae(...) { return false; }

	constexpr static bool value = sfinae<T1, T2>(0);
};

int main()
{
	int v = 0;
	DebugNewTitle("empty constructor");
	{
		vector<int> ivec{}; 
	}

	DebugNewTitle(" fill constructor");
	DebugSubTitle("fill trivial");
	{
		vector<int> ivec(10, 0);
	}
		
	DebugSubTitle("fill trivial byte");
	{
		vector<char> ivec(10, '0');
	}
		
	DebugSubTitle("fill trivial");
	{
		vector<no_trivial> ivec(4);
	}
	DebugNewTitle(" iterator constructor");
	{
		vector<int> ivec1(10, 2);
		vector<int, units::uniform> ivec2(ivec1.begin(), ivec1.begin() + 3);
		vector<int, units::ratio<2,1>> ivec3(ivec1.begin(), ivec1.begin() + 3);
		RuntimeAssertTrue(ivec2.size() == 3);
		RuntimeAssertTrue(ivec2.capacity() == 3);
		RuntimeAssertTrue(ivec3.size() == 3);
		RuntimeAssertTrue(ivec3.capacity() == 6);
	}
	DebugNewTitle(" copy constructor");
	{
		vector<int> ivec1(10, 2);
		vector<int> ivec2(ivec1);
		vector<int> ivec3(util::move(ivec1));
		vector<int, units::ratio<2, 1>> ivec4{ ivec2 };
		vector<int, units::ratio<2, 1>> ivec5{ util::move(ivec2) };
	}
	DebugNewTitle("swap");
	{
		vector<int> ivec1(10, 1);
		vector<int> ivec2(10, 2);
		RuntimeAssertTrue(ivec1[0] == 1);
		RuntimeAssertTrue(ivec2[0] == 2);
		util::swap(ivec1, ivec2);
		RuntimeAssertTrue(ivec1[0] == 2);
		RuntimeAssertTrue(ivec2[0] == 1);
	}
	DebugNewTitle("copy assign");
	{
		DebugSubTitle("copy only");
		{
			vector<int> ivec1(10, 1);
			vector<int> ivec2(10, 2);
			ivec2 = nullptr;
			ivec2 = ivec1;
		}
		DebugSubTitle("template copy only");
		{
			vector<int> ivec1(10, 1);
			vector<int, units::ratio<3,1>> ivec2(10, 2);
			ivec1 = ivec2;
		}
		DebugSubTitle("allocate copy");
		{
			vector<int> ivec1(3, 1);
			vector<int> ivec2(10, 2);
			ivec1 = ivec2;
		}
		DebugSubTitle("template allocate only");
		{
			vector<int> ivec1(3, 1);
			vector<int, units::ratio<3, 1>> ivec2(10, 2);
			ivec1 = ivec2;
		}
	}
	DebugNewTitle("move assign");
	{
		DebugSubTitle("move only");
		{
			vector<int> ivec1(10, 1);
			vector<int> ivec2(10, 2);
			ivec2 = util::move(ivec1);
		}
		DebugSubTitle("template move only");
		{
			vector<int> ivec1(10, 1);
			vector<int, units::ratio<3, 1>> ivec2(10, 2);
			ivec1 = util::move(ivec2);
		}
	}
	DebugNewTitle("assign ");
	{
		vector<int> ivec1(10, 1);
		vector<int> ivec2(10, 1);
		ivec1.assign(nullptr)
			.assign(ivec2.begin(), ivec2.end())
			.assign(ivec2.begin(), ivec2.size())
			.assign(5,0)
			.assign({ 1,2,3 });
	}
	DebugNewTitle("attribute");
	{
		vector<int, units::ratio<2,1>> ivec1(10, 1);
		RuntimeAssertTrue(ivec1.size() == 10);
		RuntimeAssertTrue(ivec1.capacity() == 20);
		RuntimeAssertTrue(ivec1.max_size() == (uint32)(-1));
		RuntimeAssertTrue(!ivec1.empty());
	}
	DebugNewTitle("iterator");
	{
		vector<int, units::ratio<2, 1>> ivec1(3, 1);
		int c = 0;
		DebugSubTitle("iterator ");
		for (auto it = ivec1.begin(); it != ivec1.end(); ++it, ++c)
		{
			*it = c;
		}
		DebugSubTitle("foreach");
		for (auto& it : ivec1)
		{
			DebugValue(it);
		}
		DebugSubTitle("reverse iterator");
		for (auto it = ivec1.rbegin(); it != ivec1.rend(); ++it)
		{
			DebugValue(*it);
		}

		// *ivec1.cbegin() =1;
		// *ivec1.crbegin() = 1;
	}
	DebugNewTitle("pop_back");
	{
		no_trivial nt;
		DebugSubTitle("pop no-trivial ");
		{
			vector<no_trivial> ivec2(4, nt);
			ivec2.pop_back();
		}
		DebugSubTitle("pop int")
		{
			vector<int>        ivec1(4, 1);
			int c = 1;
			for (auto& i : ivec1) { i = c++; }
			ivec1.pop_back();
			for (auto& i : ivec1) { DebugValue(i); }
			ivec1.pop_back();
			for (auto& i : ivec1) { DebugValue(i); }
		}
	}
	DebugNewTitle("implace back")
	{

	}


	getchar();
	return 0;
}