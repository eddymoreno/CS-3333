
#include <iostream>
#include <cstdlib>
#include <string>
#include <chrono>
#include "mazemapper.h"

using namespace std;
using namespace chrono;

inline void _test(const char* expression, const char* file, int line)
{
	cerr << "test(" << expression << ") failed in file " << file;
	cerr << ", line " << line << "." << endl;
        abort();
}

#define test(EXPRESSION) ((EXPRESSION) ? (void)0 : _test(#EXPRESSION, __FILE__, __LINE__))


void test_width_height_valid()
{
	system_clock::time_point start = system_clock::now();

	string maze;

	// Has chars other than '\n', '#', ' '
	maze = "";
	maze += "##### #\n";
	maze += "#@ #  #\n";
	maze += "## ####\n";
	Mazemapper M1(maze);
	test(!M1.valid());
	test(M1.width() == -1);
	test(M1.height() == -1);

	// Not rectangular
	maze = "";
	maze += "#### ##\n";
	maze += "#     #\n";
	maze += " ###### \n";
	Mazemapper M2(maze);
	test(!M2.valid());
	test(M2.width() == -1);
	test(M2.height() == -1);

	// Not rectangular
	maze = "";
	maze += "## #####\n";
	maze += "#    # \n";
	maze += "########\n";
	Mazemapper M3(maze);
	test(!M3.valid());
	test(M3.width() == -1);
	test(M3.height() == -1);

	// Not exactly 2 exits (0 instead)
	maze = "";
	maze += "####\n";
	maze += "#  #\n";
	maze += "####\n";
	Mazemapper M4(maze);
	test(!M4.valid());
	test(M4.width() == -1);
	test(M4.height() == -1);

	// Not exactly 2 exits (1 instead)
	maze = "";
	maze += "####\n";
	maze += "#  #\n";
	maze += "# ##\n";
	Mazemapper M5(maze);
	test(!M5.valid());
	test(M5.width() == -1);
	test(M5.height() == -1);

	// Not exactly 2 exits (3 instead)
	maze = "";
	maze += "# ##\n";
	maze += "#   \n";
	maze += "# ##\n";
	Mazemapper M6(maze);
	test(!M6.valid());
	test(M6.width() == -1);
	test(M6.height() == -1);

	maze = "";
	maze += "### ##\n";
	maze += "#    #\n";
	maze += "#    #\n";
	maze += "### ##\n";
	Mazemapper M7(maze);
	test(M7.valid());
	test(M7.width() == 6);
	test(M7.height() == 4);

	maze = "";
	maze += "#### ##\n";
	maze += "#     #\n";
	maze += " ######\n";
	Mazemapper M8(maze);
	test(M8.valid());
	test(M8.width() == 7);
	test(M8.height() == 3);

	maze = "";
	maze += "#### ##\n";
	maze += "#  #  #\n";
	maze += "# #####\n";
	Mazemapper M9(maze);
	test(M9.valid());
	test(M9.width() == 7);
	test(M9.height() == 3);

	maze = "";
	maze += "# ## ##\n";
	Mazemapper M10(maze);
	test(M10.valid());
	test(M10.width() == 7);
	test(M10.height() == 1);

	maze = "";
	maze += " \n";
	maze += "#\n";
	maze += "#\n";
	maze += "#\n";
	maze += " \n";
	Mazemapper M11(maze);
	test(M11.valid());
	test(M11.width() == 1);
	test(M11.height() == 5);

	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);
}

