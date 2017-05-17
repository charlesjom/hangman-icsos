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
#define restart '2'
#define about '2'
#define quit '0'
#define done '0'
#define yes 'y'
#define no 'n'

#define WHITE 63
#define ALPHABET 26

void erase();	// basically covers an area with a black rectangle
void generateWord();
void chooseLetter(char c);
int checkGuess(char c);
int isGuessed();
int checkIfChosen(char c);
void printHangman();
void printState();
void askToRestart();

// global variables
int row, col;
int score = 0;	// number of guessed word
int guesses = 0; // number of guesses
int lives = 10;	// number of lives left
char word[32];	// word to guessed
char hint[32];	// hint for word
char guessword[32][2];	// word with correct guesses
char str[10];
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
			do {	// game instance
				if (keypress == start) { // initial state
					generateWord();	// generate word to guess
				}
				// getch();
				erase(1,1,400,220);
				printState();
				do {	// guessing part
					if (keypress= (char)getch()) {
						chooseLetter(keypress);		// player choose a letter
						erase(1,1,400,220);
						printState();

						if (isGuessed() == 1) { // finished a word
							erase(80,160,400,60);
							score += lives;	// increment score
							write_text("Congratulations!",89,160,WHITE,0);
							write_text("Press any key to continue",101, 170,WHITE,0);
							keypress=(char)getch();
							keypress = start;
							break;	// start next round
						}
					}
				} while (keypress != restart && keypress != quit && lives != 0);

				if (keypress == restart) {	// player wants to restart
					erase(1,1,400,220);
					write_text("Do you want to restart?",80,40,WHITE,1); //title
					//menu options
					write_text("y - Yes",40,180,WHITE,0); 
					write_text("n - No",200,180,WHITE,0);
					// wait for valid answer
					do {
						keypress=(char)getch();
					}
					while (keypress != yes && keypress != no); 

					if (keypress == yes) keypress = start;
				}
				else if (keypress == quit) {	// player wants to quit
					erase(1,1,400,220);
					write_text("Do you want to exit?",80,40,WHITE,1); //title
					//menu options
					write_text("y - Yes",40,180,WHITE,0); 
					write_text("n - No",200,180,WHITE,0);
					// wait for valid answer
					do {
						keypress=(char)getch();
					}
					while (keypress != yes && keypress != no);
					
					if (keypress == yes) keypress = quit;
					break;
				}

				if (lives == 0) { // game over
					erase(1,1,400,220);
					write_text("Game Over!", 89, 40, WHITE, 1);
					write_text("Score: ", 100, 80, WHITE, 0);
					sprintf(str, "%d", score);
					write_text(str, 180, 80, WHITE, 0);
					write_text("Press any key",101, 170,WHITE,0);
					keypress=(char)getch();
					keypress = yes;
					break;
				}
			} while (keypress != yes);
		}
		else if (keypress == about) {
			// print about
			write_text("ABOUT",120,40,WHITE,1); //title
			write_text("This is a simple guessing game of words",40,70,WHITE,0);
			write_text("Guess the word you get a point",40,90,WHITE,0);
			write_text("Use up your lives, then game over",40,110,WHITE,0);
			write_text("Enjoy! ^_^",40,130,WHITE,0);
			write_text("Press any key to return to menu...",101, 180,WHITE,0);
			getch();
		}
	} while (keypress != quit);

	set_graphics(VGA_TEXT80X25X16);
	clrscr();
}

void erase(int x, int y, int w, int h){ //basically covers an area with a black rectangle 
   int i,j;
   for (i=x;i<=(y+h);i++)
      for (j=y;j<=(x+w);j++)
         write_pixel(j,i,100);
}

int isGuessed() {
	int i;
	for (i=0; i<strlen(word); i++) {
		if (guessword[i][1] == 0) return 0;
	}
	return 1;
}

int numOfEntries(char * filename) {
	FILE * fp = fopen(filename, "r");
	char string[70];
	int counter = 0;

	if (fp != NULL) {
		while (fgets(string, 70, fp)) counter++;
		fclose(fp);
	}

	return counter;
}

void generateWord(){
	// read file
	FILE * fp;
	int number, i;
	time_t t;
	char string[70];
	char delim[2] = "-";
	char * token;
	char num[15];

	fp = fopen("words.txt", "r");
	number = numOfEntries("words.txt");
	
	// randomize
	if (fp != NULL) {
		for (i=0; i<number; i++) {
			fgets(string, 70, fp);
			if (i == (rand() % number)) {
				fgets(string, 70, fp);
				string[strlen(string) - 1] = '\0';
				token = strtok(string, delim);
				strcpy(word, token);
				token = strtok(NULL, delim);
				strcpy(hint, token);
			}
		}
		fclose(fp);
	}

	lives = 10;		// reset number of lives

	for (i=0; i<strlen(word); i++) {
		if (word[i] == ' ') {
			guessword[i][0] = ' ';
			guessword[i][1] = 1;
		}
		else {
			guessword[i][0] = word[i];
			guessword[i][1] = 0;
		}
	}
	guessword[i][0] = '\0';
	guessword[i][1] = 0;

	// reset available letters
	for (i=0; i<26; i++) {
		letters[i][1] = 1;
	}
}

