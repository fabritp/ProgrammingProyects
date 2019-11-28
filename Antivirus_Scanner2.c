#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif

#include<stdio.h>
#include<SDL.h>
#include<SDL_image.h>
#include<SDL_ttf.h>

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

#define SCREEN_W 288
#define SCREEN_H 512

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

char inicio(void);
char load(void);
SDL_Texture* Loadpath(unsigned char[]);
void gameloop(void);
void charge(SDL_Rect, unsigned int);
SDL_Texture* loadfont(char, char[], unsigned char, unsigned char, unsigned char);
void close(void);

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

struct{
  SDL_Window* window;
  SDL_Renderer* render;
  SDL_Rect renderR;
  SDL_DisplayMode display;
  SDL_Event e;
}Screen;

struct{
  SDL_Surface* loadimage;
}Surfaces[11];

struct{
  SDL_Texture* loadtexture;
}Textures[11];

struct{
  unsigned char* path;
}Directories[11];

struct {
	SDL_Rect coords;
}Rects[8];

struct {
	SDL_Texture* parcheT;
	SDL_Rect parcheR;
}Parche;

struct {
	SDL_Surface* surface[4];
	SDL_Texture* fontT[4];
	SDL_Rect fontR[4];
	TTF_Font* font;
}Fonts;

char i = 0;
double degrees = 51.5;

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

int SDL_main(int argc, char *argv[]) {
	if (!inicio()) {
		SDL_Log("No se pudo iniciar el programa");
    printf("No se pudo iniciar el programa");
    SDL_Delay(3000);
	}
	else if (!load()) {
		SDL_Log("No se pudo cargar el programa");
    printf("No se pudo iniciar el programa");
    SDL_Delay(3000);
	}
	else {
		gameloop();
	}

	close();

	return 0;
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

char inicio(){
	Screen.window = NULL; Screen.render = NULL;
	Parche.parcheT = NULL; Parche.parcheR.x = Parche.parcheR.y = Parche.parcheR.w = Parche.parcheR.h = 0;
	Screen.renderR.x = Screen.renderR.y = Screen.renderR.w = Screen.renderR.h = 0;
	Fonts.fontT[0] = Fonts.fontT[1] = Fonts.fontT[2] = Fonts.fontT[3] = NULL;
	//Inicializacion de variables globales
	while (i < 8) {
		Rects[i].coords.x = 0;
		Rects[i].coords.y = 0;
		Rects[i].coords.w = 0;
		Rects[i].coords.h = 0;
		i++;
	}
	i = 0;
	while (i < 11) {
		Surfaces[i].loadimage = NULL;
		Textures[i].loadtexture = NULL;
		i++;
    }
	//Inicio Path:
	Directories[0].path = "Virus_Escaner_SetupScreen.png";
	//Home Path:
	Directories[1].path = "Virus_Home_Background.png";
	Directories[2].path = "Escanear_Button1.png";
	Directories[3].path = "Escanear_Button2.png";
	Directories[4].path = "Bien_icon.png";
	Directories[5].path = "Mal_icon.png";
	//Cuarentena Path:
	Directories[6].path = "Virus_Cuarentena_Background.png";
	Directories[7].path = "Barra_eliminar_button.png";
	//Charge icon:
	Directories[8].path = "Charge_icon.png";
	//Screen buttons:
	Directories[9].path = "Home_button.png";
	Directories[10].path = "Cuarentena_button.png";

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return 0;
	}
	else if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
		return 0;
	}
	else if (TTF_Init() < 0) {
		return 0;
	}
	else {
		return 1;
	}
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

