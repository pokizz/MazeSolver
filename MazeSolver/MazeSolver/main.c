#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
#include "solve.h"


int main(int argc, char ** argv []) {
	struct maze maze;
	argv[1] = "maze1.txt";
	

	GetMazeFromFile(argv[1], &maze);

	if (solve(&maze) == MAZE_FOUNDEXIT)
		puts("Found exit!");
	else
		puts("Can't reach exit!");

	PrintMaze(&maze);
	FreeMaze(&maze);
	system("pause");

	return EXIT_SUCCESS;
}