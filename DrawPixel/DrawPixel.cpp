#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <string>
#include "Vector.h"
#include "Scaling.h"
#include "Translation.h"
#include "Rotation.h"
#include "Matrix.h"
using std::cin; using std::cout; using std::endl;
//Screen dimension constants
int screenWidth = 640;
int screenHeight = 480;
float scaleWidth = 2, scaleHeight = 2, punto;

SDL_Window* gWindow = NULL; //The window we'll be rendering to
SDL_Renderer* gRenderer = NULL; //The window renderer
Matrix matrix1(2, 2), matrix2(2,2), matrix3(2,2);
//Translation translate(3, 2);
//Rotation rotate(20);
//Scaling scale(3, 4);
Vector vector3, vector4,pendiente(0, 0), linea(0,0),vector1, vector2;



bool init(); //Starts up SDL and creates window
void close(); //Frees media and shuts down SDL
void pruebaDeMatrices(); void pendientesConVectores(Vector&, Vector&); void drawPixel(int x, int y);  void algoritmoDeBresenham();
void digitalDiferentialAnalyzer(Vector&, Vector&); void operacionesEntreVectores(Vector&, Vector&); void drawCircle(); void bezierCurve(Vector&,Vector&,Vector&,Vector&);
void operacionesConMatrices(Matrix&);  void MatrizTraslacion(Vector& x, Vector& y);  void MatrizEscalacion(Vector& x, Vector& y); void MatrizRotacion(Vector&, Vector&);

int main(int argc, char* args[]) {
	if (!init()) { //Start up SDL and create window
	
		printf("Failed to initialize!\n");
	} else {
		bool quit = false; //Main loop flag

	
		SDL_Event eventHandler; 	//Event handler
		//pruebaDeMatrices();

		while (!quit){ //While application is running
			
			while (SDL_PollEvent(&eventHandler) != 0) { //Handle events on queue
				if (eventHandler.type == SDL_QUIT) { //User requests quit
					quit = true;
				}
			}

			
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer); //Clear screen

			
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0x0, 0x00, 0xFF);
			
			
	
			for (int i = 0; i < screenWidth; i +=10) {
				SDL_RenderDrawLine(gRenderer, i,0, i, screenHeight); //dibujar línea horizontal a la mitad de la pantalla
			}


			for (int i = 0; i < screenWidth; i += 10) {
				SDL_RenderDrawLine(gRenderer, 0, i, screenWidth, i);
			//dibujar línea horizontal a la mitad de la pantalla
				
			}

			//cambiar el color a las lineas que se encuenrtan a la mitad de la pantalla
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xFF, 0x00, 0xFF);
			SDL_RenderDrawLine(gRenderer, screenWidth/2, 0, screenWidth/2, screenHeight);
			SDL_RenderDrawLine(gRenderer, 0, screenHeight/2, screenWidth, screenHeight/2);


			 //Dibujar linea vertical de la pantalla


			//Generar las divisiones del plano horizontal.
		
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);
			for (int i = 0; i < screenWidth; i += 10) {
				SDL_RenderDrawPoint(gRenderer, i,screenHeight/2);
				
			}

			//Generar las divisiones del plano vertical
			for (int i = 0; i < screenHeight; i += 10) {
				 
				SDL_RenderDrawPoint(gRenderer, screenWidth / 2, i);
			}
			//vector3 = translate * vector4;
			bezierCurve(vector1, vector2, vector3, vector4);
			//vector3.Print();
			//pruebaDeMatrices();
			//algoritmoDeBresenham();
			//drawCircle();
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
	bool active = true;
	printf("Introduce los valores de tu vector.\n");

	int a, b;
	//se ingresan los valores de a y b
	cin >> a >> b;
	printf("\n");

	//se le dan los valores al primer vector.
	Vector vector1(a, b);

	//el vector se imprime en consola
	vector1.Print();

	//Se dibuja el vector
	drawPixel(vector1.x, vector1.y);
	printf("\n\nAhora los valores de tu siguiente vector.\n");

	int c, d;

	//se ingresan los valores del segundo vector
	std::cin >> c >> d;

	//se le asignan al vector
	Vector vector2(c, d);

	//se imprime el segundo vectoren consola
	vector2.Print();
	printf("\n");

	//se dibuja el vector
	drawPixel(vector2.x, vector2.y);
	
	printf("Implementar en matriz?\nSi = 0\nNo = 1\n");
	int respuesta;
	cin >> respuesta;

	switch (respuesta) {
	case 0:
		matrix1.VectorInMatrix(vector1, vector2);
		matrix1.Print();
		operacionesConMatrices(matrix1);
		break;
		


	case 1:
		operacionesEntreVectores(vector1, vector2);

		break;
	}
	

		
}

