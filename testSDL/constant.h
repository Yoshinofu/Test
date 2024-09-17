#ifndef constant_h_
#define constant_h_

struct TIMELIMIT
{
	static const float t;
};

enum GAMESTATE {
	OPENING,
	CASE1,
	CASE2,
	CASE3,
	CASE4,
	FINISH,
	RESULT,
	ENDING
};

enum MOVESTATUS {
	PLAY,
	TOSCORE,
	VANISH,
	GAMESET,
};

enum COLOR_No {
	NOTHING,
	BRACK,
	WHITE,
	RED,
	BRUE,
	GREEN,
	GRAY,
	LIGHTGREEN,
	YELLOW,
	PURPLE,
	ORENGE,
	LIGHTBRUE,
	SHADOW_C,
	B_RED,
	B_BRUE,
	B_GREEN,
	B_LIGHTBRUE,
	B_YELLOW,
	B_PURPLE,
	B_ORENGE,
	W_RED,
	W_BRUE,
	W_GREEN,
	W_LIGHTBRUE,
	W_YELLOW,
	W_PURPLE,
	W_ORENGE,
	FIELD
};

enum PLAYER_NO {
	P0,
	P1,
	P2,
	BOTH
};

enum MINO_NO {
	NONE,
	I_MINO,
	J_MINO,
	L_MINO,
	O_MINO,
	S_MINO,
	T_MINO,
	Z_MINO
};

enum STATUS {
	BLANK,
	FALLING,
	STACKING,
	STACKED,
	SHADOW,
	HOLD,
	NEXT
};

enum BUTTONSTATUS {
	BUP,
	BDOWN,
	BRIGHT,
	BLEFT
};

enum HELDSTATUS {
	RIGHT,
	LEFT,
	TIME
};

enum HOLDSTATUS {
	GO,
	SKIP,
	PASS
};

struct Vector
{
	int x;
	int y;
};

struct Point
{
	float x;
	float y;
};

struct WindowLength
{
	static const int WIDTH;
	static const int HEIGHT;
};

struct BlockLength
{
	static const int WIDTH;
	static const int HEIGHT;
};

struct FieldSize
{
	static const int COLUMNS;
	static const int LINES;
};

struct FieldLength
{
    static const int LINETHICKNESS;
	static const int WIDTH;
	static const int HEIGHT;
};

struct WindowPos
{
	static const int X;
	static const int Y;
};

struct FieldPos
{
	static const int X;
	static const int Y;
};

struct HoldLength
{
	static const int WIDTH;
	static const int HEIGHT;
};

struct HoldPos1
{
	static const int X;
	static const int Y;
};

struct HoldPos2
{
	static const int X;
	static const int Y;
};

struct NextLength
{
	static const int NUM;
	static const int WIDTH;
	static const int HEIGHT;
};

struct NextPos1
{
	static const int X;
	static const int Y;
};

struct NextPos2
{
	static const int X;
	static const int Y;
};



struct OMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
};


struct TMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
	static COLOR_No array1[4][4];
	static COLOR_No array2[4][4];
	static COLOR_No array3[4][4];
};

struct JMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
	static COLOR_No array1[4][4];
	static COLOR_No array2[4][4];
	static COLOR_No array3[4][4];

};


struct LMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
	static COLOR_No array1[4][4];
	static COLOR_No array2[4][4];
	static COLOR_No array3[4][4];

};

struct SMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
	static COLOR_No array1[4][4];
};

struct ZMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
	static COLOR_No array1[4][4];
};

struct IMINO
{
	static const COLOR_No c;
	static const COLOR_No bc;
	static const COLOR_No wc;
	static const COLOR_No o;
	static COLOR_No array0[4][4];
	static COLOR_No array1[4][4];
};



#endif