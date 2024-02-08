#include "raycaster.h"

// Define the map layout (1 represents a wall, 0 represents an empty space)
int map[MAP_WIDTH][MAP_HEIGHT] = {
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 1, 1, 1, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 1, 0, 0, 1, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1},
	{1, 1, 1, 1, 1, 1, 1, 1}
};

// Function to draw the walls and ground
void draw(SDL_Renderer *renderer, float cameraAngle);

// Function to run the game loop
void run_game()
{
	// Initialize SDL
	SDL_Init(SDL_INIT_VIDEO);
	
	// Create window and renderer
	SDL_Window *window = SDL_CreateWindow("Raycasting Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	// Initialize camera angle
	float cameraAngle = 0.0f;
	
	// Event handling
	SDL_Event e;
	int quit = 0;
	while (!quit)
	{
		while (SDL_PollEvent(&e))
		{
			// Check for quit event
			if (e.type == SDL_QUIT)
			{
				quit = 1;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				// Adjust camera angle based on arrow keys
				switch (e.key.keysym.sym)
				{
					case SDLK_LEFT:
						cameraAngle -= 5.0f;
						break;
					case SDLK_RIGHT:
						cameraAngle += 5.0f;
						break;
				}
			}
		}
		// Draw the scene
		draw(renderer, cameraAngle);
	}
	// Cleanup
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

// Function to draw the walls and ground using raycasting
void draw(SDL_Renderer *renderer, float cameraAngle)
{
	// Clear the screen
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	
	// Raycasting loop
	for (int x = 0; x < SCREEN_WIDTH; x++)
	{
		// Calculate the ray angle
		float rayAngle = (cameraAngle - 30.0f) + ((float)x / SCREEN_WIDTH) * 60.0f;
		
		// Calculate ray direction
		float rayDirX = cos(rayAngle * 3.14159 / 180.0);
		float rayDirY = sin(rayAngle * 3.14159 / 180.0);
		
		// Initial position of the ray
		float posX = 4.0f;
		float posY = 4.0f;
		
		// Calculate the distance to the walls using DDA algorithm
		while (map[(int)posX][(int)posY] == 0)
		{
			posX += rayDirX * 0.1f;
			posY += rayDirY * 0.1f;
		}
		
		// Calculate the height of the wall based on distance
		int wallHeight = SCREEN_HEIGHT / (posX - 4.0f);
		
		// Draw the wall segment
		SDL_SetRenderDrawColor(renderer, WALL_COLOR >> 16, (WALL_COLOR >> 8) & 0xFF, WALL_COLOR & 0xFF, 255);
		SDL_RenderDrawLine(renderer, x, SCREEN_HEIGHT / 2 - wallHeight / 2, x, SCREEN_HEIGHT / 2 + wallHeight / 2);
	}
	
	// Draw the ground and ceiling
	SDL_SetRenderDrawColor(renderer, GROUND_COLOR >> 16, (GROUND_COLOR >> 8) & 0xFF, GROUND_COLOR & 0xFF, 255);
	SDL_RenderDrawLine(renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2);
	
	// Present the renderer
	SDL_RenderPresent(renderer);
}
