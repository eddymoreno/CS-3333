#include "mazemapper.h"
#include <iostream>
#include <unordered_set>
#include <stack>
#include <algorithm>
#include <queue>
#include <map>

Mazemapper::Mazemapper(string maze)
{
	start = nullptr;
	end = nullptr;
	_width = -1;
	_height = -1;
	V.clear();
	int spaces = 0;
	int s_i = -1;
	int e_i = -1;

	//Checks for invalid chars
	if (maze.find_first_not_of("# \n") != -1)
		return;

	//Checks for valid width
	int w = maze.find_first_of('\n');
	if (maze.length() % (w + 1) != 0)
		return;
	else
		_width = w;
	_height = maze.length() / (w + 1); //assigns height

	int r = 0;
	int c = 0;
	int exits = 0;
	for (unsigned int i = 0; i < maze.length(); ++i)
	{
		if (exits > 2) // Too many exits
		{
			_width = -1;
			_height = -1;
			return;
		}

		if (c == _width) //Updates column number
		{
			r++;
			c = 0;
		}
		else
			c++;

		if (r == 0 && maze[i] == ' ') //Top boundary exits
		{
			exits++;
			if (s_i == -1)
				s_i = spaces;
			else
				e_i = spaces;
		}

		else if ((c == 1 || c == _width) && maze[i] == ' ') //Left + Right boundary exits
		{
			exits++;
			if (s_i == -1)
				s_i = spaces;
			else
				e_i = spaces;
		}
		else if (r == _height - 1 && maze[i] == ' ') // Bottom boundary exits
		{
			exits++;
			if (s_i == -1)
				s_i = spaces;
			else
				e_i = spaces;
		}

		if (maze[i] == ' ') //Add Vertex for ' '
		{
			spaces++;
			Vertex* v1 = new Vertex();
			v1->r = r;
			v1->c = c;
			V.push_back(v1);

			//Made it super slow n^2 probably worst :/
			/*if (!V.empty()) //add to adjancy list
			{
				for (Vertex* i : V)
				{
					if ((i->r == r && i->c == c - 1) || (i->r == r && i->c == c + 1)) //neighbors in row
					{
						v1->neighs.push_back(i);
						i->neighs.push_back(v1);
					}
					else if (i->r == r - 1 && i->c == c) // neighbors above
					{
						v1->neighs.push_back(i);
						i->neighs.push_back(v1);
					}
				}

			}*/
		}

		if (maze[i] == '#')//add vertex for '#'
		{
			spaces++;
			Vertex* v2 = new Vertex();
			v2->r = -10;//set invalid row & col
			v2->c = -10;
			V.push_back(v2);
		}
	}

	if (exits < 2) //Not enough exits
	{
		_width = -1;
		_height = -1;
		return;
	}

	//Set exits
	start = V.at(s_i);
	end = V.at(e_i);
	
	//Make the graph faster n time
	unsigned int wi = static_cast<unsigned int>(_width);
	for (unsigned int i = 0; i < V.size()-1; ++i)
	{
		if ((V.at(i)->r == V.at(i + 1)->r) && (V.at(i)->c == V.at(i + 1)->c-1))
		{
			V.at(i)->neighs.push_back(V.at(i+1));
			V.at(i+1)->neighs.push_back(V.at(i));
		}
		if (i > wi)
		{
			if (V.at(i - _width)->c == V.at(i)->c)
			{
				V.at(i)->neighs.push_back(V.at(i - _width));
				V.at(i - _width)->neighs.push_back(V.at(i));
			}
		}

	}
	//print stuff for checking
	/*cout << maze << endl;
	for (Vertex* i : V) //Display Graph
	{
			cout << "[ " << i->r << " , " << i->c << " ] ";
			for (Vertex* x : i->neighs)
				cout << "[ " << x->r << " , " << x->c << " ] ";
			cout << endl;
	}
	cout << endl;
	cout << "H: " << _height << endl;
	cout << "W: " << _width << endl;
	cout << "E: " << exits << endl;
	cout << "S: " << spaces << endl;
	cout << "s_i: " << s_i << endl;
	cout << "e_i: " << e_i << endl;
	cout << "Start: " << "[ " << start->r << " , " << start->c << " ] " << endl;
	cout << "End: " << "[ " << end->r << " , " << end->c << " ] " << endl << endl << endl;*/
}

bool Mazemapper::valid() 
{
	if (_width == -1) //_width is used as flag
		return false;
	else
		return true;
}

int Mazemapper::width()
{ 
	return _width;
}

int Mazemapper::height()
{
	return _height;
}

bool Mazemapper::solvable() //Used BFS to check if path exists
{
	if(!valid())
		return false;
	else
	{ 
		queue<Vertex*> Q;
		unordered_set<Vertex*> R;
		Q.push(start);
		R.insert(start);

		while (Q.size() > 0)
		{
			Vertex* cur = Q.front();
			Q.pop();

			if (cur == end)
				return true;

			for (Vertex* neigh : cur->neighs)
			{
				if (R.find(neigh) != R.end())
					continue;
				R.insert(neigh);
				Q.push(neigh);
			}
		}
		return false;
	}
}

string Mazemapper::solution() //Used Dijstra's to find shortest path
{
	if (!valid())
		return "";
	else if (!solvable())
		return "";
	else
	{
		priority_queue<pair<Vertex*, int>> Q;
		map<Vertex*, int> D;
		map<Vertex*, Vertex*> P;

		for (Vertex* v : V)
			D[v] = INT_MAX; //Set distances

		D[start] = 0;
		P[start] = nullptr;
		Q.push({ start,0 });

		while(Q.size() > 0)
		{
			Vertex* c = Q.top().first;
			Q.pop();

			for (Vertex* neigh : c->neighs)
			{
				if (D[c] + 1 < D[neigh])
				{
					D[neigh] = D[c] + 1;//Set new distances
					P[neigh] = c;
					Q.push({ neigh, D[neigh] });
				}
			}
	}
		string ans = "";
		int col = 0;
		int row = 0;
		unsigned int ctr = 0;
		for (int i = 0; i <= ((_height * _width) - 1); ++i) // Generate solution fill '#'
		{
			col++;
			if (col == _width)
			{
				ans += "#\n";
				col = 0;
				row++;
			}
			else
				ans += "#";
		}

		for (Vertex* v : V) //Generate solution fill ' '
		{
			if (v->r == -10) //ignore '#' vertices
				continue;
			ans[((v->r * (_width + 1)) + (v->c - 1))] = ' ';
		}
		Vertex * c = end;
		while (P[c] != nullptr) //Fill shortest path in ans
		{
			ans[((c->r * (_width + 1)) + (c->c -1))] = 'o';
			c = P[c];
		}
		ans[((start->r * (_width + 1)) + (start->c - 1))] = 'o'; //Mark start

		//print stuff for checking
		/*cout <<"S: " << D[start] << endl;
		cout <<"E: " <<  D[end] << endl;
		cout <<"Answer:" << endl << endl << ans << endl << endl;*/
		return ans;
	}
}