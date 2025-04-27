#pragma once

/* FUNCTIONAL */
#define START_OF_INSTR  (char*)"????"
#define RESUME_READING  (char*)"****"

/* AS CHARS - OPTIONS */
#define NUMB_OF_SECTION '?'
#define S_SELECTOR		'S'
#define A_ATTRIBUTE		'A'
#define D_REMOVE		'D'
#define E_FIND			'E'
#define i_IDXSECTION	'i'
#define SELECT_ALL		'*'

/* READING THE CSS */
#define CURLY_BRACKETS1	'{'
#define CURLY_BRACKETS2	'}'
#define COMMA			','
#define COLON			':'
#define SEMICOLON		';'

/* AS ARRAYS OF CHARS - STRING_CH */
#define NUMB_OF_SECTION_CH	(char*)"?"
#define S_SELECTOR_CH		(char*)"S"
#define A_ATTRIBUTE_CH		(char*)"A"
#define D_REMOVE_CH			(char*)"D"
#define E_FIND_CH			(char*)"E"
#define i_IDXSECTION_CH		(char*)"i"
#define SELECT_ALL_CH		(char*)"*"

/* NUMBERS */
#define BUFFERSTRING	  100
#define STARTINGPOSITION	1
#define SPACEFORENDCHAR		1 /* SPACE NEED IN ARRAY FOR CHARCTER '\0' */
#define T_ARRNUMB			8 /* NUMBER OF ELEMENTS IN ARRAY INSIDE THE DOUBLY LINKED LIST */

/* MISCELLANEOUS */
#define SPACE			' '
#define ENDLINE			'\n'
#define HORIZONTALTAB	'\t'
#define ENDOFSTRING		'\0'
#define EMPTYSTR		""