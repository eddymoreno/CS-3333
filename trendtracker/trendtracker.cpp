#include"trendtracker.h"
using namespace std;

// For the mandatory running times below:
// n is the number of hashtags in the Trendtracker.
// Creates a new empty collection of hashtags.
Trendtracker::Trendtracker()
{
	return;
}

// Adds a hashtag (tweeted 0 times) to the Trendtracker.
// If the hashtag already is in Trendtracker, does nothing.
// Must run in O(log(n)) time if the hashtag is already in 
// the Trendtracker, and O(n) time otherwise.
void Trendtracker::add_hashtag(string ht)
{
	int index = S_index(ht);	//Calls binary search - returns where a hashtag should go			
	int size = S.size();

	if ((-1 < index && index < size) && E[S[index]].hashtag == ht) // checks if hashtag is already present
		return;
	else
	{
		S.insert(S.begin() + index, E.size()); //Inserts index of hastag in E in S[index]

		Entry One;
		One.hashtag = ht;
		One.count = 0;
		E.push_back(One); // adds hashtag to the back of E
	}
}

// Return the number of hashtags in the Trendtracker.
// Must run in O(1) time.
int Trendtracker::size()
{
	return E.size();
}

// Adds 1 to the total number times a hashtag has been tweeted.
// If the hashtag does not exist in TrendTracker, does nothing.
// Must run in O(log(n)) time.
void Trendtracker::tweeted(string ht)
{
	int index_in_S = S_index(ht); //Calls binary search - returns where a hashtag should be
	int size = E.size();

	if ((-1 < index_in_S && index_in_S < size) && E[S[index_in_S]].hashtag == ht) //checks for out of bounds exceptions and if hashtag is present
	{
		E[S[index_in_S]].count++;

		//Searches for the index where the hashtag should be placed after incrementing
		int l = 0, target = -1, m, r = S[index_in_S] - 1;

		while (l <= r)
		{			
			m = (l + r) / 2;

			if (E[m].count < E[S[index_in_S]].count)
			{
				target = m;
				r = m - 1;
			}
			else
				l = m + 1;
		}

		if (target != -1) // target is -1 if the hashtag shouldn't be moved
		{
			
			int new_index_in_S = S_index(E[target].hashtag);
			int size = S.size();
			if ((-1 < new_index_in_S && new_index_in_S < size) && E[S[new_index_in_S]].hashtag == E[target].hashtag)
			{
				//swapping in E
				Entry Temp = E[S[new_index_in_S]];
				E[S[new_index_in_S]] = E[S[index_in_S]];
				E[S[index_in_S]] = Temp;

				//swapping in S
				int Temp2 = S[new_index_in_S];
				S[new_index_in_S] = S[index_in_S];
				S[index_in_S] = Temp2;
			}

		}
	}
	return;
}

// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
// Must run in O(log(n)) time.
int Trendtracker::popularity(string name)
{
	int index = S_index(name); //Calls binary search - returns where a hashtag should be
	int size = E.size();

	if ((-1 < index && index < size) && E[S[index]].hashtag == name) //checks for out of bounds exceptions and if hashtag is present
	{
		return E[S[index]].count;
	}
	return -1;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
// Must run in O(1) time.
string Trendtracker::top_trend()
{
	if (E.empty())
		return "";
	return E[0].hashtag;
}

// Fills the provided vector with the k most-tweeted hashtags, 
// in order of most-tweeted-to-least-tweeted.
// 
// If there are fewer than k hashtags, then the vector is filled
// with all hashtags (in most-tweeted-to-least-tweeted order)>
//	
// Must run in O(k) time.
// (Tip: vector.push_back() is O(1) time).
void Trendtracker::trending(int k, vector<string> &T)
{
	T.clear(); //clears vector T
	int size = E.size();
	for (int i = 0; (i < k) && (i < size); ++i)
	{
		T.push_back(E[i].hashtag); // copies sorted elements to new vector T
	}
}

// Optional helper method.
// Returns the index in S of the hashtag with the given name. 
// I.e. the index i such that H[S[i]]->name == name.
//
// Should run in O(log(n)) time.
int Trendtracker::S_index(string ht)
{
	//returns the index where a hashtag is
	//if not present, then where it should be placed
	int l = 0, m, r = E.size() - 1;

	while (l < r)
	{
		m = (l + r) / 2;	 // Halfway between l and r
		if (E[S[m]].hashtag == ht)		 // Found it!
			return m;
		else if (E[S[m]].hashtag < ht)	 // Search in right half
			l = m + 1;
		else				 // Search in left half
			r = m - 1;
	}
	if (E.empty())
		return 0;
	else if (E[S[l]].hashtag < ht)
		return (l + 1);
	else
		return l;
}

// Optional helper method to return the lowest index in P
// pointing to a hashtag with the specified number of tweets.
// 
// Should run in O(log(n)) time.
int Trendtracker::lowest_E_index_with_count(int count)
{
	return -1;
}