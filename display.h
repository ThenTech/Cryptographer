/*
*	###############################
*	###		   display.h		###
*	###	   (c) Bart Stukken 	###
*	###############################
*
*	display.h : contains methods to manipulate colours used for printing in console.
*/
#ifndef DISPLAY_H
#define DISPLAY_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <time.h>
#include <sys/time.h>

void clearScreen(void);
void setFontColorInit(unsigned short colorCode);
void setFontColorFunction(unsigned short colorCode);
void(*setFontColor)(unsigned short colorCode) = setFontColorInit;

HANDLE stdOutHandle;

/*
*	Clears the console before printing.
*/
void clearScreen(void) {
	system("cls");
}

/*
*	Initialise the setFontColour function by setting its handle as the current console window.
*/
void setFontColorInit(unsigned short colorCode) {
	stdOutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	setFontColor = setFontColorFunction;
	setFontColorFunction(colorCode);
}

/*
*	Sets the colour for printing in the console.
*/
void setFontColorFunction(unsigned short colorCode) {
	SetConsoleTextAttribute(stdOutHandle, colorCode);
}


/*
*	###############################
*	###		   display.h		###
*	###	 (c) William Thenaers 	###
*	###############################
*
*	display.h : contains methods to save and restores colours and a text representation.
*/

/*
*	Save previous colour settings.
*/
void saveConsole(WORD *saved_attributes) {
	CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
	GetConsoleScreenBufferInfo(stdOutHandle, &consoleInfo);
	*saved_attributes = consoleInfo.wAttributes;
}

/*
*	Restore previous colour settings
*/
void restoreConsole(WORD saved_attributes) {
	SetConsoleTextAttribute(stdOutHandle, saved_attributes);
}

/*
*	Define a new variable of type enum as COLOUR.
*	
*	colorCode = 0x00 == 0000 0000
*		with:					|	Foreground:	Blue
*							   |	Foreground:	Green
*							  |		Foreground:	Red
*							 |		Foreground:	Bright
*						   |		Background:	Blue
*						  |			Background:	Green
*						 |			Background:	Red
*						|			Background:	Bright
*/
typedef enum {
	// Foreground colours
	BLACK	= 0x00,	// All zero = black
	FWHITE	= 0x07,	// All Coloured = white

	FRED	= 0x04,
	FGREEN	= 0x02,
	FBLUE	= 0x01,
	FBRIGHT = 0x08, // Text colour is intensified.

	FYELLOW = FRED | FGREEN,
	FPURPLE = FRED | FBLUE,
	FCYAN	= FGREEN | FBLUE,

	// Background colours
	BWHITE	= 0x70,

	BRED	= 0x40,
	BGREEN	= 0x20,
	BBLUE	= 0x10,
	BBRIGHT = 0x80,	// Background colour is intensified.

	BYELLOW = BRED | BGREEN,
	BPURPLE = BRED | BBLUE,
	BCYAN	= BGREEN | BBLUE
} COLOUR;

/*
 *	Initialize default font colour.
 */
void Screen_init(void) {
	//setFontColor(FWHITE);
	setFontColor(-1);
}

/*
 *	Prints a timestamp, with millisecond precision.
 */
std::string Screen_getTimestamp(void) {
	time_t ltime = time(NULL);
	struct tm *Tm = localtime(&ltime);
	struct timeval detail_time;
	gettimeofday(&detail_time,NULL);
	char out[15];
	sprintf(out, "[%02d:%02d:%02d.%03ld]", Tm->tm_hour, Tm->tm_min, Tm->tm_sec, detail_time.tv_usec / 1000); //1000 == ms :: 100 == 0.1 ms
	return std::string(out);
}

/*
 *	Error outputstream or cerr << ... ;
 *	Saves and restores previous colour.
 */
void err(std::string s) {
	WORD saved_attributes_screen;
	saveConsole(&saved_attributes_screen);
	setFontColor(FRED | FBRIGHT);

	std::cerr << Screen_getTimestamp() << ' ' << s << std::endl;

	restoreConsole(saved_attributes_screen);
}

/*
 *	Logging outputstream or clog << ... ;
 *	Saves and restores previous colour.
 */
void log(std::string s) {
	WORD saved_attributes_screen;
	saveConsole(&saved_attributes_screen);
	setFontColor(FGREEN | FBRIGHT);

	std::clog << Screen_getTimestamp() << ' ' << s << std::endl;

	restoreConsole(saved_attributes_screen);
}

#endif
