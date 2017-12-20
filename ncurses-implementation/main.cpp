#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include <iostream>
#include <string>
#include <curses.h>
#define XMAX 16
#define YMAX 9

class ConsoleLCD
{
private:
	bool pixels[84][48];
	WINDOW* win;
public:
	void init()
	{
		initscr();
		noecho();
		win = newwin(48, 84, 0, 0);
		clear();
	}

	void clear()
	{
		for (int i = 0; i < 84; i++) 
		{
			for (int j = 0; j < 48; j++) 
			{
				pixels[i][j] = false;
			}
		}
		
	}

	void refresh()
	{
		for (int i = 0; i < 48; i++)
		{
			for (int j = 0; j < 84; j++)
			{
				if (pixels[j][i]) 
				{
					mvwaddch(win, i, j, char(178));
				}
				else
				{
					mvwaddch(win, i, j, ' ');
				}
			}
		}
		wrefresh(win);
	}

	void setPixel(int x, int y)
	{
		if(x >= 0 && x < 84 && y >= 0 && y < 48) 
		{
			pixels[x][48 - y] = true;
		}
	}

	void printString(std::string string, int x, int y) {
		std::cout << string << std::endl;
	}
};

ConsoleLCD lcd;

float Ox;
float Oy;
bool SW;



void wait(float time)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(long(time * 1000)));
}


void readInput() {
	while (1)
	{

	Ox = 0.5;
	Oy = 0.5;
	SW = false;

	char input = getch();

	switch (input)
	{
	case ' ':
		SW = true;
		break;
	case 'w':
		Oy = 1;
		break;
	case 's':
		Oy = 0;
		break;
	case 'a':
		Ox = 0;
		break;
	case 'd':
		Ox = 1;
		break;
	default:
		break;
	}

	wait(0.1);
	}
}