void chooseLetter(char c) {
	guesses++;	// increment number of guesses
	letters[c-97][1] = 0;
	// update number of lives left
	if (checkGuess(c) == 0) { // if guessed letter is correct
		lives--;
	}
}

int checkIfChosen(char c) {
	int i;
	for (i=0; i<26; i++) {
		if (letters[i][1] = 1) return 1;
	}
	return 0;
}

int checkGuess(char c) {
	int flag = 0, i;
	for (i=0; i<strlen(word); i++) {
		if (word[i] == c || word[i] == c-32) {
			flag = 1;
			guessword[i][1] = 1;
		}
	}
	return flag;
}

void printHangman(){
	//print vertical pole
	if(lives<10) {
		write_text("||",10,50,WHITE,0);
		write_text("||",10,60,WHITE,0);
		write_text("||",10,70,WHITE,0);
		write_text("||",10,80,WHITE,0);
		write_text("||",10,90,WHITE,0);
		write_text("||",10,100,WHITE,0);
		write_text("||",10,110,WHITE,0);
		write_text("||",10,120,WHITE,0);
		write_text("||",10,130,WHITE,0);
	}
	//horizontal beam
	if(lives<9){
		write_text("===========",10,40,WHITE,0);
	}
	//support beam
	if(lives<8){
		write_text("/",40,50,WHITE,0);
		write_text("/",30,60,WHITE,0);
	}
	//rope
	if(lives<1){
		write_text("|",60,50,WHITE,0);
		write_text("|",60,60,WHITE,0);
		write_text("_",70,60,WHITE,0);
	}
	//head
	if(lives<7){
		write_text("( )",82,60,WHITE,0);
	}
	//body
	if(lives<6){
		write_text("|",85,70,WHITE,0);
		write_text("|",85,80,WHITE,0);
		write_text("|",85,90,WHITE,0);
		write_text("|",95,70,WHITE,0);
		write_text("|",95,80,WHITE,0);
		write_text("|",95,90,WHITE,0);
	}
	//left arm
	if(lives<5){
		write_text("/",80,70,WHITE,0);
		write_text("/",70,80,WHITE,0);
	}
	//right arm
	if(lives<4){
		write_text("\\",100,70,WHITE,0);
		write_text("\\",110,80,WHITE,0);
	}
	//left leg
	if(lives<3){
		write_text("/",80,100,WHITE,0);
		write_text("/",70,110,WHITE,0);
	}
	//right leg
	if(lives<2){
		write_text("\\",100,100,WHITE,0);
		write_text("\\",110,110,WHITE,0);
	}
}

void printState(){
	int i, j;
	char letter[5];
	char num[5];
	char str1[32];
	char str2[128];
	// menu options
	write_text("2 - Restart",40,180,WHITE,0);
	write_text("0 - Quit",200,180,WHITE,0);
	printHangman();
	// print word
	for (i=0; i<strlen(word); i++) {
		if (guessword[i][1] == 1) str1[i] = word[i];
		else str1[i] = '_';
	}
	str1[strlen(word)] = '\0';
	// print hint
	sprintf(str2, "%s", hint);
	sprintf(num,  "LIVES: %d", lives);

	write_text(str1, 150, 20, WHITE, 1);
	write_text("-------HINT-------", 150, 50, WHITE, 0);
	write_text(str2, 150, 70, WHITE, 0);
	write_text(num, 10, 20, WHITE, 0);

	// display all available letters
	for (i=0; i<9; i++) {
		j = 150 + (18 * i);
		if (letters[i][1] == 1) {
			sprintf(letter, "%c", letters[i][0] - 32);
			write_text(letter,j,90,WHITE,0);
		}
	}

	for (i=9; i<18; i++) {
		j = 150 + (18 * (i%9));
		if (letters[i][1] == 1) {
			sprintf(letter, "%c", letters[i][0] - 32);
			write_text(letter,j,110,WHITE,0);
		}
	}

	for (i=18; i<26; i++) {
		j = 150 + (18 * (i%9));
		if (letters[i][1] == 1) {
			sprintf(letter, "%c", letters[i][0] - 32);
			write_text(letter,j,130,WHITE,0);
		}
	}

	// display number of lives
}

//displays header
int header(){
	write_text("HANGMAN",120,40,WHITE,1); //title
	//menu options
	write_text("1 - Start",15,180,WHITE,0); 
	write_text("2 - About", 120, 180, WHITE, 0);
	write_text("0 - Exit", 225,180,WHITE,0);
}