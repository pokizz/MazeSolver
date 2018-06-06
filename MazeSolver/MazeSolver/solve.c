#include "solve.h"


/*  Рекурсивна функция за намиране на път през ла  */

int look(struct maze * maze, struct pos pos) {
	int i, n;


	/*  Смяна на посоката  */

	switch (pos.dir) {
	case MOVE_UP:
		pos.y -= 1;
		break;

	case MOVE_DOWN:
		pos.y += 1;
		break;

	case MOVE_LEFT:
		pos.x -= 1;
		break;

	case MOVE_RIGHT:
		pos.x += 1;
		break;

	default:
		break;
	}


	/*  Проверява за нова позиция  */

	if (pos.y < 0 || pos.y >= maze->numrows)
		return MAZE_NOWAY;
	else if (pos.x < 0 || pos.x >= strlen(maze->map[pos.y]))
		return MAZE_NOWAY;
	else if (maze->map[pos.y][pos.x] == MAZE_WALL)
		return MAZE_NOWAY;
	else if (maze->map[pos.y][pos.x] == MAZE_EXIT)
		return MAZE_FOUNDEXIT;
	else if (maze->map[pos.y][pos.x] == MAZE_ENTRANCE)
		return MAZE_NOEXIT;


	/* Проверява за трите възможни посоки само не и в обратна посока  */

	pos.dir -= 1;
	if (pos.dir < 0)
		pos.dir += 4;

	for (i = 0; i < 3; ++i) {
		maze->map[pos.y][pos.x] = MAZE_TRAIL;          /*  Изписва символът, който служи за изминатия път  */

		n = look(maze, pos);
		if (n) {
			if (n == MAZE_NOEXIT)
				maze->map[pos.y][pos.x] = MAZE_PATH;   /*  Ако няма изход се изтрива "MAZE_TRAIL"   */
			return n;
		}

		pos.dir += 1;
		if (pos.dir > 3)
			pos.dir -= 4;
	}


	/*  Път без изход, изтрива "MAZE_TRAIL" и се връща  */

	maze->map[pos.y][pos.x] = MAZE_PATH;

	return 0;
}


/*  Функция за намирането на пътя през лабиринта  */

int solve(struct maze * maze) {
	struct pos pos;

	pos.x = maze->startx;
	pos.y = maze->starty;
	pos.dir = maze->initdir;

	return look(maze, pos);
}