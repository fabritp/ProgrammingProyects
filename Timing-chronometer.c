#include<stdio.h>
#include<assert.h>
#include<SDL_video.h>
#include<SDL_image.h>
#include<SDL_error.h>
#include<SDL_events.h>
#include<SDL_quit.h>
#include<SDL_rect.h>
#include<SDL_render.h>
#include<SDL_keycode.h>
#include<SDL_surface.h>
#include<SDL_timer.h>
#include<SDL_mouse.h>
#include<SDL_audio.h>
#include<SDL_mixer.h>

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

#define ASSERT_IN 1

enum screen {
	SCREEN_W = 292,
	SCREEN_H = 197
};

enum formats {
	BMP,
	PNG,
	JPG
};

#define CERO 0
#define UNO 19
#define DOS 38
#define TRES 57
#define CUATRO 76
#define CINCO 95
#define SEIS 114
#define SIETE 133
#define OCHO 152
#define NUEVE 171

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

char setup(void);
char load(void);
SDL_Texture *textureload(char[], char);
void gameloop(void);
void desc(void);
void draw(unsigned char, char);
void close(void);
void assert_s(char, unsigned int);

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

struct {
	SDL_Surface *loadimage;
	SDL_Texture *texture[4];
	SDL_Rect textureR;
	Mix_Chunk *buttonsound;
}Resources;

struct {						//Digitos separados, controlan la modificacion de la imagen de digitos
	unsigned char digit : 4;
}digitosfield[9];

SDL_Point mouse;

struct {
	SDL_Window *window;
	SDL_Renderer *render;
	SDL_Rect renderR;
	SDL_Event e;
}Screen;

struct {
	unsigned char *path;
}Directories[5];

int numero = 0, save = 0;
int save1 = 0, save2 = 0;

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

int main() {
	if (!setup()) {
		printf_s("No se pudo iniciar el programa, errores producidos: %s, %s, %s", SDL_GetError(), IMG_GetError(), Mix_GetError());
		SDL_Delay(10000);
	}
	else if (!load()) {
		printf_s("No se pudo cargar el programa, errores producidos: %s, %s, %s", SDL_GetError(), IMG_GetError(), Mix_GetError());
		SDL_Delay(10000);
	}
	else {
		gameloop();
	}

	close();

	return 0;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

char setup() {
	mouse.x = mouse.y = NULL;
	Resources.loadimage = Resources.texture[0] = Resources.texture[1] = Resources.texture[2] = Screen.window = Screen.render = NULL;
	Resources.textureR.x = Resources.textureR.y = Resources.textureR.w = Resources.textureR.h = Screen.renderR.x = Screen.renderR.y = Screen.renderR.w = Screen.renderR.h = NULL;
	digitosfield[0].digit = digitosfield[1].digit = digitosfield[2].digit = digitosfield[3].digit = digitosfield[4].digit = digitosfield[5].digit = digitosfield[6].digit = digitosfield[7].digit = digitosfield[8].digit = NULL;

	Directories[0].path = "cronometro.png";
	Directories[1].path = "play.png";
	Directories[2].path = "reset.png";
	Directories[3].path = "digit.png";
	Directories[4].path = "sound.wav";

	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		return 0;
	}
	else if (IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG) == NULL) {
		return 0;
	}
	else if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 14100) < 0) {
		return 0;
	}
	else {
		return 1;
	}
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

