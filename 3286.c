#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 50

int dist[MAX_SIZE*MAX_SIZE];

int qX[MAX_SIZE*MAX_SIZE*2];
int qY[MAX_SIZE*MAX_SIZE*2];

int offsetX[4] = {0,0,1,-1};
int offsetY[4] = {1,-1,0,0};

int getShortest(int** grid, int width, int height) {
	for (int y=0; y<height; y++)
		for (int x=0; x<width; x++)
			dist[y*width + x] = MAX_SIZE*MAX_SIZE;

	dist[0] = 0;
	int front = MAX_SIZE*MAX_SIZE;
	int back = MAX_SIZE*MAX_SIZE;
	qX[front] = 0;
	qY[back] = 0;

	while (front <= back) {
		int currX = qX[front];
		int currY = qY[front];
		front++;

		// check 4 possible neighbours
		for (int d=0; d<4; d++) {
			int nextX = currX+offsetX[d];
			int nextY = currY+offsetY[d];

			if (nextX>=0 && nextX<width &&
				nextY>=0 && nextY<height) {
				int cost = grid[nextY][nextX];
				int newDist = cost+dist[width*currY+currX];
				
				if (newDist < dist[width*nextY+nextX]) {
					dist[width*nextY+nextX] = newDist;
					
					if (!cost) {
						front--;
						qX[front] = nextX;
						qY[front] = nextY;
					} else {
						back++;
						qX[back] = nextX;
						qY[back] = nextY;
					}
				}
			}
		}
	}

	return dist[width*(height-1) + (width-1)];
}

bool findSafeWalk(int** grid, int gridSize, int* gridColSize, int health) {
    int width = gridColSize[0];
	int height = gridSize;

	// its basically find best route from (0,0) to (m-1, n-1). 01 bfs is recommended

	int s = getShortest(grid, width, height);
	
	return s<health-grid[0][0];
}

int main() {
    // Test: [[1,0,0,0],[0,0,0,0]], health=1
    int rows = 2, cols = 4;
    
    // Create grid
    int** grid = (int**)malloc(rows * sizeof(int*));
    int data[] = {1, 0, 0, 0, 0, 0, 0, 0};
    for (int i = 0; i < rows; i++) {
        grid[i] = (int*)malloc(cols * sizeof(int));
        for (int j = 0; j < cols; j++) {
            grid[i][j] = data[i * cols + j];
        }
    }
    
    int gridColSize[] = {cols};
    int health = 1;
    
    bool result = findSafeWalk(grid, rows, gridColSize, health);
    printf("Result: %s\n", result ? "true" : "false");
    
    for (int i = 0; i < rows; i++) free(grid[i]);
    free(grid);
    
    return 0;
}

