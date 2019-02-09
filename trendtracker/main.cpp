
#include <cassert>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include <sstream>
#include "trendtracker.h"

using namespace std;
using namespace chrono;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
        abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


void test_size_add_hashtag()
{
	// Test size() and add_hashtag().
	Trendtracker T1;
	test(T1.size() == 0);
	T1.add_hashtag("#cs4all");
	test(T1.size() == 1);
	T1.add_hashtag("#algorithms");
	test(T1.size() == 2);
	T1.add_hashtag("#programming");
	test(T1.size() == 3);

	// Test adding a hashtag twice
	Trendtracker T2;
	T2.add_hashtag("#cs4all");
	test(T2.size() == 1);
	T2.add_hashtag("#programming");
	test(T2.size() == 2);
	T2.add_hashtag("#cs4all");
	test(T2.size() == 2);
	T2.add_hashtag("#programming");
	test(T2.size() == 2);
}

void test_tweeted_popularity()
{
	// Test whether popularity() returns 0 for hashtags in TrendTracker
	// and -1 for all other hashtags.
	Trendtracker T1;
	test(T1.popularity("#algorithms") == -1);
	test(T1.popularity("#cs4all") == -1);
	test(T1.popularity("#programming") == -1);
	T1.add_hashtag("#algorithms");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == -1);
	test(T1.popularity("#programming") == -1);
	T1.add_hashtag("#cs4all");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == -1);
	T1.add_hashtag("#programming");
	test(T1.popularity("#algorithms") == 0);
	test(T1.popularity("#cs4all") == 0);
	test(T1.popularity("#programming") == 0);

	// Test whether tweeted() adds to a hashtag's count
	// and that popularity() returns the correct total.
	Trendtracker T2;
	test(T2.popularity("#programming") == -1);
	T2.add_hashtag("#programming");
	test(T2.popularity("#programming") == 0);
	T2.tweeted("#programming");
	test(T2.popularity("#programming") == 1);
	T2.tweeted("#programming");
	test(T2.popularity("#programming") == 2);
	T2.tweeted("#programming");
	test(T2.popularity("#programming") == 3);

	// Same as previous test, but with multiple hashtags.
	Trendtracker T3;
	T3.add_hashtag("#programming");
	test(T3.popularity("#programming") == 0);
	test(T3.popularity("#cs4all") == -1);
	test(T3.popularity("#algorithms") == -1);
	test(T3.popularity("#C++") == -1);
	T3.add_hashtag("#cs4all");
	test(T3.popularity("#programming") == 0);
	test(T3.popularity("#cs4all") == 0);
	test(T3.popularity("#algorithms") == -1);
	test(T3.popularity("#C++") == -1);
	T3.add_hashtag("#algorithms");
	test(T3.popularity("#programming") == 0);
	test(T3.popularity("#cs4all") == 0);
	test(T3.popularity("#algorithms") == 0);
	test(T3.popularity("#C++") == -1);
	T3.tweeted("#programming");
	test(T3.popularity("#programming") == 1);
	test(T3.popularity("#cs4all") == 0);
	test(T3.popularity("#algorithms") == 0);
	test(T3.popularity("#C++") == -1);
	T3.tweeted("#cs4all");
	test(T3.popularity("#programming") == 1);
	test(T3.popularity("#cs4all") == 1);
	test(T3.popularity("#algorithms") == 0);
	test(T3.popularity("#C++") == -1);
	T3.tweeted("#algorithms");
	test(T3.popularity("#programming") == 1);
	test(T3.popularity("#cs4all") == 1);
	test(T3.popularity("#algorithms") == 1);
	test(T3.popularity("#C++") == -1);
	T3.tweeted("#cs4all");
	test(T3.popularity("#programming") == 1);
	test(T3.popularity("#cs4all") == 2);
	test(T3.popularity("#algorithms") == 1);
	test(T3.popularity("#C++") == -1);
	T3.tweeted("#algorithms");
	test(T3.popularity("#programming") == 1);
	test(T3.popularity("#cs4all") == 2);
	test(T3.popularity("#algorithms") == 2);
	test(T3.popularity("#C++") == -1);
	T3.add_hashtag("#C++");	
	test(T3.popularity("#programming") == 1);
	test(T3.popularity("#cs4all") == 2);
	test(T3.popularity("#algorithms") == 2);
	test(T3.popularity("#C++") == 0);

	// Another variation of multiple hashtag test
	Trendtracker T4;
	T4.add_hashtag("#3333");	
	T4.add_hashtag("#programming");
	T4.add_hashtag("#cs4all");
	T4.add_hashtag("#C++");
	T4.add_hashtag("#algorithms");
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#C++");	
	T4.tweeted("#C++");	
	T4.tweeted("#C++");	
	T4.tweeted("#C++");	
	T4.tweeted("#cs4all");
	T4.tweeted("#cs4all");
	T4.tweeted("#cs4all");
	T4.tweeted("#algorithms");
	T4.tweeted("#algorithms");
	T4.tweeted("#3333");
	test(T4.popularity("#programming") == 5);
	test(T4.popularity("#cs4all") == 3);
	test(T4.popularity("#algorithms") == 2);
	test(T4.popularity("#C++") == 4);
	test(T4.popularity("#3333") == 1);

	// Test popularity() when passed a hashtag that doesn't exist
	Trendtracker T5;
	T5.add_hashtag("#programming");
	test(T5.popularity("#programming") == 0);		
	test(T5.popularity("#cs4all") == -1);		
	test(T5.popularity("#algorithms") == -1);		
	T5.tweeted("#cs4all");
	test(T5.popularity("#programming") == 0);		
	test(T5.popularity("#cs4all") == -1);		
	test(T5.popularity("#algorithms") == -1);		
	T5.tweeted("#algorithms");
	test(T5.popularity("#programming") == 0);		
	test(T5.popularity("#cs4all") == -1);		
	test(T5.popularity("#algorithms") == -1);		
	T5.tweeted("#programming");
	test(T5.popularity("#programming") == 1);		
	test(T5.popularity("#cs4all") == -1);		
	test(T5.popularity("#algorithms") == -1);		

	// Test adding a hashtag a second time
	Trendtracker T6;
	T6.add_hashtag("#programming");
	T6.tweeted("#programming");
	T6.tweeted("#programming");
	test(T6.popularity("#programming") == 2);
	T6.add_hashtag("#programming");
	test(T6.size() == 1);
	test(T6.popularity("#programming") == 2);
}

