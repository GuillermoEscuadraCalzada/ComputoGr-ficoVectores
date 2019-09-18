#include "pch.h"
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <vector>
#include <string>
#include "Vector.h"
#include "Scaling.h"
#include "Translation.h"
#include "Rotation.h"
#include "Matrix.h"
using std::cin; using std::cout; using std::endl; using std::vector;
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
void pruebaDeMatrices(); 
void drawLine(int, int, int, int);
void pendientesConVectores(Vector&, Vector&);
void eleccionDeDimensiones();
void drawPixel(int x, int y); 
void algoritmoDeBresenham(int, int);
void algoritmoDeBresenham();
void algoritmoDeBresenham(Vector&, Vector&);
void operaciones();
void digitalDiferentialAnalyzer(Vector&, Vector&); 
void operacionesEntreVectores(Vector&, Vector&, Vector&, Vector&);
void drawCircle(); 
void bezierCurve(Vector&,Vector&,Vector&,Vector&);
void operacionesConMatrices(Matrix&);  
void MatrizTraslacion(Vector& x, Vector& y);  
void MatrizEscalacion(Vector& x, Vector& y);
void MatrizEscalacion(Vector& x, Vector& y,Vector&);
void MatrizRotacion(Vector&, Vector&);
void MatrizRotacion(Vector&, Vector&, Vector &);
void bezierCurveNDimensions(vector<Vector>);
int Factorial(int);


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

			Vector examen1(10, 10), examen2(-10, 20), examen3(-20, -20);
			operaciones();

			

			SDL_RenderPresent(gRenderer); //Update screen
		}
	}
	//Free resources and close SDL
	//algoritmoDeBresenham(examen2, examen1);
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
	
	printf("Implementar en matriz?\nSi = 1\nNo = 2\n");
	int respuesta;
	cin >> respuesta;

	switch (respuesta) {

	case 1:
		matrix1.VectorInMatrix(vector1, vector2);
		matrix1.Print();
		operacionesConMatrices(matrix1);
		break;

	case 2:
		operacionesEntreVectores(vector1, vector2, vector3, vector4);

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


/*==================================================================================
  ===================Digiyal Diferential Analyzer===================================
  ==================================================================================*/

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

/*==================================================================================
  =========================Operaciones==============================================
  ==================================================================================*/

void operacionesEntreVectores(Vector & vec1, Vector & vec2, Vector& vec3, Vector& vec4)
{	vec1.z = 1;
	vec2.z = 1;

	printf("Ahora, que quieres hacer con ellos?.\nSumar = 0\nRestar = 1\nProducto Cruz = 2\nProducto Punto = 3\nEscalar = 4\nDividir = 5\nPendiente =  6\n"
		"DDA = 7\nTrasladar = 8\nEscalar = 9\nRotacion = 10\nCurva de Bezier = 11\nCurva de Bezier 'n' dimensiones = 12\n\n");
	int respuesta; cin >> respuesta;
	//Booleanos para controlar lo que el usuario realizara
	printf("\n");

	switch (respuesta) {

	case 0: //Suma
		vector3.Print();
		vector3 = vec1 + vec2;
		drawPixel(vector3.x, vector3.y);
		break;



	case 1: //Resta
		vector3 = vec1 - vec2;

		vector3.Print();
		drawPixel(vector3.x, vector3.y);
		break;


	case 2: //Multiplicacion
		vector3 = vec1.productoCruz(vec2);
		vector3.Print();
		drawPixel(vector3.x, vector3.y);
		break;



	case 3: //Producto Punto
		punto = vec1.productoPunto(vec2);
		drawPixel(vector3.x, vector3.y);
		break;


	case 4: //Escala 
		int numero;
		printf("Introduce el numero con el que quieres escalar los vectores.\n");
		cin >> numero;
		printf("Numero:%i ", numero);

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



	case 5: //Division  entre vectores
		int numero2;
		printf("Introduce el numero con el que quieres dividir los vectores.\n");
		cin >> numero;
		printf("Numero:%i ", numero);

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


	case 6: //Pendiente con vectores
		pendientesConVectores(vec1, vec2);

		break;



	case 7: //DDA 
		digitalDiferentialAnalyzer(vec1, vec2);

		break;


	case 8: //Matriz traslación
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

		
	case 11: //Curva de Bezier
		printf("\nIntroduce los valores del vector 3 y vector 4:\n");
		printf("Vector3:\n"); cin >> vec3.x >> vec3.y; 
		printf("Vector4:\n"); cin >> vec4.x >> vec4.y;
		bezierCurve(vec1, vec2, vec3, vec4);
		
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


/*==================================================================================
  =========================Matriz de traslacion=====================================
  ==================================================================================*/

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


/*==================================================================================
  =========================Matriz de escalacion=====================================
  ==================================================================================*/

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



void MatrizEscalacion(Vector & vec1, Vector & vec2, Vector& vec3)
{
	int sx = 0, sy = 0;

	printf("\nIngresa los valores de escalamiento.\nSX: ");
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

	//Escalando vector 3
	printf("\nTrasladar vector3\n");
	vector1 = scale * vec2;
	vector1.Print();
	drawPixel(vector1.x, vector1.y);

	algoritmoDeBresenham(vector3, vector4);
	algoritmoDeBresenham(vector4, vector2);
	algoritmoDeBresenham(vector3, vector2);
}

/*==================================================================================
  =========================Matriz de rotacion===================================
  ==================================================================================*/

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



void MatrizRotacion(Vector &vec1, Vector &vec2, Vector &vec3)
{
	float angle = 0.0f;
	printf("Ingresa el angulo de rotacion: ");
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

	//Escalando vector 2
	printf("\nAngulo en vector3\n");
	vector2 = rotating * vec2;
	vector2.Print();
	drawPixel(vector2.x, vector2.y);

	MatrizEscalacion(vector3, vector4, vector2);


}



/*==================================================================================
  =========================algoritmo de brezengam===================================
  ==================================================================================*/
  
void algoritmoDeBresenham() {
	float X1, X2, Y1, Y2, dx, dy, incremento, X, Y;
	float P;
	printf("Introduce los valores de X1, X2, Y1, Y2: \nX1: ");
	cin >> X1;
	printf("Y1: "); cin >> Y1;
	printf("X2: "); cin >> X2;
	printf("Y2: "); cin >> Y2;

	X = X1; Y = Y1; 
	dx = X2 - X1;
	cout << "\n\nDX: " << dx << "\n\n";

	dy = Y2 - Y1;
	cout << "\nDY: " <<dy << "\n\n";

	P = 2 * dy - dx;
	cout <<  "\nP: " << P << "\n\n";

	if (dx > dy) {
		for (int i = 0; i <= dx; i++) {
			drawPixel(X, Y);
			pendiente.setValues(X, Y, 0);
			pendiente.Print();
			X += 1;
			if (P < 0) {
				Y = Y;
				P = P + 2 * dy;
				cout << P << endl;
			} else if(P >= 0){				
				Y = Y + 1;
				P = P + 2*(dy -  dx);
				cout << P << endl;
			}
		}
	} else {
		for (int i = 0; i <= dy; i++) {
			drawPixel(X, Y);
			pendiente.setValues(X, Y, 0);
			pendiente.Print();
			Y += 1;
			if (P < 0) {
				P = P + 2 * dx;
			}
			else {
				X = X + 1;
				P = P + 2 * (dx - dy);
			}
		}
	}

}

void algoritmoDeBresenham(Vector &vec1, Vector &vec2) {


	printf("Se uniran los siguientes puntos X1, X2, Y1, Y2:\n ");
	cout << "X1: " << vec1.x << "\nY1: " << vec1.y << "\nX2: " << vec2.x << "\nY2: " << vec2.y << "\n";
	
	float X1 = vec1.x; 
	float Y1 = vec1.y; 

	float X2 = vec2.x;
	float Y2 = vec2.y;

	float x = X1; 
	float y = Y1;

	int dx = X2 - X1;
	cout << "\n\nDX: " << dx << "\n\n";

	int dy = Y2 - Y1;

	cout << "\nDY: " << dy << "\n\n";

	float P = (2 * dy) - dx;
	cout << "\nP: " << P << "\n\n";


	if (dx > dy) {
		for (int i = 0; i <= dx; i++) {

			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();
			x += 1;

			if (P < 0) {		
				P = P + 2 * dy;
				cout << P << endl;
			}
			else{

				y +=1;
				P = P + 2 * dy - 2 * dx;
				cout << P << endl;
			}
		}
	}
	else {
		
		for (int i = 0; i <= dy; i++) {
			drawPixel(x, y);
			pendiente.setValues(x, y, 0);
			pendiente.Print();
			y += 1;

			if (P < 0) {
			
				P = P + 2 * dx;
				cout << P << "\n";
			}
			else {
				x += 1;
				P = P + (2 * (dx - dy));
				cout << P << "\n";
			}

		}
	}

}



void drawPixel(int x, int y) {
	SDL_RenderDrawPoint(gRenderer, screenWidth / 2 + x, screenHeight / 2 - y);
}


//El usuario escribe la ubicación del círculo en la pantalla, después introduce el valor del radio que quiere que se obtenga y se imprime cada valor.
void drawCircle() {
	//centro del círculo
	int Xc, Yc;

	//pixeles, radio y parametro.
	int x, y, Radius, Perimeter;

	cout << "Introduce la ubicacion del centro del circulo.\nXC: ";
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

/*==================================================================================
  =========================Curva de bezier, tres y N dimensiones====================
  ==================================================================================*/

void bezierCurve(Vector& vec1, Vector& vec2, Vector& vec3, Vector& vec4) {	

	vec1.x += screenWidth / 2;
	vec2.x += screenWidth / 2;
	vec3.x += screenWidth / 2;
	vec4.x += screenWidth / 2;

	vec1.y += -vec1.y + screenWidth / 2;
	vec2.y += -vec2.y + screenWidth / 2;
	vec3.y += -vec3.y + screenWidth / 2;
	vec4.y += -vec4.y + screenWidth / 2;

	//int t = 1;
	double x = 0.0, y = 0.0;
	Vector temp;

	for (double i = 0.0; i <= 1; i += 0.0001) {
		temp.x = pow(1 - i, 3) * vec1.x + (3 * i)*(pow(1 - i, 2) * vec2.x) + (3 * pow(i, 2))*(1 - i *vec3.x) + (pow(i, 3))*(vec4.x);
		temp.y = pow(1 - i, 3) * vec1.y + (3 * i)*(pow(1 - i, 2) * vec2.y) + (3 * pow(i, 2))*(1 - i *vec3.y) + (pow(i, 3))*(vec4.y);
		temp.Print();
		drawPixel(temp.x, temp.y);
	}
	

}

/*
	Curva de bezier con "n" dimensiones, esta función le pedirá al usuario el número de dimensiones que quiera usar.
*/
void eleccionDeDimensiones() {
	vector<Vector> vectorContainer;
	int dimensiones, x, y;
	printf("\nDime el numero de vectores que quieres utilizar.\n");
	cin >> dimensiones;
	printf("Las dimensiones se usaran para el numero de vectores que se necesitan para la curva de bezier. \nIntroduce los valores de X y Y de cada vector.\n\n");

	for (int i = 0; i != dimensiones; i++) {
		cout << "Vector " << i << " \nX: ";
		cin>> x;
		printf("Y: "); 
		cin >> y;
		Vector vectorGenerico(x ,y);
		vectorContainer.push_back(vectorGenerico);	
	}

	bezierCurveNDimensions(vectorContainer);

}

/*Se dibuja una curva de bezier usando el numero de dimensiones que el usuario eliga. 
	@param contenedor de Vectores
	@return curva de Bezier, N dimensiones.
*/
void bezierCurveNDimensions(vector<Vector> vectCont)
{

	std::vector<Vector> ::iterator containerIt = vectCont.begin();
	for (containerIt; containerIt != vectCont.end(); containerIt++) {
		cout << "Vector(" << containerIt->x << ", " << containerIt->y << ")\n";
	}

	int n = vectCont.size() - 1;
	Vector container_Draw;

	for (double  t= 0; t <= 1; t += 0.000001) {

		container_Draw = Vector(0, 0);

		for (int k = 0; k <= n; k++) {
			int b = Factorial(n) / (Factorial(k) * (Factorial(n - k)));
			container_Draw = container_Draw + (vectCont[k] * b * pow(t, k) * pow(1 - t, k - 1));
		}
		drawPixel(container_Draw.x, container_Draw.y);
	}

	
}

int Factorial(int numero)
{
	if (numero <= 1)
		return 1;
	else
		return numero * Factorial(numero - 1);
}

void operaciones() {
	printf("Que quieres utilizar?\nVectores y Matrices: 1\nNumeros:2\nCurva de Bezier 'n' dimensiones = 3\n\n");
	int numero;
	cin >> numero;
	switch (numero) {
	case 1:
		pruebaDeMatrices();
		break;


	case 2:
		printf("\nAhora elige lo que quieras realizar:\nCirulo: 1\n Algoritmo de Bresenham: 2\n");
		cin >> numero;

		switch (numero) {
		case 1:
			drawCircle();
			break;


		case 2:
			algoritmoDeBresenham();
			break;


		}
		break;
	
			
			
	case 3:
		eleccionDeDimensiones();
		break;
	
	}
}

void drawLine(int x1, int x2, int y1, int y2) {

	SDL_RenderDrawLine(gRenderer, x1, y1, x2, y2);
}