char mapa[9][16][4] = {
	{ { '1','0','1','1' },{ '0','1','1','0' },{ '0','0','1','1' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '0','1','1','0' },{ '0','1','1','1' },{ '0','0','1','1' },{ '1','0','1','0' },{ '1','1','1','0' },{ '0','0','1','1' },{ '0','1','1','0' },{ '0','0','1','1' },{ '0','0','1','0' },{ '1','1','1','0' } },
	{ { '0','1','1','1' },{ '0','1','0','1' },{ '1','0','0','1' },{ '1','0','1','0' },{ '0','1','1','0' },{ '0','1','1','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','0','1','1' },{ '1','0','1','0' },{ '1','1','0','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','0','1','1' } },
	{ { '0','0','0','1' },{ '1','0','0','0' },{ '1','0','1','0' },{ '0','1','1','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '1','0','0','1' },{ '0','0','0','0' },{ '0','0','0','0' },{ '1','0','1','0' },{ '0','1','1','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' } },
	{ { '0','1','0','1' },{ '0','0','1','1' },{ '0','1','1','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '1','0','0','1' },{ '0','1','1','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','0','1','1' },{ '0','1','0','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' } },
	{ { '0','1','0','1' },{ '0','1','0','1' },{ '1','0','0','1' },{ '1','1','0','0' },{ '1','0','0','1' },{ '1','0','0','0' },{ '1','1','1','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '1','1','0','1' },{ '0','1','0','1' } },
	{ { '0','1','0','1' },{ '0','0','0','1' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '0','1','1','0' },{ '0','0','1','1' },{ '0','1','0','0' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '1','0','0','1' },{ '1','0','0','0' },{ '1','0','0','0' },{ '1','1','0','0' } },
	{ { '0','1','0','1' },{ '0','0','0','1' },{ '0','0','1','0' },{ '1','0','1','0' },{ '0','1','1','0' },{ '0','1','0','1' },{ '1','1','0','1' },{ '0','1','0','1' },{ '1','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','1','0','1' },{ '0','0','1','1' },{ '1','0','1','0' },{ '1','0','1','0' },{ '0','1','1','0' } },
	{ { '1','1','0','1' },{ '0','1','0','1' },{ '1','0','0','1' },{ '1','1','1','0' },{ '0','1','0','1' },{ '1','0','0','1' },{ '1','0','1','0' },{ '1','0','0','0' },{ '1','0','1','0' },{ '1','1','0','0' },{ '1','0','0','1' },{ '1','1','0','0' },{ '0','1','0','1' },{ '0','0','1','1' },{ '1','1','1','0' },{ '0','1','0','1' } },
	{ { '1','0','1','0' },{ '1','0','0','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','0','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','1','0' },{ '1','0','0','1' },{ '1','0','0','1' },{ '1','0','1','0' },{ '1','1','0','0' } }
};

char x = 0, y = 8; // pozicija igraca
char orijentacija = 1; // 0-3

class Timer
{
private:
	unsigned long begTime;
	unsigned long endTime = 0;
public:
	void start() 
	{
		begTime = clock();
	}

	unsigned long read_ms() 
	{
		if (endTime == 0) 
		{
			return ((unsigned long)clock() - begTime) / CLOCKS_PER_SEC;
		}
		else {
			return(endTime - begTime) / CLOCKS_PER_SEC;
		}
	}

	void stop() 
	{
		endTime = clock();
	}
};

void crtaj2D()
{
	lcd.clear();
	for (int i = 0; i<9; i++)
		for (int j = 0; j<16; j++)
		{

			if (mapa[8 - i][j][2] == '1')
			{
				for (int k = 0; k<5; k++)
					lcd.setPixel(j * 5 + k, (i + 1) * 5);
			}
			if (mapa[8 - i][j][1] == '1')
			{
				for (int k = 0; k<5; k++)
					lcd.setPixel((j + 1) * 5, i * 5 + k);
			}
			if (mapa[8 - i][j][0] == '1')
			{
				for (int k = 0; k<5; k++)
					lcd.setPixel(j * 5 + k, i * 5);
			}
			if (mapa[8 - i][j][3] == '1')
			{
				for (int k = 0; k<5; k++)
					lcd.setPixel(j * 5, i * 5 + k);
			}
		}
	int py = 8 - y;
	switch (orijentacija)
	{
	case 2:
		for (int j = 0; j < 5; j++)
			lcd.setPixel(x * 5 + 2, py * 5 + j);
		lcd.setPixel(x * 5 + 4, py * 5 + 2);
		lcd.setPixel(x * 5 + 3, py * 5 + 3);
		lcd.setPixel(x * 5 + 1, py * 5 + 3);
		lcd.setPixel(x * 5 + 0, py * 5 + 2);
		break;
	case 1:
		for (int i = 0; i < 5; i++)
			lcd.setPixel(x * 5 + i, py * 5 + 2);
		lcd.setPixel(x * 5 + 2, py * 5 + 4);
		lcd.setPixel(x * 5 + 3, py * 5 + 3);
		lcd.setPixel(x * 5 + 3, py * 5 + 1);
		lcd.setPixel(x * 5 + 2, py * 5 + 0);
		break;
	case 0:
		for (int j = 0; j < 5; j++)
			lcd.setPixel(x * 5 + 2, py * 5 + j);
		lcd.setPixel(x * 5 + 4, py * 5 + 2);
		lcd.setPixel(x * 5 + 3, py * 5 + 1);
		lcd.setPixel(x * 5 + 1, py * 5 + 1);
		lcd.setPixel(x * 5 + 0, py * 5 + 2);
		break;
	case 3:
		for (int i = 0; i < 5; i++)
			lcd.setPixel(x * 5 + i, py * 5 + 2);
		lcd.setPixel(x * 5 + 2, py * 5 + 4);
		lcd.setPixel(x * 5 + 1, py * 5 + 3);
		lcd.setPixel(x * 5 + 1, py * 5 + 1);
		lcd.setPixel(x * 5 + 2, py * 5 + 0);
		break;
	}
	lcd.refresh();
}


void rotirajDesno()
{
	orijentacija++;
	if (orijentacija > 3)
		orijentacija = 0;
}

void rotirajLijevo()
{
	if (orijentacija == 0)
		orijentacija = 3;
	else
		orijentacija--;
}

bool mozePravo()
{
	switch (orijentacija)
	{
	case 0:
		if (y == YMAX)
			return false;
		if (mapa[y][x][0] == '0' && mapa[y + 1][x][2] == '0')
			return true;
		break;
	case 1:
		if (x == XMAX)
			return false;
		if (mapa[y][x][1] == '0' && mapa[y][x + 1][3] == '0')
			return true;
		break;
	case 2:
		if (y == 0)
			return false;
		if (mapa[y][x][2] == '0' && mapa[y - 1][x][0] == '0')
			return true;
		break;
	case 3:
		if (x == 0)
			return false;
		if (mapa[y][x][3] == '0' && mapa[y][x - 1][1] == '0')
			return true;
		break;
	}
	return true;
}

void pravo()
{
	switch (orijentacija)
	{
	case 0:
		if (y == YMAX)
			break;
		if (mapa[y][x][0] == '0' && mapa[y + 1][x][2] == '0')
			y++;
		break;
	case 1:
		if (x == XMAX)
			break;
		if (mapa[y][x][1] == '0' && mapa[y][x + 1][3] == '0')
			x++;
		break;
	case 2:
		if (y == 0)
			break;
		if (mapa[y][x][2] == '0' && mapa[y - 1][x][0] == '0')
			y--;
		break;
	case 3:
		if (x == 0)
			break;
		if (mapa[y][x][3] == '0' && mapa[y][x - 1][1] == '0')
			x--;
		break;
	}
}

void linije()
{
	for (int i = 0; i<28; i++)
		for (int j = 0; j < 36; j++)
			if (36.0 / 28.0*i - j < 1 && 36.0 / 28.0*i - j > -1)
				lcd.setPixel(i, j);
	for (int i = 0; i < 28; i++)
		for (int j = 0; j < 36; j++)
			if (-36.0 / 28.0*(i - 28) - j < 1 && -36.0 / 28.0*(i - 28) - j > -1)
				lcd.setPixel(i + 56, j);
	for (int i = 0; i < 84; i++)
		lcd.setPixel(i, 24);
	for (int j = 24; j<48; j++)
	{
		lcd.setPixel(18, j);
		lcd.setPixel(66, j);
	}
	for (int j = 36; j < 48; j++)
	{
		lcd.setPixel(28, j);
		lcd.setPixel(56, j);
	}
	for (int i = 28; i < 56; i++)
		lcd.setPixel(i, 36);
}

void desni()
{
	for (int i = 0; i < 18; i++)
		for (int j = 0; j < 24; j++)
			if (36.0 / 28.0*i - j < 1)
				lcd.setPixel(i, j);
	for (int j = 24; j<48; j++)
		for (int i = 0; i < 18; i++)
			lcd.setPixel(i, j);
}

void lijevi()
{
	for (int i = 0; i < 28; i++)
		for (int j = 0; j < 24; j++)
			if (-36.0 / 28.0*(i - 28) - j < 1)
				lcd.setPixel(i + 56, j);
	for (int j = 24; j<48; j++)
		for (int i = 0; i < 18; i++)
			lcd.setPixel(i + 66, j);
}

void skriveniDesni()
{
	for (int j = 24; j<48; j++)
		for (int i = 0; i < 18; i++)
			lcd.setPixel(i, j);
}

void skriveniLijevi()
{
	for (int j = 24; j<48; j++)
		for (int i = 0; i < 18; i++)
			lcd.setPixel(i + 66, j);
}

void daljiDesni()
{
	for (int i = 18; i<28; i++)
		for (int j = 24; j < 36; j++)
			if (36.0 / 28.0*i - j < 1)
				lcd.setPixel(i, j);
	for (int j = 36; j<48; j++)
		for (int i = 18; i < 28; i++)
			lcd.setPixel(i, j);
}

void daljiLijevi()
{
	for (int i = 0; i < 10; i++)
		for (int j = 24; j < 36; j++)
			if (-36.0 / 28.0*(i - 28) - j < 1)
				lcd.setPixel(i + 56, j);
	for (int j = 36; j<48; j++)
		for (int i = 0; i < 10; i++)
			lcd.setPixel(i + 56, j);
}

void blizi()
{
	for (int i = 18; i < 66; i++)
		for (int j = 24; j < 48; j++)
			lcd.setPixel(i, j);
}

void dalji()
{
	for (int i = 28; i < 56; i++)
		for (int j = 36; j < 48; j++)
			lcd.setPixel(i, j);
}

void linijeSkretanje()
{
	for (int i = 0; i<74; i++)
		for (int j = 6; j < 32; j++)
			if (24.0 / 74.0*i + 6 - j < 1 && 24.0 / 74.0*i + 6 - j > -1)
				lcd.setPixel(i, j);
	for (int i = 0; i < 74; i++)
		for (int j = 6; j < 32; j++)
			if (-24.0 / 74.0*(i - 74) + 6 - j < 1 && -24.0 / 74.0*(i - 74) + 6 - j > -1)
				lcd.setPixel(i + 10, j);
	for (int i = 0; i < 42; i++)
		for (int j = 28; j < 42; j++)
			if (14.0 / 42.0*i + 28 - j < 1 && 14.0 / 42.0*i + 28 - j > -1)
				lcd.setPixel(i, j);
	for (int i = 0; i < 42; i++)
		for (int j = 28; j < 42; j++)
			if (-14.0 / 42.0*(i - 42) + 28 - j < 1 && -14.0 / 42.0*(i - 42) + 28 - j > -1)
				lcd.setPixel(i + 42, j);
	for (int j = 30; j < 48; j++)
	{
		lcd.setPixel(10, j);
		lcd.setPixel(74, j);
	}
	for (int j = 20; j < 48; j++)
		lcd.setPixel(42, j);
}

void daljaDesno()
{
	for (int i = 0; i<10; i++)
		for (int j = 6; j < 48; j++)
			if (14.0 / 48.0*i + 28 - j <1)
				lcd.setPixel(i, j);
}

void daljaLijevo()
{
	for (int i = 74; i < 84; i++)
		for (int j = 6; j < 48; j++)
			if (-14.0 / 48.0*(i - 48) + 28 - j <1)
				lcd.setPixel(i, j + 12);
}

void blizaDesno()
{
	for (int i = 0; i<42; i++)
		for (int j = 6; j < 48; j++)
			if (24.0 / 74.0*i + 6 - j <1)
				lcd.setPixel(i, j);
}

void blizaLijevo()
{
	for (int i = 42; i < 84; i++)
		for (int j = 0; j < 48; j++)
			if (-24.0 / 74.0*(i - 74) + 6 - j < 1)
				lcd.setPixel(i, j + 4);
}

void drugaDesno()
{
	for (int i = 10; i < 42; i++)
		for (int j = 10; j < 48; j++)
			if (-24.0 / 74.0*(i - 74) + 6 - j < 1)
				lcd.setPixel(i, j + 4);
}

void drugaLijevo()
{
	for (int i = 42; i<74; i++)
		for (int j = 10; j < 48; j++)
			if (24.0 / 74.0*i + 6 - j <1)
				lcd.setPixel(i, j);
}

void izaDesno()
{
	for (int i = 10; i<42; i++)
		for (int j = 6; j < 48; j++)
			if (14.0 / 42.0*i + 28 - j <1)
				lcd.setPixel(i, j);
}

void izaLijevo()
{
	for (int i = 42; i < 74; i++)
		for (int j = 6; j < 48; j++)
			if (-14.0 / 42.0*(i - 42) + 28 - j <1)
				lcd.setPixel(i, j + 14);
}

void linijeNaprijed()
{
	for (int i = 0; i < 30; i++)
		for (int j = 0; j < 30; j++)
			if (i - j<1 && i - j>-1)
				lcd.setPixel(i, j);
	for (int i = 54; i < 84; i++)
		for (int j = 0; j < 30; j++)
			if (-(i - 84) - j < 1 && -(i - 84) - j > -1)
				lcd.setPixel(i, j);
	for (int i = 30; i < 54; i++)
		lcd.setPixel(i, 30);
	for (int i = 0; i < 84; i++)
		lcd.setPixel(i, 8);
	for (int j = 30; j < 48; j++)
	{
		lcd.setPixel(30, j);
		lcd.setPixel(54, j);
	}
	for (int j = 8; j < 48; j++)
	{
		lcd.setPixel(8, j);
		lcd.setPixel(76, j);
	}
}

void naprijedDalji()
{
	for (int i = 30; i < 54; i++)
		for (int j = 30; j < 48; j++)
			lcd.setPixel(i, j);
}

void naprijedLijevi()
{
	for (int i = 76; i < 84; i++)
		for (int j = 0; j < 48; j++)
			if (-(i - 84) - j < 1)
				lcd.setPixel(i, j);
}


void naprijedDesni()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 48; j++)
			if (i - j<1)
				lcd.setPixel(i, j);
}

void naprijedDaljiLijevi()
{
	for (int i = 54; i < 76; i++)
		for (int j = 8; j < 48; j++)
			if (-(i - 84) - j <1)
				lcd.setPixel(i, j);
}

void naprijedDaljiDesni()
{
	for (int i = 8; i < 30; i++)
		for (int j = 8; j < 48; j++)
			if (i - j<1)
				lcd.setPixel(i, j);
}

void naprijedSkriveniLijevi()
{
	for (int i = 76; i<84; i++)
		for (int j = 8; j < 48; j++)
			lcd.setPixel(i, j);
}

void naprijedSkriveniDesni()
{
	for (int i = 0; i<8; i++)
		for (int j = 8; j < 48; j++)
			lcd.setPixel(i, j);
}

void crtaj()
{
	lcd.clear();
	linije();
	switch (orijentacija)
	{
	case 0:
		if (y<YMAX)
		{
			if (mapa[y + 1][x][0] == '1')
				dalji();
			if (mapa[y + 1][x][3] == '1')
				daljiLijevi();
			if (mapa[y + 1][x][1] == '1')
				daljiDesni();
			if (mapa[y + 1][x][2] == '1' || mapa[y][x][0] == '1')
				blizi();
			if (x>0)
			{
				if (mapa[y + 1][x - 1][2] == '1' || mapa[y][x - 1][0] == '1')
					skriveniLijevi();
			}
			if (x<XMAX)
			{
				if (mapa[y + 1][x + 1][2] == '1' || mapa[y][x + 1][0] == '1')
					skriveniDesni();
			}
		}
		else
		{
			if (mapa[y][x][0] == '1')
				blizi();
			if (x<XMAX)
				if (mapa[y][x + 1][0] == '1')
					skriveniDesni();
			if (x>0)
				if (mapa[y][x - 1][0] == '1')
					skriveniLijevi();
		}
		if (mapa[y][x][1] == '1')
			desni();
		if (mapa[y][x][3] == '1')
			lijevi();
		break;
	case 1:
		if (x<XMAX)
		{
			if (mapa[y][x + 1][1] == '1')
				dalji();
			if (mapa[y][x + 1][0] == '1')
				daljiLijevi();
			if (mapa[y][x + 1][2] == '1')
				daljiDesni();
			if (mapa[y][x + 1][3] == '1' || mapa[y][x][1] == '1')
				blizi();
			if (y>0)
			{
				if (mapa[y - 1][x + 1][3] == '1' || mapa[y - 1][x][1] == '1')
					skriveniDesni();
			}
			if (y<YMAX)
			{
				if (mapa[y + 1][x + 1][3] == '1' || mapa[y + 1][x][1] == '1')
					skriveniLijevi();
			}
		}
		else
		{
			if (mapa[y][x][1] == '1')
				blizi();
			if (y>0)
				if (mapa[y - 1][x][1] == '1')
					skriveniDesni();
			if (y<YMAX)
				if (mapa[y + 1][x][1] == '1')
					skriveniLijevi();
		}
		if (mapa[y][x][2] == '1')
			desni();
		if (mapa[y][x][0] == '1')
			lijevi();
		break;
	case 2:
		if (y>0)
		{
			if (mapa[y - 1][x][2] == '1')
				dalji();
			if (mapa[y - 1][x][1] == '1')
				daljiLijevi();
			if (mapa[y - 1][x][3] == '1')
				daljiDesni();
			if (mapa[y - 1][x][0] == '1' || mapa[y][x][2] == '1')
				blizi();
			if (x>0)
			{
				if (mapa[y - 1][x - 1][0] == '1' || mapa[y][x - 1][2] == '1')
					skriveniDesni();
			}
			if (x<XMAX)
			{
				if (mapa[y - 1][x + 1][0] == '1' || mapa[y][x + 1][2] == '1')
					skriveniLijevi();
			}
		}
		else
		{
			if (mapa[y][x][2] == '1')
				blizi();
			if (x>0)
				if (mapa[y][x - 1][2] == '1')
					skriveniDesni();
			if (x<XMAX)
				if (mapa[y][x + 1][2] == '1')
					skriveniLijevi();
		}
		if (mapa[y][x][3] == '1')
			desni();
		if (mapa[y][x][1] == '1')
			lijevi();
		break;
	case 3:
		if (x>0)
		{
			if (mapa[y][x - 1][3] == '1')
				dalji();
			if (mapa[y][x - 1][2] == '1')
				daljiLijevi();
			if (mapa[y][x - 1][0] == '1')
				daljiDesni();
			if (mapa[y][x - 1][1] == '1' || mapa[y][x][3] == '1')
				blizi();
			if (y<YMAX)
			{
				if (mapa[y + 1][x - 1][1] == '1' || mapa[y + 1][x][3] == '1')
					skriveniDesni();
			}
			if (y>0)
			{
				if (mapa[y - 1][x - 1][1] == '1' || mapa[y - 1][x][3] == '1')
					skriveniLijevi();
			}
		}
		else
		{
			if (mapa[y][x][3] == '1')
				blizi();
			if (y>0)
				if (mapa[y - 1][x][3] == '1')
					skriveniLijevi();
			if (y<YMAX)
				if (mapa[y + 1][x][3] == '1')
					skriveniDesni();
		}
		if (mapa[y][x][0] == '1')
			desni();
		if (mapa[y][x][2] == '1')
			lijevi();
		break;
	}
	lcd.refresh();
}

void crtajRotacijaDesno()
{
	lcd.clear();
	linijeSkretanje();
	switch (orijentacija)
	{
	case 0:
		if (y<YMAX)
		{
			if (mapa[y + 1][x][3] == '1')
				drugaDesno();
			if (mapa[y + 1][x][0] == '1')
				daljaDesno();
			if (x>0)
			{
				if (mapa[y + 1][x - 1][0] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][3] == '1')
			blizaLijevo();
		if (x>0)
		{
			if (mapa[y][x - 1][0] == '1')
				drugaLijevo();
			if (mapa[y][x - 1][3] == '1')
				daljaLijevo();
			if (y<YMAX)
			{
				if (mapa[y + 1][x - 1][3] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][0] == '1')
			blizaDesno();
		break;
	case 1:
		if (x<XMAX)
		{
			if (mapa[y][x + 1][0] == '1')
				drugaDesno();
			if (mapa[y][x + 1][1] == '1')
				daljaDesno();
			if (y<YMAX)
			{
				if (mapa[y + 1][x + 1][1] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][0] == '1')
			blizaLijevo();
		if (y<YMAX)
		{
			if (mapa[y + 1][x][1] == '1')
				drugaLijevo();
			if (mapa[y + 1][x][0] == '1')
				daljaLijevo();
			if (x<XMAX)
			{
				if (mapa[y + 1][x + 1][0] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][1] == '1')
			blizaDesno();
		break;
	case 2:
		if (y>0)
		{
			if (mapa[y - 1][x][1] == '1')
				drugaDesno();
			if (mapa[y - 1][x][2] == '1')
				daljaDesno();
			if (x<XMAX)
			{
				if (mapa[y - 1][x + 1][2] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][1] == '1')
			blizaLijevo();
		if (x<XMAX)
		{
			if (mapa[y][x + 1][2] == '1')
				drugaLijevo();
			if (mapa[y][x + 1][1] == '1')
				daljaLijevo();
			if (y>0)
			{
				if (mapa[y - 1][x + 1][1] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][2] == '1')
			blizaDesno();
		break;
	case 3:
		if (x>0)
		{
			if (mapa[y][x - 1][2] == '1')
				drugaDesno();
			if (mapa[y][x - 1][3] == '1')
				daljaDesno();
			if (y>0)
			{
				if (mapa[y - 1][x - 1][3] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][2] == '1')
			blizaLijevo();
		if (y>0)
		{
			if (mapa[y - 1][x][3] == '1')
				drugaLijevo();
			if (mapa[y - 1][x][2] == '1')
				daljaLijevo();
			if (x>0)
			{
				if (mapa[y - 1][x - 1][2] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][3] == '1')
			blizaDesno();
		break;
	}
	lcd.refresh();
}

void crtajRotacijaLijevo()
{
	lcd.clear();
	linijeSkretanje();
	switch (orijentacija)
	{
	case 0:
		if (y<YMAX)
		{
			if (mapa[y + 1][x][1] == '1')
				drugaLijevo();
			if (mapa[y + 1][x][0] == '1')
				daljaLijevo();
			if (x<XMAX)
			{
				if (mapa[y + 1][x + 1][0] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][1] == '1')
			blizaDesno();
		if (x<XMAX)
		{
			if (mapa[y][x + 1][0] == '1')
				drugaDesno();
			if (mapa[y][x + 1][1] == '1')
				daljaDesno();
			if (y<YMAX)
			{
				if (mapa[y + 1][x + 1][1] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][0] == '1')
			blizaLijevo();
		break;
	case 1:
		if (x<XMAX)
		{
			if (mapa[y][x + 1][2] == '1')
				drugaLijevo();
			if (mapa[y][x + 1][1] == '1')
				daljaLijevo();
			if (y>0)
			{
				if (mapa[y - 1][x + 1][1] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][2] == '1')
			blizaDesno();
		if (y>0)
		{
			if (mapa[y - 1][x][1] == '1')
				drugaDesno();
			if (mapa[y - 1][x][2] == '1')
				daljaDesno();
			if (x<XMAX)
			{
				if (mapa[y - 1][x + 1][2] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][1] == '1')
			blizaLijevo();
		break;
	case 2:
		if (y>0)
		{
			if (mapa[y - 1][x][3] == '1')
				drugaLijevo();
			if (mapa[y - 1][x][2] == '1')
				daljaLijevo();
			if (x>0)
			{
				if (mapa[y - 1][x - 1][2] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][3] == '1')
			blizaDesno();
		if (x>0)
		{
			if (mapa[y][x - 1][2] == '1')
				drugaDesno();
			if (mapa[y][x - 1][3] == '1')
				daljaDesno();
			if (y>0)
			{
				if (mapa[y - 1][x - 1][3] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][2] == '1')
			blizaLijevo();
		break;
	case 3:
		if (x>0)
		{
			if (mapa[y][x - 1][0] == '1')
				drugaLijevo();
			if (mapa[y][x - 1][3] == '1')
				daljaLijevo();
			if (y<YMAX)
			{
				if (mapa[y + 1][x - 1][3] == '1')
					izaLijevo();
			}
		}
		if (mapa[y][x][0] == '1')
			blizaDesno();
		if (y<YMAX)
		{
			if (mapa[y + 1][x][3] == '1')
				drugaDesno();
			if (mapa[y + 1][x][0] == '1')
				daljaDesno();
			if (x>0)
			{
				if (mapa[y + 1][x - 1][0] == '1')
					izaDesno();
			}
		}
		if (mapa[y][x][3] == '1')
			blizaLijevo();
		break;
	}
	lcd.refresh();
}

void crtajNaprijed()
{
	lcd.clear();
	linijeNaprijed();
	switch (orijentacija)
	{
	case 0:
		if (mapa[y][x][0] == '1')
			naprijedDalji();
		if (mapa[y][x][3] == '1')
			naprijedDaljiLijevi();
		if (mapa[y][x][1] == '1')
			naprijedDaljiDesni();
		if (y>0)
		{
			if (mapa[y - 1][x][3] == '1')
				naprijedLijevi();
			if (mapa[y - 1][x][1] == '1')
				naprijedDesni();
			if (x>0)
				if (mapa[y - 1][x - 1][0] == '1')
					naprijedSkriveniLijevi();
			if (x<XMAX)
				if (mapa[y - 1][x + 1][0] == '1')
					naprijedSkriveniDesni();
		}
		break;
	case 1:
		if (mapa[y][x][1] == '1')
			naprijedDalji();
		if (mapa[y][x][0] == '1')
			naprijedDaljiLijevi();
		if (mapa[y][x][2] == '1')
			naprijedDaljiDesni();
		if (x>0)
		{
			if (mapa[y][x - 1][0] == '1')
				naprijedLijevi();
			if (mapa[y][x - 1][2] == '1')
				naprijedDesni();
			if (y>0)
				if (mapa[y - 1][x - 1][1] == '1')
					naprijedSkriveniDesni();
			if (y<YMAX)
				if (mapa[y + 1][x - 1][1] == '1')
					naprijedSkriveniLijevi();
		}
		break;
	case 2:
		if (mapa[y][x][2] == '1')
			naprijedDalji();
		if (mapa[y][x][1] == '1')
			naprijedDaljiLijevi();
		if (mapa[y][x][3] == '1')
			naprijedDaljiDesni();
		if (y<YMAX)
		{
			if (mapa[y + 1][x][3] == '1')
				naprijedLijevi();
			if (mapa[y + 1][x][1] == '1')
				naprijedDesni();
			if (x>0)
				if (mapa[y + 1][x - 1][2] == '1')
					naprijedSkriveniDesni();
			if (x<XMAX)
				if (mapa[y + 1][x + 1][2] == '1')
					naprijedSkriveniLijevi();
		}
		break;
	case 3:
		if (mapa[y][x][3] == '1')
			naprijedDalji();
		if (mapa[y][x][2] == '1')
			naprijedDaljiLijevi();
		if (mapa[y][x][0] == '1')
			naprijedDaljiDesni();
		if (x<XMAX)
		{
			if (mapa[y][x + 1][2] == '1')
				naprijedLijevi();
			if (mapa[y][x + 1][0] == '1')
				naprijedDesni();
			if (y>0)
				if (mapa[y - 1][x + 1][3] == '1')
					naprijedSkriveniLijevi();
			if (y<YMAX)
				if (mapa[y + 1][x + 1][3] == '1')
					naprijedSkriveniDesni();
		}
		break;
	}
	lcd.refresh();
}
Timer t;
char vrijeme[6] = "00:00";
char* dajVrijeme()
{
	vrijeme[5] = 0;
	int milisekunde = t.read_ms();
	int sekunde = (t.read_ms() / 1000) % 60;
	int minute = t.read_ms() / 60000;
	if (minute > 99)
	{
		minute = 99;
		sekunde = 99;
	}
	int i = 4;
	while (sekunde > 0)
	{
		int cifra = sekunde % 10;
		vrijeme[i] = '0' + cifra;
		sekunde /= 10;
		i--;
	}
	if (i == 4)
	{
		vrijeme[i] = '0';
		i--;
	}
	if (i == 3)
	{
		vrijeme[i] = '0';
		i--;
	}
	if (i == 2)
	{
		vrijeme[i] = ':';
		i--;
	}
	while (minute > 0)
	{
		int cifra = minute % 10;
		vrijeme[i] = '0' + cifra;
		i--;
		minute /= 10;
	}
	if (i == 1)
	{
		vrijeme[i] = '0';
		i--;
	}
	if (i == 0)
	{
		vrijeme[i] = '0';
		i--;
	}
	return vrijeme;
}

void citajJoystick()
{
	t.start();
	crtaj();
	while (1)
	{
		if (Ox>0.75)
		{
			rotirajLijevo();
			crtajRotacijaLijevo();
			wait(0.49);
			crtaj();
		}
		else if (Ox<0.25)
		{
			rotirajDesno();
			crtajRotacijaDesno();
			wait(0.49);
			crtaj();
		}
		else if (Oy<0.25)
		{
			crtaj2D();
			wait(0.49);
		}
		else if (Oy>0.75)
		{
			pravo();
			if (mozePravo())
				crtajNaprijed();
			wait(0.49);
			crtaj();
		}
		wait(0.25);
		if (x == 15 && y == 1)
		{
			t.stop();
			lcd.clear();
			lcd.printString("KRAJ!", 28, 1);
			lcd.printString("VRIJEME:", 20, 2);
			lcd.printString(dajVrijeme(), 28, 3);
			lcd.refresh();
			while (1);
		}

	}


}

int main() {
	lcd.init();
	nodelay(stdscr, TRUE);
	std::thread first(readInput);

	int i = 0;
	while (1) {
		lcd.clear();
		linije();
		switch (i)
		{
		case 0:
			desni();
			break;
		case 1:
			lijevi();
			break;
		case 2:
			daljiDesni();
			break;
		case 3:
			daljiLijevi();
			break;
		case 4:
			skriveniDesni();
			break;
		case 5:
			skriveniLijevi();
			break;
		case 6:
			dalji();
			break;
		case 7:
			blizi();
			break;
		case 8:
			desni();
			lijevi();
			break;
		case 9:
			daljiDesni();
			daljiLijevi();
			break;
		case 10:
			blizi();
			skriveniDesni();
			skriveniLijevi();
			break;
		case 11:
			i = 0;
		}
		lcd.refresh();
		if (SW == true)
			citajJoystick();
		i++;
		wait(0.5);
	}
}