void test_solvable()
{
	system_clock::time_point start = system_clock::now();

	string maze;

	// Isn't valid, so isn't solvable.
	maze = "";
	maze += "##### #\n";
	maze += "#@    #\n";
	maze += "## ####\n";
	Mazemapper M1(maze);
	test(!M1.solvable());

	// Isn't valid, so isn't solvable.
	maze = "";
	maze += "##### #\n";
	maze += "#     #\n";
	maze += "## ## #\n";
	Mazemapper M2(maze);
	test(!M2.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#     #\n";
	maze += "# #####\n";
	Mazemapper M3(maze);
	test(M3.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#  #  #\n";
	maze += "# #####\n";
	Mazemapper M4(maze);
	test(!M4.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# # # #\n";
	maze += "# #   #\n";
	maze += "# #####\n";
	Mazemapper M5(maze);
	test(M5.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# ### #\n";
	maze += "# #   #\n";
	maze += "# #####\n";
	Mazemapper M6(maze);
	test(!M6.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#   ###\n";
	maze += "# # # #\n";
	maze += "# #   #\n";
	maze += "# #####\n";
	Mazemapper M7(maze);
	test(!M7.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "# # # #\n";
	maze += "# # # #\n";
	maze += "# #   #\n";
	maze += "# #####\n";
	Mazemapper M8(maze);
	test(!M8.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# # # #\n";
	maze += "# ##  #\n";
	maze += "# #####\n";
	Mazemapper M9(maze);
	test(!M9.solvable());

	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# # # #\n";
	maze += "# #  ##\n";
	maze += "# #####\n";
	Mazemapper M10(maze);
	test(!M10.solvable());

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "# ## ###\n";
	maze += "#  #   #\n";
	maze += "## ## ##\n";
	maze += "## ##  #\n";
	maze += "## ### #\n";
	maze += "## ### #\n";
	Mazemapper M11(maze);
	test(M11.solvable());

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "# ######\n";
	maze += "#  #   #\n";
	maze += "# ### ##\n";
	maze += "#  ##  #\n";
	maze += "## ### #\n";
	maze += "## ### #\n";
	Mazemapper M12(maze);
	test(!M12.solvable());

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "## ## ##\n";
	maze += "#  ##  #\n";
	maze += "## ### #\n";
	maze += "## ### #\n";
	Mazemapper M13(maze);
	test(M13.solvable());

	maze = "";
	maze += "####### #\n";
	maze += "#       #\n";
	maze += "# # # # #\n";
	maze += "#       #\n";
	maze += "# #######\n";
	Mazemapper M14(maze);
	test(M14.solvable());

	maze = "";
	maze += "#########################################################\n";
	maze += "#     #  #     #  #  #  #  #     #        #     #       #\n";
	maze += "  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##  \n";
	maze += "#  #        #                 #     #  #     #     #  # #\n";
	maze += "#########################################################\n";
	Mazemapper M15(maze);
	test(M15.solvable());

	maze = "";
	maze += "# ######################################\n";
	maze += "#   ###     ##                      ## #\n";
	maze += "### ### ### #  ###### ######## #  # #  #\n";
	maze += "# #     # # ##      #        # #### # ##\n";
	maze += "# ####### # ##### # # ###### # #       #\n";
	maze += "#         #     # # #      # # #  ##   #\n";
	maze += "# ### ### ##### # # ######## # #####   #\n";
	maze += "# ### #     #   ###          # ##    ###\n";
	maze += "#     # ### # ######## #######  # #### #\n";
	maze += "# # # # ### #          ##    ## # ## # #\n";
	maze += "# # # #     ########## #   #### # ## # #\n";
	maze += "# # ##### #          # ### #    #      #\n";
	maze += "# #    ## #######  # # #      # ### ####\n";
	maze += "# #### ##   # # #### # #####  #   # #  #\n";
	maze += "# ## ## ###       ## #       ## # # # ##\n";
	maze += "## # #  ###### ## ## ####### ## # # # ##\n";
	maze += "#  # #       # ##                      #\n";
	maze += "###################################### #\n";
	Mazemapper M16(maze);
	test(M16.solvable());

	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);
}

void test_solution()
{
	system_clock::time_point start = system_clock::now();

	string maze;
	string soln;

	// Isn't valid, so isn't solvable.
	maze = "";
	maze += "##### #\n";
	maze += "#@    #\n";
	maze += "## ####\n";
	Mazemapper M1(maze);
	test(M1.solution() == "");

	// Isn't valid, so isn't solvable.
	maze = "";
	maze += "##### #\n";
	maze += "#     #\n";
	maze += "## ## #\n";
	Mazemapper M2(maze);
	test(M2.solution() == "");

	maze = "";
	maze += "##### #\n";
	maze += "#     #\n";
	maze += "# #####\n";
	soln = "";
	soln += "#####o#\n";
	soln += "#ooooo#\n";
	soln += "#o#####\n";
	Mazemapper M3(maze);
	test(M3.solution() == soln);
	
	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# #####\n";
	Mazemapper M4(maze);
	test(M4.solution() == "");
	
	maze = "";
	maze += "##### #\n";
	maze += "#   # #\n";
	maze += "# # # #\n";
	maze += "# #   #\n";
	maze += "# #####\n";
	soln = "";
	soln += "#####o#\n";
	soln += "#ooo#o#\n";
	soln += "#o#o#o#\n";
	soln += "#o#ooo#\n";
	soln += "#o#####\n";
	Mazemapper M5(maze);
	test(M5.solution() == soln);

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "## ## ##\n";
	maze += "#  ##  #\n";
	maze += "## ### #\n";
	maze += "## ### #\n";
	soln = "";
	soln += "########\n";
	soln += "#      #\n";
	soln += "# ## ###\n";
	soln += "# oooo #\n";
	soln += "##o##o##\n";
	soln += "# o##oo#\n";
	soln += "##o###o#\n";
	soln += "##o###o#\n";
	Mazemapper M6(maze);
	test(M6.solution() == soln);

	maze = "";
	maze += "########\n";
	maze += "#  #    \n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "# # # ##\n";
	maze += "# ###  #\n";
	maze += "#  ### #\n";
	maze += "## #####\n";
	soln = "";
	soln += "########\n";
	soln += "#  #oooo\n";
	soln += "# ##o###\n";
	soln += "#oooo  #\n";
	soln += "#o# # ##\n";
	soln += "#o###  #\n";
	soln += "#oo### #\n";
	soln += "##o#####\n";
	Mazemapper M7(maze);
	test(M7.solution() == soln);
		
	maze = "";
	maze += "# ######\n";
	maze += "#  #   #\n";
	maze += "# ## ###\n";
	maze += "#      #\n";
	maze += "# # # ##\n";
	maze += "# ###  #\n";
	maze += "#  ###  \n";
	maze += "########\n";
	soln = "";
	soln += "#o######\n";
	soln += "#o #   #\n";
	soln += "#o## ###\n";
	soln += "#ooooo #\n";
	soln += "# # #o##\n";
	soln += "# ###oo#\n";
	soln += "#  ###oo\n";
	soln += "########\n";
	Mazemapper M8(maze);
	test(M8.solution() == soln);

	maze = "";
	maze += "########\n";
	maze += "#      #\n";
	maze += "#      #\n";
	maze += "#      #\n";
	maze += "## ## ##\n";
	maze += "## ##  #\n";
	maze += "## ### #\n";
	soln = "";
	soln += "########\n";
	soln += "#      #\n";
	soln += "#      #\n";
	soln += "# oooo #\n";
	soln += "##o##o##\n";
	soln += "##o##oo#\n";
	soln += "##o###o#\n";
	Mazemapper M9(maze);
	test(M9.solution() == soln);

	maze = "";
	maze += "#########################################################\n";
	maze += "#     #        #  #  #     #  #  #        #     #       #\n";
	maze += "  ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ## ##  \n";
	maze += "#  #     #  #           #           #  #     #     #  # #\n";
	maze += "#########################################################\n";
	soln = "";
	soln += "#########################################################\n";
	soln += "#oooo #ooooooo #  #  #oooo #  #  #ooooooo #oooo #ooooooo#\n";
	soln += "oo##o##o## ##o## ## ##o##o## ## ##o## ##o##o##o##o## ##oo\n";
	soln += "#  #oooo #  #oooooooooo #oooooooooo #  #oooo #oooo #  # #\n";
	soln += "#########################################################\n";
	Mazemapper M10(maze);
	test(M10.solution() == soln);

	maze = "";
	maze += "# ######################################\n";
	maze += "#   ###     ##                      ## #\n";
	maze += "### ### ### #  ###### ######## #  # #  #\n";
	maze += "# #     # # ##      #        # #### # ##\n";
	maze += "# ####### # ##### # # ###### # #       #\n";
	maze += "#         #     # # #      # # #  ##   #\n";
	maze += "# ### ### ##### # # ######## # #####   #\n";
	maze += "# ### #     #   ###          # ##    ###\n";
	maze += "#     # ### # ######## #######  # #### #\n";
	maze += "# # # # ### #          ##    ## # ## # #\n";
	maze += "# # # #     ########## #   #### # ## # #\n";
	maze += "# # ##### #          # ### #    #      #\n";
	maze += "# #    ## #######  # # #      # ### ####\n";
	maze += "# #### ##   # # #### # #####  #   # #  #\n";
	maze += "# ## ## ###       ## #       ## # # # ##\n";
	maze += "## # #  ###### ## ## ####### ## # # # ##\n";
	maze += "#  # #       # ##                      #\n";
	maze += "###################################### #\n";
	soln = "";
	soln += "#o######################################\n";
	soln += "#ooo###ooooo##                      ## #\n";
	soln += "###o###o###o#  ###### ######## #  # #  #\n";
	soln += "# #ooooo# #o##      #        # #### # ##\n";
	soln += "# ####### #o##### # # ###### # #       #\n";
	soln += "#         #ooooo# # #      # # #  ##   #\n";
	soln += "# ### ### #####o# # ######## # #####   #\n";
	soln += "# ### #     #ooo###          # ##    ###\n";
	soln += "#     # ### #o######## #######  # #### #\n";
	soln += "# # # # ### #oooooooooo##    ## # ## # #\n";
	soln += "# # # #     ##########o#   #### # ## # #\n";
	soln += "# # ##### #          #o### #    #      #\n";
	soln += "# #    ## #######  # #o#      # ### ####\n";
	soln += "# #### ##   # # #### #o#####  #   # #  #\n";
	soln += "# ## ## ###       ## #ooooooo## # # # ##\n";
	soln += "## # #  ###### ## ## #######o## # # # ##\n";
	soln += "#  # #       # ##           ooooooooooo#\n";
	soln += "######################################o#\n";
	Mazemapper M11(maze);
	test(M11.solution() == soln);

	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	test(dur < 30.0);
}

void test_perf()
{
	string maze;
	string soln;
	int width;
	int height;

	// Test a very wide tunnel
	width = 100000;
	height = 3;
	for (int i = 0; i < width; ++i)
		maze += '#';
	maze += '\n';
	for (int i = 0; i < width; ++i)
		maze += ' ';
	maze += '\n';
	for (int i = 0; i < width; ++i)
		maze += '#';
	maze += '\n';

	system_clock::time_point start = system_clock::now();
	Mazemapper M1(maze);	
	system_clock::time_point end = system_clock::now();
	float dur = duration<float>(end - start).count();
	cout << "Time: " << dur << endl;
	test(dur < 0.8);

	start = system_clock::now();
	for (int i = 0; i < 100000; ++i)
	{
		test(M1.valid());
		test(M1.width() == width);
		test(M1.height() == height);
	}
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	cout << "Time: " << dur << endl;
	test(dur < 0.02);

	start = system_clock::now();
	test(M1.solvable());	
	end = system_clock::now();		
	dur = duration<float>(end - start).count();
	cout << "Time: " << dur << endl;
	test(dur < 1.0);

	start = system_clock::now();
	soln = M1.solution();
	end = system_clock::now();		
	test(soln[width+1+1] == 'o' && soln[(width+1)*2-1-1] == 'o');
	dur = duration<float>(end - start).count();
	cout << "Time: " << dur << endl;
	test(dur < 2.0);


	// Test a very tall tunnel
	width = 3;
	height = 100000;
	maze = "";
	for (int i = 0; i < 100000; ++i)
		maze += "# #\n";

	start = system_clock::now();
	Mazemapper M2(maze);	
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	cout << "Time: " << dur << endl;
	test(dur < 0.8);
		
	start = system_clock::now();
	for (int i = 0; i < height; ++i)
	{
		test(M2.valid());
		test(M2.width() == width);
		test(M2.height() == height);
	}
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	test(dur < 0.02);

	start = system_clock::now();
	test(M2.solvable());	
	end = system_clock::now();		
	dur = duration<float>(end - start).count();
	test(dur < 1.0);

	start = system_clock::now();
	soln = M2.solution();
	end = system_clock::now();		
	test(soln[1] == 'o' && soln[(width+1)*height-1-2] == 'o');
	dur = duration<float>(end - start).count();
	test(dur < 2.0);


	// Test a square-ish maze with vertical tunnels 
	width = 400;
	height = 1000;
	// First row
	maze = "# ";
	for (int c = 0; c < width-2; ++c)
		maze += '#';
	maze += '\n';
	// Second row
	maze += '#';
	for (int c = 0; c < width-2; ++c)
		maze += ' ';
	maze += "#\n";
	// Middle rows
	string line = "#";
	for (int c = 0; c < width-2; ++c)
		line += (c % 2) ? ' ' : '#';
	line += "#\n";	
	for (int r = 0; r < height-3; ++r)
		maze += line; 
	// Last row
	for (int c = 0; c < width-2; ++c)
		maze += '#';
	maze += " #\n";
	
	start = system_clock::now();
	Mazemapper M3(maze);	
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	cout << "Time: " << dur << endl;
	test(dur < 0.8);
		
	start = system_clock::now();
	for (int i = 0; i < 100000; ++i)
	{
		test(M3.valid());
		test(M3.width() == width);
		test(M3.height() == height);
	}
	end = system_clock::now();
	dur = duration<float>(end - start).count();
	test(dur < 0.02);

	start = system_clock::now();
	test(M3.solvable());	
	end = system_clock::now();		
	dur = duration<float>(end - start).count();
	test(dur < 2.0);

	start = system_clock::now();
	soln = M3.solution();
	end = system_clock::now();		
	test(soln[1] == 'o' && soln[(width+1)*height-1-2] == 'o');
	dur = duration<float>(end - start).count();
	test(dur < 4.0);
}

int main()
{
	test_width_height_valid(); // Deadline 1
	test_solvable();           // Deadline 2
	test_solution();           // Deadline 3
	test_perf();               // Deadline 4

	cout << "Assignment complete." << endl;
}



