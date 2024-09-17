#include "constant.h"

const float TIMELIMIT::t = 180;

const int WindowLength::WIDTH = 1200;
const int WindowLength::HEIGHT = 650;

const int BlockLength::WIDTH = 30;
const int BlockLength::HEIGHT = 30;

const int FieldSize::COLUMNS = 14 + 2;
const int FieldSize::LINES = 21 + 4;

const int FieldLength::LINETHICKNESS = 2;
const int FieldLength::WIDTH = BlockLength::WIDTH * FieldSize::COLUMNS;
const int FieldLength::HEIGHT = BlockLength::HEIGHT * FieldSize::LINES;

const int WindowPos::X = 50;
const int WindowPos::Y = 25;

const int FieldPos::X = (WindowLength::WIDTH - FieldLength::WIDTH) / 2;
const int FieldPos::Y = 0 - BlockLength::HEIGHT * 4;

const int HoldLength::HEIGHT = BlockLength::HEIGHT * 4;
const int HoldLength::WIDTH = BlockLength::WIDTH * 4;

const int HoldPos1::X = FieldPos::X * 3 / 4 - HoldLength::WIDTH / 2;
const int HoldPos1::Y = FieldLength::HEIGHT / 3;

const int HoldPos2::X = WindowLength::WIDTH - FieldPos::X * 3 / 4 - HoldLength::WIDTH / 2;
const int HoldPos2::Y = FieldLength::HEIGHT / 3;

const int NextLength::NUM = 4;
const int NextLength::WIDTH = HoldLength::WIDTH;
const int NextLength::HEIGHT = HoldLength::HEIGHT * NUM;

const int NextPos1::X = FieldPos::X / 3 - NextLength::WIDTH / 2;
const int NextPos1::Y = ( WindowLength::HEIGHT - NextLength::HEIGHT ) / 2 ;

const int NextPos2::X = WindowLength::WIDTH - FieldPos::X / 3 - NextLength::WIDTH / 2;
const int NextPos2::Y = ( WindowLength::HEIGHT - NextLength::HEIGHT ) / 2;


const COLOR_No OMINO::c = YELLOW;
const COLOR_No OMINO::bc = B_YELLOW;
const COLOR_No OMINO::wc = W_YELLOW;
const COLOR_No OMINO::o = NOTHING;
COLOR_No OMINO::array0[4][4] = { {o,o,o,o},
								{o,c,c,o},
								{o,c,c,o},
								{o,o,o,o} };

const COLOR_No TMINO::c = PURPLE;
const COLOR_No TMINO::bc = B_PURPLE;
const COLOR_No TMINO::wc = W_PURPLE;
const COLOR_No TMINO::o = NOTHING;
COLOR_No TMINO::array0[4][4] = { {o,o,o,o},
								{o,c,o,o},
								{c,c,c,o},
								{o,o,o,o} };

COLOR_No TMINO::array1[4][4] = { {o,o,o,o},
								{o,c,o,o},
								{o,c,c,o},
								{o,c,o,o} };

COLOR_No TMINO::array2[4][4] = { {o,o,o,o},
								{o,o,o,o},
								{c,c,c,o},
								{o,c,o,o} };

COLOR_No TMINO::array3[4][4] = { {o,o,o,o},
								{o,c,o,o},
								{c,c,o,o},
								{o,c,o,o} };

const COLOR_No JMINO::c = ORENGE;
const COLOR_No JMINO::bc = B_ORENGE;
const COLOR_No JMINO::wc = W_ORENGE;
const COLOR_No JMINO::o = NOTHING;
COLOR_No JMINO::array0[4][4] = { {o,o,c,o},
								{o,o,c,o},
								{o,c,c,o},
								{o,o,o,o} };

COLOR_No JMINO::array1[4][4] = { {o,o,o,o},
								{o,c,o,o},
								{o,c,c,c},
								{o,o,o,o} };

COLOR_No JMINO::array2[4][4] = { {o,o,o,o},
								{o,c,c,o},
								{o,c,o,o},
								{o,c,o,o} };

COLOR_No JMINO::array3[4][4] = { {o,o,o,o},
								{c,c,c,o},
								{o,o,c,o},
								{o,o,o,o} };

const COLOR_No LMINO::c = BRUE;
const COLOR_No LMINO::bc = B_BRUE;
const COLOR_No LMINO::wc =W_BRUE;
const COLOR_No LMINO::o = NOTHING;
COLOR_No LMINO::array0[4][4] = { {o,c,o,o},
								{o,c,o,o},
								{o,c,c,o},
								{o,o,o,o} };

COLOR_No LMINO::array1[4][4] = { {o,o,o,o},
								{o,c,c,c},
								{o,c,o,o},
								{o,o,o,o} };

COLOR_No LMINO::array2[4][4] = { {o,o,o,o},
								{o,c,c,o},
								{o,o,c,o},
								{o,o,c,o} };

COLOR_No LMINO::array3[4][4] = { {o,o,o,o},
								{o,o,c,o},
								{c,c,c,o},
								{o,o,o,o} };

const COLOR_No SMINO::c = GREEN;
const COLOR_No SMINO::bc = B_GREEN;
const COLOR_No SMINO::wc = W_GREEN;
const COLOR_No SMINO::o = NOTHING;
COLOR_No SMINO::array0[4][4] = { {o,o,o,o},
								{o,c,c,o},
								{c,c,o,o},
								{o,o,o,o} };

COLOR_No SMINO::array1[4][4] = { {o,c,o,o},
								{o,c,c,o},
								{o,o,c,o},
								{o,o,o,o} };

const COLOR_No ZMINO::c = RED;
const COLOR_No ZMINO::bc = B_RED;
const COLOR_No ZMINO::wc = W_RED;
const COLOR_No ZMINO::o = NOTHING;
COLOR_No ZMINO::array0[4][4] = { {o,o,o,o},
								{c,c,o,o},
								{o,c,c,o},
								{o,o,o,o} };

COLOR_No ZMINO::array1[4][4] = { {o,o,c,o},
								{o,c,c,o},
								{o,c,o,o},
								{o,o,o,o} };

const COLOR_No IMINO::c = LIGHTBRUE;
const COLOR_No IMINO::bc = B_LIGHTBRUE;
const COLOR_No IMINO::wc = W_LIGHTBRUE;
const COLOR_No IMINO::o = NOTHING;
COLOR_No IMINO::array0[4][4] = { {o,o,o,o},
								{o,o,o,o},
								{c,c,c,c},
								{o,o,o,o} };

COLOR_No IMINO::array1[4][4] = { {o,c,o,o},
								{o,c,o,o},
								{o,c,o,o},
								{o,c,o,o} };