void test_top_trend_trending()
{
	vector<string> R;
	string s; 

	// Test top_trend()
	Trendtracker T1;
	T1.add_hashtag("#programming");
	T1.tweeted("#programming");	
	// #programming: 1
	test(T1.top_trend() == "#programming");
	T1.add_hashtag("#C++");
	T1.tweeted("#C++");
	T1.tweeted("#C++"); 
	// #C++: 2, #programming: 1
	test(T1.top_trend() == "#C++"); 
	T1.add_hashtag("#3333");
	T1.tweeted("#3333");
	// #C++: 2, #programming: 1, #3333: 1 
	test(T1.top_trend() == "#C++"); 
	T1.add_hashtag("#cs4all");
	T1.tweeted("#cs4all");
	// #C++: 2, #programming: 1, #3333: 1, #cs4all: 1 
	test(T1.top_trend() == "#C++"); 
	T1.tweeted("#cs4all");
	T1.tweeted("#cs4all");
	// #cs4all: 3, #C++: 2, #programming: 1, #3333: 1
	test(T1.top_trend() == "#cs4all");
	T1.tweeted("#C++");
	T1.tweeted("#programming");	
	T1.tweeted("#programming");	
	T1.tweeted("#programming");	
	// #programming: 4, #cs4all: 3, #C++: 3, #3333: 1
	test(T1.top_trend() == "#programming");
	T1.tweeted("#3333");
	T1.tweeted("#3333");
	T1.tweeted("#3333");
	T1.tweeted("#3333");
	// #3333: 5, #programming: 4, #cs4all: 3, #C++: 3
	test(T1.top_trend() == "#3333");

	Trendtracker T2;
	test(T2.top_trend() == ""); // Test empty Trendtracker
	T2.add_hashtag("#cs4all");  
	test(T2.top_trend() == "#cs4all"); // Test 0 tweeted 
	T2.add_hashtag("#programming");  
	s = T2.top_trend();
	test(s == "#cs4all" || s == "#programming"); // Test a tie 

	// Test top_trends()
	Trendtracker T3;
	T3.add_hashtag("#programming");
	T3.tweeted("#programming");
	T3.trending(1, R);
	test(R.size() == 1);
	test(R[0] == "#programming"); 
	T3.trending(2, R); 
	test(R.size() == 1);
	test(R[0] == "#programming"); 

	Trendtracker T4;
	T4.add_hashtag("#programming");	
	T4.add_hashtag("#3333");	
	T4.add_hashtag("#cs4all");
	T4.add_hashtag("#C++");
	T4.add_hashtag("#algorithms");
	T4.add_hashtag("#programming");	
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#programming");
	T4.tweeted("#C++");	
	T4.tweeted("#C++");	
	T4.tweeted("#C++");	
	T4.tweeted("#cs4all");
	T4.tweeted("#cs4all");
	T4.tweeted("#algorithms");
	T4.trending(1, R);
	test(R.size() == 1);
	test(R[0] == "#programming");
	T4.trending(2, R);
	test(R.size() == 2);
	test(R[0] == "#programming");
	test(R[1] == "#C++");
	T4.trending(3, R);
	test(R.size() == 3);
	test(R[0] == "#programming");
	test(R[1] == "#C++");
	test(R[2] == "#cs4all");
	T4.trending(4, R);
	test(R.size() == 4);
	test(R[0] == "#programming");
	test(R[1] == "#C++");
	test(R[2] == "#cs4all");
	test(R[3] == "#algorithms");
	T4.trending(5, R);
	test(R.size() == 5);
	test(R[0] == "#programming");
	test(R[1] == "#C++");
	test(R[2] == "#cs4all");
	test(R[3] == "#algorithms");
	test(R[4] == "#3333");
	T4.trending(6, R);
	test(R.size() == 5);
	test(R[0] == "#programming");
	test(R[1] == "#C++");
	test(R[2] == "#cs4all");
	test(R[3] == "#algorithms");
	test(R[4] == "#3333");
	T4.tweeted("#C++");
	T4.tweeted("#C++");
	T4.trending(5, R);
	test(R.size() == 5);
	test(R[0] == "#C++");         // 5
	test(R[1] == "#programming"); // 4
	test(R[2] == "#cs4all");      // 2
	test(R[3] == "#algorithms");  // 1
	test(R[4] == "#3333");        // 0
	T4.tweeted("#3333");	
	T4.tweeted("#3333");	
	T4.tweeted("#3333");	
	T4.trending(5, R);
	test(R.size() == 5);
	test(R[0] == "#C++");         // 5
	test(R[1] == "#programming"); // 4
	test(R[2] == "#3333");        // 3
	test(R[3] == "#cs4all");      // 2
	test(R[4] == "#algorithms");  // 1
	T4.tweeted("#algorithms");	
	T4.tweeted("#algorithms");	
	T4.tweeted("#algorithms");	
	T4.tweeted("#algorithms");	
	T4.tweeted("#algorithms");	
	T4.trending(5, R);
	test(R.size() == 5);
	test(R[0] == "#algorithms");  // 6
	test(R[1] == "#C++");         // 5
	test(R[2] == "#programming"); // 4
	test(R[3] == "#3333");        // 3
	test(R[4] == "#cs4all");      // 2
	T4.tweeted("C++");
	T4.trending(5, R);
	test(R.size() == 5);
	test((R[0] == "#algorithms" && R[1] == "#C++") 
		|| (R[0] == "#C++" && R[1] == "#algorithms")); 
	test(R[2] == "#programming"); 
	test(R[3] == "#3333");        
	test(R[4] == "#cs4all");      

	Trendtracker T5;
	T5.trending(1, R);
	test(R.size() == 0);
	T5.add_hashtag("#cs4all");
	T5.trending(0, R);
	test(R.size() == 0);
	T5.trending(1000, R);
	test(R.size() == 1);
}