void pendientesConVectores(Vector& vec1, Vector& vec2) {
	int X1 = vec1.x, X2 = vec2.x, Y1 = vec1.y, Y2 = vec2.y, x, y;

	y = Y1;
	x = X1;

	//printf("Ahora, calculare 'm' y 'c' para ti.\n");

	float m = (Y2 - Y1) / (X2 - X1);
	std::cout << "M: " << m << "\n";
	float c = y - m * x;
	std::cout << "C: " << c << "\n\n";

	if (abs(m) < 1) {
		for (int i = X1; i < X2; i++) {
			pendiente.setValues(x, y, 0);
			pendiente.Print();
			drawPixel(x, y);
			x = x + 1;
			y = (m * x) + c;


		}
	} else if (abs(m) > 1) {
		for (int i = Y1; i < Y2; i++) {
			x = (y - c) / m;
			y = y + 1;
			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();
		}
	} else
		std::cout << "estas mal.\n";

}

void digitalDiferentialAnalyzer(Vector& vec1, Vector& vec2) {
	int  X1 = vec1.x, X2 = vec2.x, Y1 = vec1.y, Y2 = vec2.y;
	float x, y;
	
	x = X1;
	y = Y1;

	int  incremento = 0;
	
	float xINCRMNT = 0.0f, yINCRMNT = 0.0f, dx = 0, dy = 0, DENO;

	//Calulos de dx y dy
	dx = abs(X2 - X1);
	dy = abs(Y2 - Y1);


	cout << "\n\nDX: " << dx << "\nDY: " << dy << "\n\n";


	//Obtencion del denominador
	//sí es mayor dx a dy, DENO es dx
	if (dx > dy) {
		DENO = dx;
	}

	//sí es mayor o igual dy a dx, DENO es dy
	if (dy >= dx) {
		DENO = dy;
	}

	//ahora podemos conseguir xINCRMNT y yINCRMNT
	xINCRMNT = dx / DENO;
	yINCRMNT = dy / DENO;


	//Impresion de valores anteriores
	cout << "Incremento en X: " << xINCRMNT << "\n";
	cout << "Incremento en Y: " << yINCRMNT << "\n";

	//empezamos un ciclo para dibujar la linea por medio de pixeles.

	while (incremento <= DENO) {
		drawPixel(x, y);
		linea.setValues(x, y, 0);
		linea.Print();
		x = x + xINCRMNT;
		y = y + yINCRMNT;
		incremento++;
	}

}

