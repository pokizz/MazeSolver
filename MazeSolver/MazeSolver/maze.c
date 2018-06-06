#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#include "maze.h"


/*  Ïðàâè ëàáèðèíò îò ôàéë  */

void GetMazeFromFile(char * filename, struct maze * maze) {
	
	char buffer[BUFFERSIZE];
	FILE * fp;
	char ** map;
	int n = 0, foundentrance = 0, foundexit = 0;


	/*  Îòâàðÿ ôàéëà */

	if (!(fp = fopen(filename, "r"))) {
		sprintf(buffer, "Couldn't open file %s", filename);
		perror(buffer);
		exit(EXIT_FAILURE);
	}


	/*  Ïðîâåðÿâà êîëêî ðåäà èìà ëàáèðèíòà */

	while (fgets(buffer, BUFFERSIZE, fp))
		++n;


	/*  Íàìèðà äîñòàòú÷íà ïàìåò çà ëàáèðèíòà  */

	if (!(map = malloc(n * sizeof *map))) {
		fputs("Couldn't allocate memory for map\n", stderr);
		exit(EXIT_FAILURE);
	}


	/*  Ðåñòàðòèðà ôàéëà  */

	rewind(fp);
	n = 0;


	/* Çàïàçâà âñåêè ðåä îò ëàáèðèíòà  */

	while (fgets(buffer, BUFFERSIZE, fp)) {
		int i;

		if (!(map[n] = malloc((strlen(buffer) + 1) * sizeof map[n]))) {
			fputs("Couldn't allocate memory for map\n", stderr);

			for (i = 0; i < n; ++i)
				free(map[i]);

			free(map);

			exit(EXIT_FAILURE);
		}

		strcpy(map[n], buffer);


		/*  Ïðåìàõâà ïðîñëåäÿâàíåòî íà ïðàçíèòå ìåñòà */

		for (i = strlen(map[n]) - 1; isspace(map[n][i]); --i)
			map[n][i] = 0;


		/*  Ïðîâåðÿ çà âõîä è çàïàçâà êîîðäèíàòèòå ìó àêî èìà òàêúâ  */

		if (!foundentrance) {
			i = 0;
			while (map[n][i] != 'I' && map[n][i++]);
			if (map[n][i] == MAZE_ENTRANCE) {
				maze->startx = i;
				maze->starty = n;
				foundentrance = 1;
			}
		}

		/*  Ïðîâåðÿâà çà èçõîä  */

		if (!foundexit) {
			if (strchr(map[n], MAZE_EXIT))
				foundexit = 1;
		}
		++n;
	}


	/*  Ñòðóêòóðà çà çàïúëâàíå íà ëàáèðèíòà  */

	maze->map = map;
	maze->numrows = n;


	/*  Ïðîãðàìàòà ñå ïðåêðàòÿâà àêî íÿìà âõîä èëè èçõîä */

	if (!foundentrance) {
		fputs("Maze has no entrance!\n", stderr);
		FreeMaze(maze);
		exit(EXIT_FAILURE);
	}

	if (!foundexit) {
		fputs("Maze has no exit!\n", stderr);
		FreeMaze(maze);
		exit(EXIT_FAILURE);
	}


	/*  Ïðîâåðÿâà çà ïúðâîíà÷àëíà ïîñîêà  */

	if (maze->startx < strlen(maze->map[maze->starty]) - 1 &&
		maze->map[maze->starty][maze->startx + 1] == MAZE_PATH)
		maze->initdir = MOVE_RIGHT;
	else if (maze->startx > 0 &&
		maze->map[maze->starty][maze->startx - 1] == MAZE_PATH)
		maze->initdir = MOVE_LEFT;
	else if (maze->starty > 0 &&
		maze->map[maze->starty - 1][maze->startx] == MAZE_PATH)
		maze->initdir = MOVE_UP;
	else if (maze->starty < (maze->numrows - 1) &&
		maze->map[maze->starty + 1][maze->startx] == MAZE_PATH)
		maze->initdir = MOVE_DOWN;


	/*  Ïðîãðàìàòà ñïèðà àêî íå ìîæå äà ñå çàòâîðè ôàéëà  */

	if (fclose(fp)) {
		perror("Couldn't close file");
		FreeMaze(maze);
		exit(EXIT_FAILURE);
	}
}


/*  Îñâáîæäàâà ïàìåòòà èçïîëçâàíà îò ëàáèðèíòà  */

void FreeMaze(struct maze * maze) {
	int n;

	for (n = 0; n < maze->numrows; ++n)
		free(maze->map[n]);

	free(maze->map);
}


/*  Ïðèíòèðà ëàáèðèíòà  */

void PrintMaze(struct maze * maze) {
	int n;

	for (n = 0; n < maze->numrows; ++n)
		puts(maze->map[n]);
}