void test_add_hashtag_tweeted_popularity_perf()
{
	Trendtracker T1;

	// Test add_hashtag() performance.
	ifstream f;
	f.open("shaketags.txt", ios::in);
	assert(f.is_open()); // If this fails, you're missing above file
	string line;
	system_clock::time_point start = system_clock::now();
	while (getline(f, line))
		T1.add_hashtag(line);
	system_clock::time_point end = system_clock::now();
	f.close();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);

	// Test tweeted() performance. 
	f.open("shaketags.txt", ios::in);
	start = system_clock::now();
	while (getline(f, line))
		T1.tweeted(line);
	end = system_clock::now();
	f.close();
	dur = duration<float>(end - start).count();
	test(dur < 6.0);
	
	// Test popularity() performance. 
	f.open("shaketags.txt", ios::in);
	start = system_clock::now();
	for (int i = 0; i < 100000; ++i)
	{	
		getline(f, line);
		test(T1.popularity(line) > 0);
	}
	end = system_clock::now();
	f.close();
	dur = duration<float>(end - start).count();
	test(dur < 1.3);

	// Also check correctness a little 
	test(T1.size() == 13831); 
	test(T1.popularity("#hath") == 769);
	test(T1.popularity("#doth") == 317);
	test(T1.popularity("#whence") == 33);
	test(T1.popularity("#hark") == 63);
}

void test_top_trend_trending_perf()
{
	Trendtracker T1;
	vector<string> R;

	// Build a Trendtracker from Shakespeare
	ifstream f;
	f.open("shaketags.txt", ios::in);
	assert(f.is_open()); // If this fails, you're missing above file
	string line;
	while (getline(f, line))
	{
		T1.add_hashtag(line); 
		T1.tweeted(line);
	}
	f.close();
	
	// Test top_trend() performance.
	system_clock::time_point start = system_clock::now();
	for (int i = 0; i < 10000; ++i)
		test(T1.top_trend() == "#the");
	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 0.01);

	// Test trending() performance.
	start = system_clock::now();
	for (int i = 0; i < 10000; ++i)
		T1.trending(10, R);
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	test(dur < 0.1);
	test(R[0] == "#the");
	test(R[5] == "#a");
	test(R[9] == "#in");
	
	start = system_clock::now();
	T1.trending(100000, R);
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	test(dur < 0.1);
	test(R[28] == "#thou");
	test(R[34] == "#are");
	test(R[39] == "#good");
}


int main()
{
	// Setup
	srand(2017);

	test_size_add_hashtag();                    // Deadline 1 
	test_tweeted_popularity();                  // Deadline 2
	test_top_trend_trending();                  // Deadline 3
	test_add_hashtag_tweeted_popularity_perf(); // Deadline 4
	test_top_trend_trending_perf();             // Deadline 5

	cout << "Assignment complete." << endl;
}