char load() {
	if ((Screen.window = SDL_CreateWindow("Crono 1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN)) == NULL) {
		return 0;
	}
	else if ((Screen.render = SDL_CreateRenderer(Screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
		return 0;
	}
	else {
		char i = 0;

		for (i; i < 4; i++) {
			if ((Resources.texture[i] = textureload(Directories[i].path, PNG)) == NULL) {
				return 0;
			}
		}

		if ((Resources.buttonsound = Mix_LoadWAV(Directories[i].path)) == NULL) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

SDL_Texture *textureload(char path[],char format) {
	SDL_Texture *newtexture = NULL;

	switch (format) {
	case BMP:
		if ((Resources.loadimage = SDL_LoadBMP(path)) == NULL) {
			return NULL;
		}
		break;
	case PNG:
		if ((Resources.loadimage = IMG_Load(path)) == NULL) {
			return NULL;
		}
		break;
	case JPG:
		if ((Resources.loadimage = IMG_Load(path)) == NULL) {
			return NULL;
		}
		break;
	default:
		return NULL;
		break;
	}

	if ((newtexture = SDL_CreateTextureFromSurface(Screen.render, Resources.loadimage)) == NULL) {
		return NULL;
	}
	else {
		return newtexture;
	}
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void gameloop() {
	unsigned int tcapturado = 0;
	char eventoactual = 1;
	char eventoanterior = 0;
	char play_pause = 0;
	SDL_Surface *digitimage2 = NULL;

	Resources.textureR.x = 0;
	Resources.textureR.y = 0;
	Resources.textureR.w = 38;
	Resources.textureR.h = 42;

	SDL_Rect clearlcd;
	clearlcd.x = 38;
	clearlcd.y = 27;
	clearlcd.w = 216;
	clearlcd.h = 42;
	SDL_Rect clearbutton1;
	clearbutton1.x = 41;
	clearbutton1.y = 108;
	clearbutton1.w = 38;
	clearbutton1.h = 42;
	SDL_Rect clearbutton2;
	clearbutton2.x = 92;
	clearbutton2.y = 108;
	clearbutton2.w = 38;
	clearbutton2.h = 42;

	Screen.renderR.x = 0;
	Screen.renderR.y = 0;
	Screen.renderR.w = SCREEN_W;
	Screen.renderR.h = SCREEN_H;
	SDL_RenderCopy(Screen.render, Resources.texture[0], NULL, &Screen.renderR);	//Dibuja el background

	while (1) {
		SDL_PollEvent(&Screen.e);

		if (Screen.e.type == SDL_QUIT) {
			break;
		}
		else {
			char i = 0;

			SDL_RenderCopy(Screen.render, Resources.texture[0], &clearlcd, &clearlcd);

			desc();														//Descompone el timer de SDL_GetTicks() en digitos con sistema sexagesimal 
			for (i; i < 9; i++) {												//Imprime los digitos en la pantalla

				switch (digitosfield[i].digit) {
				case 0:
					draw(CERO, i);
					break;
				case 1:
					draw(UNO, i);
					break;
				case 2:
					draw(DOS, i);
					break;
				case 3:
					draw(TRES, i);
					break;
				case 4:
					draw(CUATRO, i);
					break;
				case 5:
					draw(CINCO, i);
					break;
				case 6:
					draw(SEIS, i);
					break;
				case 7:
					draw(SIETE, i);
					break;
				case 8:
					draw(OCHO, i);
					break;
				case 9:
					draw(NUEVE, i);
					break;
				default:
					draw(CERO, i);
					break;
				}
			}

			if (eventoanterior != eventoactual) {																//Renderiza las imagenes de los botones una unica vez, actualizandolas en caso de un cambio de evento
				switch (eventoactual) {
				case 1:																							//Button play and reset
					SDL_RenderCopy(Screen.render, Resources.texture[0], &clearbutton1, &clearbutton1);
					SDL_RenderCopy(Screen.render, Resources.texture[0], &clearbutton2, &clearbutton2);
					Resources.textureR.x = 0;
					SDL_RenderCopy(Screen.render, Resources.texture[1], &Resources.textureR, &clearbutton1);
					SDL_RenderCopy(Screen.render, Resources.texture[2], &Resources.textureR, &clearbutton2);
					eventoanterior = eventoactual;
					break;
				case 2:																							//Button play
					SDL_RenderCopy(Screen.render, Resources.texture[0], &clearbutton1, &clearbutton1);
					Resources.textureR.x = 38;
					SDL_RenderCopy(Screen.render, Resources.texture[1], &Resources.textureR, &clearbutton1);
					eventoanterior = eventoactual;
					break;
				case 3:
					SDL_RenderCopy(Screen.render, Resources.texture[0], &clearbutton1, &clearbutton1);
					Resources.textureR.x = 76;
					SDL_RenderCopy(Screen.render, Resources.texture[1], &Resources.textureR, &clearbutton1);
					eventoanterior = eventoactual;
					break;
				case -2:																						//Button reset
					SDL_RenderCopy(Screen.render, Resources.texture[0], &clearbutton2, &clearbutton2);
					Resources.textureR.x = 38;
					SDL_RenderCopy(Screen.render, Resources.texture[2], &Resources.textureR, &clearbutton2);
					eventoanterior = eventoactual;
					break;
				case -3:
					SDL_RenderCopy(Screen.render, Resources.texture[0], &clearbutton2, &clearbutton2);
					Resources.textureR.x = 76;
					SDL_RenderCopy(Screen.render, Resources.texture[2], &Resources.textureR, &clearbutton2);
					eventoanterior = eventoactual;
					break;
				}
			}

			SDL_GetMouseState(&mouse.x, &mouse.y);						//Obtiene posicion del mouse

			if ((mouse.x >= clearbutton1.x) && (mouse.x <= (clearbutton1.x + clearbutton1.w)) && (mouse.y >= clearbutton1.y) && (mouse.y <= (clearbutton1.y + clearbutton1.h))) {		//Comprueba si el raton esta sobre el boton de play
				if (Screen.e.type == SDL_MOUSEBUTTONDOWN) {
					eventoactual = 3;
					Mix_PlayChannel(-1, Resources.buttonsound, 0);		//Reproduce el sonido del boton

					if (play_pause == 0) {								//Compara si el boton esta en play o pause
						play_pause = 1;
						tcapturado = SDL_GetTicks();					//Guarda el tiempo hasta que el boton sea presionado
					}
					else {
						play_pause = 0;
						save = numero;
					}
				}
				else {
					eventoactual = 2;
				}
			}
			else if ((mouse.x >= clearbutton2.x) && (mouse.x <= (clearbutton2.x + clearbutton2.w)) && (mouse.y >= clearbutton2.y) && (mouse.y <= (clearbutton2.y + clearbutton2.h))) {	//Comprueba si el raton esta sobre el boton de reset
				if (Screen.e.type == SDL_MOUSEBUTTONDOWN) {
					eventoactual = -3;
					Mix_PlayChannel(-1, Resources.buttonsound, 0);
					tcapturado = SDL_GetTicks();
					save = 0;
					play_pause = 1;
				}
				else {
					eventoactual = -2;
				}
			}
			else if ((eventoactual == 2 || eventoactual == -2) && ((mouse.x<clearbutton1.x || mouse.x>(clearbutton1.x + clearbutton1.w)) || (mouse.y<clearbutton1.y || mouse.y>(clearbutton1.y + clearbutton1.h))) && ((mouse.x<clearbutton2.x || mouse.x>(clearbutton2.x + clearbutton2.w)) || (mouse.y<clearbutton2.y || mouse.y>(clearbutton2.y + clearbutton2.h)))) {	//Compara si recientemente se dibujo el boton 2, y si el mouse se encuentra fuera de los limites de los botones play y reset para volver a dibujar el boton default respectivo de play y reset
				eventoactual = 1;
			}

			if (play_pause == 1) {
				numero = save + (SDL_GetTicks() - tcapturado);		//Guarda numeros desde el 0 en "numero" solo si el boton esta en play y los acumula para que cuando se presione pause, tcapturado reinicie pero la variable numero no
			}

			SDL_RenderPresent(Screen.render);
		}
	}
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void desc() {
	int num = 0;
	int cont = 0;
	char dig = 0;

	while (cont < 9) {
		digitosfield[cont].digit = 0;
		cont++;
	}
	cont = 0;

	if ((numero - (save1 + 60000)) >= 0 && (numero - (save1 + 60000)) < 1000) {				//Rango 0 a 999 para ejecucion correcta de SDL_GetTicks()
		if ((numero - (save2 + 6060000)) >= 0 && (numero - (save2 + 6060000)) < 1000) {		//Funaciona hasta las 72 horas
			numero += 3940000;
			save += 3940000;
			save1 = numero;
			save2 = numero;
		}
		else {
			numero += 40000;
			save += 40000;
			save1 = numero;
		}
	}
	num = numero;

	while (num != 0) {
		while ((num % (int)pow(10.0, (double)(dig + 1))) != 0) {
			num -= (int)pow(10.0, (double)dig);
			cont++;
		}

		digitosfield[dig].digit = cont;
		cont = 0;
		dig++;
	}

	return;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void draw(unsigned char def, char digito) {
	SDL_Rect digitR;
	Screen.renderR.w = Resources.loadimage->w / 10;
	Screen.renderR.h = Resources.loadimage->h;
	digitR.x = def;
	digitR.y = 0;
	digitR.w = 19;
	digitR.h = 42;

	switch (digito) {
	case 0:
		Screen.renderR.x = 235;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 1:
		Screen.renderR.x = 213;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 2:
		Screen.renderR.x = 191;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 3:
		Screen.renderR.x = 162;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 4:
		Screen.renderR.x = 140;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 5:
		Screen.renderR.x = 111;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 6:
		Screen.renderR.x = 89;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 7:
		Screen.renderR.x = 60;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	case 8:
		Screen.renderR.x = 38;
		Screen.renderR.y = 27;
		SDL_RenderCopy(Screen.render, Resources.texture[3], &digitR, &Screen.renderR);
		break;
	}
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

void close() {
	SDL_FreeSurface(Resources.loadimage);
	SDL_DestroyTexture(Resources.texture[0]);
	SDL_DestroyTexture(Resources.texture[1]);
	SDL_DestroyTexture(Resources.texture[2]);
	SDL_DestroyTexture(Resources.texture[3]);
	Mix_FreeChunk(Resources.buttonsound);
	SDL_DestroyWindow(Screen.window);
	SDL_DestroyRenderer(Screen.render);
	Mix_CloseAudio();
	SDL_Quit();
	IMG_Quit();
	Mix_Quit();

	return;
}

//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||||

//Definicion funcion "assert_s" creada por FabricioT, hace estatica a assert para su manejo estatico de aserciones, pudiendo activarlo durante lla compilacion y desactivarlo en el lanzamiento de la aplicacion

void assert_s(char expression, unsigned int line) {
	if (ASSERT_IN == 1) {
		if (expression == 0) {
			_wassert(_CRT_WIDE("Logic error"), _CRT_WIDE("Sourc.c"), (line));
			assert(0);
		}
		else {
			return;
		}
	}
	else {
		return;
	}
}