void operacionesEntreVectores(Vector & vec1, Vector & vec2)
{

	

	vec1.z = 1;
	vec2.z = 1;

	
	
	
	printf("Ahora, que quieres hacer con ellos?.\nSumar = 0\nRestar = 1\nProducto Cruz = 2\nProducto Punto = 3\nEscalar = 4\nDividir = 5\nPendiente =  6\n"
		"DDA = 7\nTrasladar = 8\nEscalar = 9\nRotacion = 10\n\n");
	int respuesta; cin >> respuesta;
	//Booleanos para controlar lo que el usuario realizara
	printf("\n");

	switch (respuesta) {
	case 0:
		vector3.Print();
		vector3 = vec1 + vec2;
		drawPixel(vector3.x, vector3.y);
		break;



	case 1:
		vector3 = vec1 - vec2;

		vector3.Print();
		drawPixel(vector3.x, vector3.y);
		break;


	case 2:
		vector3 = vec1.productoCruz(vec2);
		vector3.Print();
		drawPixel(vector3.x, vector3.y);
		break;



	case 3:
		punto = vec1.productoPunto(vec2);
		drawPixel(vector3.x, vector3.y);
		break;


	case 4:
		int numero;
		printf("Introduce el numero con el que quieres escalar los vectores.\n");
		cin >> numero;
		printf("Numero:%f ", numero);

		//multiplicar el vector por el numero
		vec1 = vec1 * numero;
		vec2 = vec2 * numero;

		//impresion de vectores
		vec1.Print();
		vec2.Print();

		//dibujar pixeles
		drawPixel(vec1.x, vec1.y);
		drawPixel(vec2.x, vec2.y);
		break;



	case 5:
		int numero2;
		printf("Introduce el numero con el que quieres dividir los vectores.\n");
		cin >> numero;
		printf("Numero:%f ", numero);

		//multiplicar el vector por el numero
		vec1 = vec1 / numero;
		vec2 = vec2 / numero;

		//impresion de vectores
		vec1.Print();
		vec2.Print();

		//dibujar pixeles
		drawPixel(vec1.x, vec1.y);
		drawPixel(vec2.x, vec2.y);
		break;


	case 6:
		pendientesConVectores(vec1, vec2);

		break;



	case 7:
		digitalDiferentialAnalyzer(vec1, vec2);

		break;


	case 8:
		printf("Para esto, es necesario utilizar una matriz de traslacion: \n 1 0 vx \n 0 1 vy \n 0 0 1\nNecesito que me ingreses los valores de vx y vy.\nVx: ");
		MatrizTraslacion(vec1, vec2);
		break;


	case 9:
		printf("Para esto, es necesario utilizar una matriz de escala: \n 1 0 sx \n 0 1 sy \n 0 0 1\nNecesito que me ingreses los valores de sx y sy.\nSx: ");

		MatrizEscalacion(vec1,vec2);
		break;



	case 10:
		printf("Para esto, es necesario utilizar una matriz de rotacion: \n cos(O) sin(O) 0 \n -sin(O) cos(O) 0 \n 0 0 1\nNecesito que me ingreses el angulo por el cual debe girar.\n"
			"\nAngulo: ");
		MatrizRotacion(vec1,vec2);
		
		break;
	}
}

void operacionesConMatrices(Matrix & matrx) {
	printf("Para realizar operaciones con otra Matriz, necesitas ingresar los valores de esta\n");
	matrix2.ModifyMatrix();
	matrix2.Print();
	
	printf("Que operacion quieres realizar con las matrices?\nSumar = 0\nRestar = 1\nMultiplicar = 2\nTransponer = 3\nSacar identidad = 4\n\n");
	int respuesta;
	cin >> respuesta;

	switch (respuesta) {
		
		case 0:
			matrix3 = matrx + matrix2;
			printf("Resultado:\n");
			matrix3.Print();
			break;



		case 1:
			matrix3 = matrx - matrix2;
			printf("Resultado:\n");
			matrix3.Print();
			break;



		case 2:
			matrix3 = matrx * matrix2;
			printf("Resultado:\n");
			matrix3.Print();
			break;



		case 3:
			matrx = matrx.transpose();
			printf("Resultado M1:\n");
			matrx.Print();
			matrix2.transpose();
			printf("\n\nResultado M2:\n");
			matrix2.Print();
			break;



		case 4:
			matrx = matrx.identity();
			printf("Resultado M1:\n");
			matrx.Print();
			matrix2.identity();
			printf("\n\nResultado M2:\n");
			matrix2.Print();
			break;
		
	}
	

	
}

void MatrizTraslacion(Vector& vec1, Vector& vec2)
{
	int vx = 0, vy = 0;
	cin >> vx;
	printf("VY: ");
	cin >> vy;

	Translation translating(vx, vy);

	//trasladando el vector 1
	printf("\nTrasladar vector 1\n");
	vector3 = translating * vec1;
	vector3.Print();
	drawPixel(vector3.x, vector3.y);

	//trasladando el vector 2
	printf("\nTrasladar vector2\n");
	vector4 = translating * vec2;
	vector4.Print();
	drawPixel(vector4.x, vector4.y);

	//drawPixel(vector3, vector4);


}

void MatrizEscalacion(Vector & vec1, Vector & vec2)
{
	int sx = 0, sy = 0;

	cin >> sx;
	printf("SY: ");
	cin >> sy;

	Scaling scale(sx, sy);
	scale.Print();

	//Escalando vector 1
	printf("\nEscalando vector 1\n");
	vector3 = scale * vec1;
	vector3.Print();
	drawPixel(vector3.x, vector3.y);

	//Escalando vector 2
	printf("\nTrasladar vector2\n");
	vector4 = scale * vec2;
	vector4.Print();
	drawPixel(vector4.x, vector4.y);
}

