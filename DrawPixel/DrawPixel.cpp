#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Vector.h"
#include "Matrix.h"

//Screen dimension constants
int screenWidth = 640;
int screenHeight = 480;
float scaleWidth = 2, scaleHeight = 2;
SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Renderer* gRenderer = NULL; //The window renderer

bool init(); //Starts up SDL and creates window
void close(); //Frees media and shuts down SDL
void pruebaDeMatrices();


int main(int argc, char* args[]) {
	
	pruebaDeMatrices();

	if (!init()) { //Start up SDL and create window
	
		printf("Failed to initialize!\n");
	} else {
		bool quit = false; //Main loop flag

	
		SDL_Event eventHandler; 	//Event handler
		
		while (!quit){ //While application is running
			
			while (SDL_PollEvent(&eventHandler) != 0) { //Handle events on queue
				if (eventHandler.type == SDL_QUIT) { //User requests quit
					quit = true;
				}
			}

			
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			SDL_RenderClear(gRenderer); //Clear screen

			
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x00, 0x00, 0xFF);
			
			SDL_RenderDrawLine(gRenderer, 0, screenHeight / 2, screenWidth, screenHeight / 2); //dibujar línea horizontal a la mitad de la pantalla
			SDL_RenderDrawLine(gRenderer, screenWidth/2, 0, screenWidth/2, screenHeight); //Dibujar linea vertical de la pantalla


			//Generar las divisiones del plano horizontal.
		
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			for (int i = 0; i < screenWidth; i += 5) {
				SDL_RenderDrawPoint(gRenderer, i,screenHeight/2);
				
			}

			//Generar las divisiones del plano vertical
			for (int i = 0; i < screenHeight; i += 5) {
				 
				SDL_RenderDrawPoint(gRenderer, screenWidth / 2, i);
			}


			SDL_RenderPresent(gRenderer); //Update screen
		}
	}
	//Free resources and close SDL
	close();

	return 0;
}

bool init() {
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else {
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN);
		if (gWindow == NULL) {
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else {
			//Create renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			if (gRenderer == NULL) {
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else {
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);


			}
		}
	}

	return success;
}

void close() {
	//Destroy window	
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	SDL_Quit();
}

void pruebaDeMatrices() {
	Matrix m1(3, 3), m2(3, 3), m3(0,0), m4(0, 0);
	
	m1.ModifyMatrix(0);
	m1.Print();
	m2.ModifyMatrix(0);
	m2.Print();
	m3 = m1 + m2;
	m3.Print();

	//m3 = m1.transpose();
	//m3.Print();

	
	/*m3 = m1 + m2;
	m3.Print();*/
	/*
	m4 = m1 * m2;
	m4.Print();*/
}