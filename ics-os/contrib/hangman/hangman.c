#include "../../sdk/dexsdk.h"

// constants
#define A 'a'
#define B 'b'
#define C 'c'
#define D 'd'
#define E 'e'
#define F 'f'
#define G 'g'
#define H 'h'
#define I 'i'
#define J 'j'
#define K 'k'
#define L 'l'
#define M 'm'
#define N 'n'
#define O 'o'
#define P 'p'
#define Q 'q'
#define R 'r'
#define S 's'
#define T 't'
#define U 'u'
#define V 'v'
#define W 'w'
#define X 'x'
#define Y 'y'
#define Z 'z'
#define start '1'
#define quit '2'
#define done '0'

#define WHITE 63

void erase();	// basically covers an area with a black rectangle
void generateWord();
void chooseLetter(char c);
void printHangman();
void printState();

// global variables
int row, col;
int guessed = 0; // 1 if word is guessed, 0 if not
int score = 0;
int guesses = 0; // number of guesses
char * word;	// word to guessed
char * guessword;	// word with correct guesses
	// available letters to pick from
char letters[26][2] = {{A,1}, {B,1}, {C,1}, {D,1}, {E,1}, {F,1}, {G,1}, {H,1}, {I,1}, {J,1},
					{K,1}, {L,1}, {M,1}, {N,1}, {O,1}, {P,1}, {Q,1}, {R,1}, {S,1}, {T,1},
					{U,1}, {V,1}, {W,1}, {X,1}, {Y,1}, {Z,1}};

int main() {
	char keypress= start;
	
	set_graphics(VGA_320X200X256);

	do {
		erase(1,1,400,220);

		header(8,5);	// print menu

		keypress = (char) getch();
		erase(1,1,400,220);

		if (keypress == start) {
			do {
				if (keypress == start) { // initial state
					erase(1,1,400,220);
					generateWord();
				}
				else {
					printState();
				}
				do {
					if (keypress= (char)getch()) {
						chooseLetter(keypress);
					}
				} while (keypress != quit && guessed !=1);
			} while (keypress != done);
		}
	}
	while (keypress != quit);

	set_graphics(VGA_320X200X256);
	clrscr();	
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=y;i<=(y+h);i++)
      for (j=x;j<=(x+w);j++)
         write_pixel(i,j,100);
}

void generateWord(){
	// read file
	// randomize
	printState();
}
void chooseLetter(char c){
	guesses++;	// increment number of guesses

}
void printHangman(){
	// check 'guesses'
}

void printState(){
	printHangman();
	// check 'guessword'
	// print all letters with value 1
	// print all available letters
}

//displays header
int header(){
	write_text("HANGMAN",120,40,WHITE,1); //title

	//menu options
	write_text("1 - Start",40,160,WHITE,0); 
	write_text("2 - Quit",200,160,WHITE,0);
}