void MatrizRotacion(Vector &vec1, Vector &vec2)
{
	float angle = 0.0f;

	cin >> angle;
	
	Rotation rotating(angle);
	rotating.Print();

	//Escalando vector 1
	printf("\nAngulo en vector 1\n");
	vector3 = rotating * vec1;
	vector3.Print();
	drawPixel(vector3.x, vector3.y);

	//Escalando vector 2
	printf("\nAngulo en vector2\n");
	vector4 = rotating * vec2;
	vector4.Print();
	drawPixel(vector4.x, vector4.y);
}

void algoritmoDeBresenham() {
	int X1, X2, Y1, Y2, dx, dy, incremento, x, y;
	float P;
	printf("Introduce los valores de X1, X2, Y1, Y2: \nX1: ");
	cin >> X1;

	printf("Y1: "); cin >> Y1;
	printf("X2: "); cin >> X2;
	printf("Y2: "); cin >> Y2;

	x = X1; y = Y1; 

	dx = X2 - X1;
	cout << "\n\nDX: " << dx << "\n\n";

	dy = Y2 - Y1;

	cout << "\nDY: " <<dy << "\n\n";

	P = 2 * dy - dx;
	cout <<  "\nP: " << P << "\n\n";


	for (int i = 0; i <= dx; i++) {
		if (P < 0) {
			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();
			x = x + 1;
			y = y;
			P = P + 2 * dy;
			cout << P << endl;
		} else if(P >= 0){
			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();

			x = x + 1;
			y = y + 1;
			P = P + 2 * dy - 2 * dx;
			cout << P << endl;
		}
		
	}

}

void drawPixel(int x, int y) {
	SDL_RenderDrawPoint(gRenderer, screenWidth / 2 + x, screenHeight / 2 - y);
}

void drawCircle() {
	//centro del círculo
	int Xc, Yc;

	//pixeles, radio y parametro.
	int x, y, Radius, Perimeter;

	cout << "Introduce los valores del centro del circulo.\nXC: ";
	cin >> Xc;
	cout << "YC: ";
	cin >> Yc;

	cout << "Ahora introduce el valor del radio.\nRadio: ";
	cin >> Radius;

	x = 0;
	y = Radius;
	Perimeter = 1 - Radius;

	for (int i = 0; x <= y; i++) {
		drawPixel(x + Xc, y + Yc);
		if (Perimeter <= 0) {
			x = x + 1;
			y = y;
			Perimeter = Perimeter + 2 * x  +3;
		} else if (Perimeter > 0) {
			x = x + 1;
			y = y - 1;
			Perimeter = 2 *x - 2 * y + 5 + Perimeter;
		}

		drawPixel(x + Xc, -y + Yc);
		drawPixel(-x + Xc, y + Yc);
		drawPixel(-x + Xc, -y + Yc);
		drawPixel(y + Xc, x + Yc);
		drawPixel(y + Xc, -x + Yc);
		drawPixel(-y + Xc, x + Yc);
		drawPixel(-y + Xc, -x + Yc);
	}
}

void bezierCurve(Vector& vec1, Vector& vec2, Vector& vec3, Vector& vec4) {	
	cout << "Vector1 X y Y: "; cin >> vec1.x; cin >> vec1.y;
	cout << "Vector2 X y Y: "; cin >> vec2.x; cin >> vec2.y;
	cout << "Vector3 X y Y: "; cin >> vec3.x; cin >> vec3.y;
	cout << "Vector4 X y Y: "; cin >> vec4.x; cin >> vec4.y;

	//int t = 1;
	double x = 0.0, y = 0.0;
	Vector temp;

	for (double i = 0.0; i <= 1; i += 0.0001) {
		temp.x = pow(1 - i, 3) * vec1.x + (3 * i)*(pow(1 - i, 2) * vec2.x) + (3 * pow(i, 2))*(1 - i *vec3.x) + (pow(i, 3))*(vec4.x);
		temp.y = pow(1 - i, 3) * vec1.y + (3 * i)*(pow(1 - i, 2) * vec2.y) + (3 * pow(i, 2))*(1 - i *vec3.y) + (pow(i, 3))*(vec4.y);
		drawPixel(temp.x, temp.y);
	}

}
