#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "SDL2main.lib")
#pragma comment (lib,"opengl32.lib")
#pragma comment (lib,"Glu32.lib")

#include <SDL.h>
#include <SDL_opengl.h>
#include <GL\GLU.h>

#include <iostream>
#include <string>
#include <ctime>

#include "struct.h";
#include "grid.h"

using namespace std;

const float g_WindowWidth{ 500.0f };
const float g_WindowHeight{ 300.0f };
const std::string g_WindowTitle{ "Grid System" };
bool g_IsVSyncOn{ true };

SDL_Window* g_pWindow{ nullptr };
SDL_GLContext g_pContext;

Grid grid{ 30, 10 };

SDL_Event e;
bool quit;
Vector2Int mousePosition{-1, -1};

void Initialize();
void Update();
void Cleanup();
void QuitOnError();

void ReadInput();

void Draw();
void ClearBackground();

int main(int argc, char* args[])
{
	srand(unsigned int(time(nullptr)));

	Initialize();

	Update();

	Cleanup();

	return 0;
}

void Update()
{
	while (!quit)
	{
		Draw();
		SDL_GL_SwapWindow(g_pWindow);

		ReadInput();
	}
}

void ReadInput()
{
	while (SDL_PollEvent(&e) != 0)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			quit = true;
			break;

		case SDL_MOUSEBUTTONDOWN:
			SDL_GetMouseState(&mousePosition.X, &mousePosition.Y);
			grid.SelectCell(mousePosition);
			break;
		}
	}
}

void Draw()
{
	ClearBackground();

	grid.DrawGrid();
	if (grid.GetSelectedCell()) grid.FillCell(grid.GetSelectedCell());
}

void ClearBackground()
{
	glClearColor(185.0f / 255.0f, 211.0f / 255.0f, 238.0f / 255.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Initialize()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0) QuitOnError();

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);

	g_pWindow = SDL_CreateWindow(
		g_WindowTitle.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		int(g_WindowWidth),
		int(g_WindowHeight),
		SDL_WINDOW_OPENGL);

	if (g_pWindow == nullptr)
	{
		QuitOnError();
	}

	g_pContext = SDL_GL_CreateContext(g_pWindow);
	if (g_pContext == nullptr)
	{
		QuitOnError();
	}

	if (g_IsVSyncOn)
		if (SDL_GL_SetSwapInterval(1) < 0) QuitOnError();
		else
			SDL_GL_SetSwapInterval(0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Origin at top left of window
	gluOrtho2D(0, g_WindowWidth, g_WindowHeight, 0);

	glViewport(0, 0, int(g_WindowWidth), int(g_WindowHeight));

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void Cleanup()
{
	SDL_GL_DeleteContext(g_pContext);

	SDL_DestroyWindow(g_pWindow);
	g_pWindow = nullptr;

	SDL_Quit();
}

void QuitOnError()
{
	std::cout << "Error.";
	Cleanup();
	exit(-1);
}