char load() {
	if ((Screen.window = SDL_CreateWindow("Antivirus Escaner", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN)) == NULL) {
		return 0;
	}
	else if ((Screen.render = SDL_CreateRenderer(Screen.window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC)) == NULL) {
		return 0;
	}
	else {
		i = 0;

		while (i < 11) {
			if ((Textures[i].loadtexture = Loadpath(Directories[i].path)) == NULL) {
				return 0;
			}
			i++;
		}

		if ((Fonts.font = TTF_OpenFont("Impact.ttf", 12)) == NULL) {
			return 0;
		}
		else if ((Fonts.fontT[0] = loadfont(0, "Analizando dispositivo...", 255, 255, 255)) == NULL) {
			return 0;
		}
		else if ((Fonts.fontT[1] = loadfont(1, "Se registr� la amenaza satisfactoriamente", 0, 255, 0)) == NULL) {
			return 0;
		}
		else if ((Fonts.fontT[2] = loadfont(2, "No se encontr� ninguna amenaza", 255, 0, 0)) == NULL) {
			return 0;
		}
		else {
			return 1;
		}
	}
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

SDL_Texture* Loadpath(unsigned char path[]) {
	SDL_Texture* newtexture = NULL;

	if ((Surfaces[i].loadimage = IMG_Load(path)) == NULL) {
		return NULL;
	}
	else if ((newtexture = SDL_CreateTextureFromSurface(Screen.render, Surfaces[i].loadimage)) == NULL) {
		return NULL;
	}
	else {
		return newtexture;
	}
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

void gameloop() {
	FILE* file = NULL;
    char p = 0;
	i = 0;
	char filenum = 0;
	unsigned char filenames[63];
	char SCREEN = 1;
	char ischarging = 0;
	unsigned int frames = 0;
	char touchonbar = 0;
	SDL_Point fingercoords;
	fingercoords.x = 0; fingercoords.y = 0;

	Screen.renderR.x = 0;
	Screen.renderR.y = 0;
	Screen.renderR.w = SCREEN_W;
	Screen.renderR.h = SCREEN_H;

	//"Virus_Escaner_SetupScreen.png" coords
	Rects[0].coords.x = 0;
	Rects[0].coords.y = 0;
	Rects[0].coords.w = SCREEN_W;
	Rects[0].coords.h = SCREEN_H;
	//"Virus_Home_Background.png" coords
	Rects[1].coords.x = 0;
	Rects[1].coords.y = 0;
	Rects[1].coords.w = SCREEN_W;
	Rects[1].coords.h = SCREEN_H;
	//"Escanear_Button1.png" coords
	Rects[2].coords.x = 63;
	Rects[2].coords.y = 102;
	Rects[2].coords.w = Surfaces[2].loadimage->w;
	Rects[2].coords.h = Surfaces[2].loadimage->h;
	//"Escanear_Button2.png" coords
	Rects[3].coords.x = Rects[2].coords.x;
	Rects[3].coords.y = Rects[2].coords.y;
	Rects[3].coords.w = Surfaces[3].loadimage->w;
	Rects[3].coords.h = Surfaces[3].loadimage->h;
	//"Bien_icon.png" coords
	Rects[4].coords.x = 63;
	Rects[4].coords.y = 282;
	Rects[4].coords.w = Surfaces[4].loadimage->w;
	Rects[4].coords.h = Surfaces[4].loadimage->h;
	//"Mal_icon.png" coords
	Rects[5].coords.x = Rects[4].coords.x;
	Rects[5].coords.y = Rects[4].coords.y;
	Rects[5].coords.w = Surfaces[5].loadimage->w;
	Rects[5].coords.h = Surfaces[5].loadimage->h;
	//"Virus_Cuarentena_Background.png" coords
	Rects[6].coords.x = 0;
	Rects[6].coords.y = 0;
	Rects[6].coords.w = Surfaces[6].loadimage->w;
	Rects[6].coords.h = Surfaces[6].loadimage->h;
	//"Barra_eliminar_button.png" coords
	Rects[7].coords.x = 22;
	Rects[7].coords.y = 52;
	Rects[7].coords.w = Surfaces[7].loadimage->w;
	Rects[7].coords.h = Surfaces[7].loadimage->h;
	//"Charge_icon.png" coords
	Rects[8].coords.x = 132;
	Rects[8].coords.y = 352;
	Rects[8].coords.w = Surfaces[8].loadimage->w;
	Rects[8].coords.h = Surfaces[8].loadimage->h;
	//"Home_button.png" coords
	Rects[9].coords.x = 8;
	Rects[9].coords.y = 477;
	Rects[9].coords.w = Surfaces[9].loadimage->w;
	Rects[9].coords.h = Surfaces[9].loadimage->h;
	//"Cuarentena_button.png" coords
	Rects[10].coords.x = 63;
	Rects[10].coords.y = 477;
	Rects[10].coords.w = Surfaces[10].loadimage->w;
	Rects[10].coords.h = Surfaces[10].loadimage->h;
	//Text coords
	//Text "Analizando dispositivo..."
	Fonts.fontR[0].x = 86;
	Fonts.fontR[0].y = 282;
	Fonts.fontR[0].w = Fonts.surface[0]->w;
	Fonts.fontR[0].h = Fonts.surface[0]->h;
	//Text "Se registr� la amenaza satisfactoriamente"
	Fonts.fontR[1].x = Fonts.fontR[0].x;
	Fonts.fontR[1].y = Fonts.fontR[0].y;
	Fonts.fontR[1].w = Fonts.surface[1]->w;
	Fonts.fontR[1].h = Fonts.surface[1]->h;
	//Text "No se encontr� ninguna amenaza"
	Fonts.fontR[2].x = Fonts.fontR[0].x;
	Fonts.fontR[2].y = Fonts.fontR[0].y;
	Fonts.fontR[2].w = Fonts.surface[2]->w;
	Fonts.fontR[2].h = Fonts.surface[2]->h;
	//Setup parche coords form the initialize image
	SDL_RenderCopy(Screen.render, Textures[0].loadtexture, &Rects[0].coords, &Screen.renderR);
	Parche.parcheT = Textures[0].loadtexture;
	Parche.parcheR.x = Rects[8].coords.x;
	Parche.parcheR.y = Rects[8].coords.y;
	Parche.parcheR.w = Rects[8].coords.w;
	Parche.parcheR.h = Rects[8].coords.h;

	for (frames=0; frames <= 6000; frames++) {
		SDL_RenderCopy(Screen.render, Parche.parcheT, &Parche.parcheR, &Parche.parcheR);

		charge(Rects[8].coords, frames);
	}
	frames = 0;

	while (SCREEN != 0) {
		switch (SCREEN) {
		//Home Page
		case 1:
			Parche.parcheT = Textures[1].loadtexture;
			//Set charge icon into a home page
			Rects[8].coords.x = 63;
			Rects[8].coords.y = 282;
			Parche.parcheR.x = Rects[8].coords.x;
			Parche.parcheR.y = Rects[8].coords.y;
			Parche.parcheR.w = Rects[8].coords.w + (Fonts.fontR[1].x - Rects[8].coords.x) + Fonts.fontR[1].w;
			Parche.parcheR.h = Rects[8].coords.h;

			//Draw background home image
			SDL_RenderCopy(Screen.render, Textures[1].loadtexture, NULL, &Screen.renderR);
			//Draw home button
			SDL_RenderCopy(Screen.render, Textures[9].loadtexture, NULL, &Rects[9].coords);
			//Draw cuarentena button
			SDL_RenderCopy(Screen.render, Textures[10].loadtexture, NULL, &Rects[10].coords);

			while (1) {
				if (SDL_PollEvent(&Screen.e) == SDL_QUIT) {
					SCREEN = 0;
					break;
				}
				else {//Posible error  de boton mantenido presionado
					SDL_GetMouseState(&fingercoords.x, &fingercoords.y);

					if (fingercoords.x >= Rects[10].coords.x&&fingercoords.x <= (Rects[10].coords.x+Rects[10].coords.w)&&fingercoords.y >= Rects[10].coords.y&&fingercoords.y <= (Rects[10].coords.y+Rects[10].coords.h)&&Screen.e.type == SDL_MOUSEBUTTONDOWN) {
						SCREEN = 2;
						break;
					}
					else if (fingercoords.x >= Rects[2].coords.x&&fingercoords.x <= (Rects[2].coords.x+Rects[2].coords.w)&&fingercoords.y >= Rects[2].coords.y&&fingercoords.y <= (Rects[2].coords.y+Rects[2].coords.h)&&Screen.e.type==SDL_MOUSEBUTTONDOWN) {
						SDL_RenderCopy(Screen.render, Textures[3].loadtexture, NULL, &Rects[3].coords);
						SDL_RenderPresent(Screen.render);
						//While user press long time the button
						while (SDL_PollEvent(&Screen.e) == SDL_MOUSEBUTTONDOWN);

						ischarging = 1;

						if ((file = fopen("database.txt", "w")) == NULL) {
							printf("Cannot open \"database.txt\" file.");
						}
						else {
							fclose(file);
						}
						//Virus Escaner system
						for (i = 0; i <= 9; i++) {
							const char filename[] = { (const char)(i + 48),(const char)'.',(const char)'t',(const char)'x',(const char)'t',(const char)'\0' };

							if ((file = fopen(filename, "r")) != NULL) {
								fclose(file);
								if ((file = fopen("database.txt", "a")) == NULL) {
									printf("Cannot open \"database.txt\" file.");
								}
								else {
									fprintf(file, "%s\n",filename);
									fclose(file);
								}
							}
						}
					}
					else {
						SDL_RenderCopy(Screen.render, Textures[2].loadtexture, NULL, &Rects[2].coords);
					}

					if (ischarging == 1) {
						file = fopen("database.txt", "r");

						if (frames <= 60) {
							//Borrado de textura
							SDL_RenderCopy(Screen.render, Parche.parcheT, &Parche.parcheR, &Parche.parcheR);
							SDL_RenderCopy(Screen.render, Fonts.fontT[0], NULL, &Fonts.fontR[0]);

							charge(Rects[8].coords, frames);
						}
						else if ((p=fgetc(file)) == EOF) {
							fclose(file);
							//Primero se borra lo anterior
							SDL_RenderCopy(Screen.render, Parche.parcheT, &Parche.parcheR, &Parche.parcheR);
							//Carga el boton de mal icon
							SDL_RenderCopy(Screen.render, Textures[5].loadtexture, NULL, &Rects[5].coords);
							SDL_RenderCopy(Screen.render, Fonts.fontT[2], NULL, &Fonts.fontR[2]);
							ischarging = 0;
						}
						else {
							fclose(file);

							SDL_RenderCopy(Screen.render, Parche.parcheT, &Parche.parcheR, &Parche.parcheR);
							SDL_RenderCopy(Screen.render, Textures[4].loadtexture, NULL, &Rects[4].coords);
							SDL_RenderCopy(Screen.render, Fonts.fontT[1], NULL, &Fonts.fontR[1]);
							ischarging = 0;
						}
					}

					frames++;
					SDL_RenderPresent(Screen.render);
				}
			}
			break;
		     //Cuarentena Page
		case 2:
			i = 0;
             //Se modifico "fopen(file,"r")" por "file=fopen("database.txt","r")"
			file = fopen("database.txt", "r");

			while (feof(file) == 0) {
				filenames[i] = fgetc(file);
				i++;
			}
			if (i > 0) {
				i++;
				filenames[i] = '\0';
			}
			i = 0;

			while (filenames[i] != '\0') {
				if (filenames[i] == '\n')
					filenum++;
				i++;
			}

			char textobarra[] = { (const char)(filenum + 48),(const char)' ',(const char)'F',(const char)'i',(const char)'c',(const char)'h',(const char)'e',(const char)'r',(const char)'o',(const char)'s',(const char)' ',(const char)'p',(const char)'e',(const char)'l',(const char)'i',(const char)'g',(const char)'r',(const char)'o',(const char)'s',(const char)'o',(const char)'s',(const char)'\0' };

			if ((Fonts.fontT[3] = loadfont(3, textobarra, 0, 0, 255)) == NULL) {
				SDL_Log("No se pudo detectar los ficheros");
			}
			else {
				Fonts.fontR[3].x = Rects[7].coords.x + 16;
				Fonts.fontR[3].y = Rects[7].coords.y + 2;
				Fonts.fontR[3].w = Fonts.surface[3]->w;
				Fonts.fontR[3].h = Fonts.surface[3]->h;
			}
			i = 0;
			char impressignal = 1;

			while (1) {
				if (SDL_PollEvent(&Screen.e) == SDL_QUIT) {
					SCREEN = 0;
					break;
				}
				else {
					//Draw cuarentena background
					SDL_RenderCopy(Screen.render, Textures[6].loadtexture, NULL, &Screen.renderR);
					//Draw home button
					SDL_RenderCopy(Screen.render, Textures[9].loadtexture, NULL, &Rects[9].coords);
					//Draw cuarentena button
					SDL_RenderCopy(Screen.render, Textures[10].loadtexture, NULL, &Rects[10].coords);

					SDL_GetMouseState(&fingercoords.x, &fingercoords.y);

					if (fingercoords.x >= Rects[9].coords.x&&fingercoords.x <= (Rects[9].coords.x+Rects[9].coords.w)&&fingercoords.y >= Rects[9].coords.y&&fingercoords.y <= (Rects[9].coords.y+Rects[9].coords.h)&&Screen.e.type==SDL_MOUSEBUTTONDOWN) {
						SCREEN = 1;
						break;
					}

					if (impressignal == 1) {
						if (touchonbar == 1) {
							SDL_RenderCopy(Screen.render, Textures[7].loadtexture, NULL, &Rects[7].coords);

							if (fingercoords.x >= 243 && fingercoords.x <= (243+Rects[7].coords.w)&&fingercoords.y >= Rects[7].coords.y&&fingercoords.y <= (Rects[7].coords.y+Rects[7].coords.h) && Screen.e.type == SDL_MOUSEBUTTONDOWN) {
								impressignal = 0;

								for (i=0; i <= filenum; i++) {
									const char filename[] = { (const char)(i + 48),(const char)'.',(const char)'t',(const char)'x',(const char)'t',(const char)'\0' };

									remove(filename);
								}
							}
						}

						if (fingercoords.x >= Rects[7].coords.x&&fingercoords.x <= (Rects[7].coords.x+Rects[7].coords.w)&&fingercoords.y >= Rects[7].coords.y&&fingercoords.y <= (Rects[7].coords.y+Rects[7].coords.h) && Screen.e.type == SDL_MOUSEBUTTONDOWN) {
							if (touchonbar == 0)
								touchonbar = 1;
							else
								touchonbar = 0;
						}

						SDL_RenderCopy(Screen.render, Fonts.fontT[3], NULL, &Fonts.fontR[3]);
					}

					SDL_RenderPresent(Screen.render);
				}
			}
			break;
		default:
			SCREEN = 0;
			break;
		}
	}
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

void charge(SDL_Rect position, unsigned int signal) { 
	degrees += 51.5;
	SDL_Point point;
	point.x = position.w / 2;
	point.y = position.h / 2;
	SDL_RendererFlip flip = SDL_FLIP_NONE;

	if ((signal % 15) == 0) {
		SDL_RenderCopyEx(Screen.render, Textures[8].loadtexture, NULL, &position, degrees, &point, flip);
		SDL_RenderPresent(Screen.render);
		return;
	}
	else {
		return;
	}
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

SDL_Texture* loadfont(char pos, char text[], unsigned char r, unsigned char g, unsigned char b) {
	SDL_Texture* newtexture = NULL;
	SDL_Color color;
	color.r = r; color.g = g; color.b = b; color.a = 255;

	if ((Fonts.surface[pos] = TTF_RenderText_Solid(Fonts.font, text, color)) == NULL) {
		return NULL;
	}
	else if ((newtexture = SDL_CreateTextureFromSurface(Screen.render, Fonts.surface[pos])) == NULL) {
		return NULL;
	}
	else {
		return newtexture;
	}
}

//############################################################################################################################################
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
//############################################################################################################################################

void close() {
	SDL_DestroyWindow(Screen.window);
	SDL_DestroyRenderer(Screen.render);
	SDL_FreeSurface(Surfaces[0].loadimage);
	SDL_FreeSurface(Surfaces[1].loadimage);
	SDL_FreeSurface(Surfaces[2].loadimage);
	SDL_FreeSurface(Surfaces[3].loadimage);
	SDL_FreeSurface(Surfaces[4].loadimage);
	SDL_FreeSurface(Surfaces[5].loadimage);
	SDL_FreeSurface(Surfaces[6].loadimage);
	SDL_FreeSurface(Surfaces[7].loadimage);
	SDL_FreeSurface(Surfaces[8].loadimage);
	SDL_FreeSurface(Surfaces[9].loadimage);
	SDL_FreeSurface(Surfaces[10].loadimage);
	SDL_FreeSurface(Fonts.surface[0]);
	SDL_FreeSurface(Fonts.surface[1]);
	SDL_FreeSurface(Fonts.surface[2]);
	SDL_FreeSurface(Fonts.surface[3]);
	SDL_DestroyTexture(Textures[0].loadtexture);
	SDL_DestroyTexture(Textures[1].loadtexture);
	SDL_DestroyTexture(Textures[2].loadtexture);
	SDL_DestroyTexture(Textures[3].loadtexture);
	SDL_DestroyTexture(Textures[4].loadtexture);
	SDL_DestroyTexture(Textures[5].loadtexture);
	SDL_DestroyTexture(Textures[6].loadtexture);
	SDL_DestroyTexture(Textures[7].loadtexture);
	SDL_DestroyTexture(Textures[8].loadtexture);
	SDL_DestroyTexture(Textures[9].loadtexture);
	SDL_DestroyTexture(Textures[10].loadtexture);
	SDL_DestroyTexture(Parche.parcheT);
	SDL_DestroyTexture(Fonts.fontT[0]);
	SDL_DestroyTexture(Fonts.fontT[1]);
	SDL_DestroyTexture(Fonts.fontT[2]);
	SDL_DestroyTexture(Fonts.fontT[3]);
	TTF_CloseFont(Fonts.font);

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();

	return;
}
