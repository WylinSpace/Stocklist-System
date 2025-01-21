#ifndef TEXTSTYLE_CPP
#define TEXTSTYLE_CPP

//COLOR DEFINIITION
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

//TEXT STYLE
#define BOLD            "\033[1m"
#define ITALIC          "\033[3m"
#define UNDERLINE       "\033[4m"
#define STRIKETHROUGH   "\033[9m"

//CURSOR MOVEMENT
#define MOVE_CURSOR(row, col) "\033[" #row ";" #col "H"
#define CLEAR_SCREEN "\033[2J"
#define CLEAR_TO_END "\033[0J"
#define SAVE_CURSOR "\033[s"
#define RESTORE_CURSOR "\033[u"
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

#endif