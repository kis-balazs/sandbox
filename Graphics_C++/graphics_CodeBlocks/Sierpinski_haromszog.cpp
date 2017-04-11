#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <conio.h>

// ====================================================================================== //
// =============================== Sierpinski Haromszog ================================= //
// ====================================================================================== //

void haromszog(int x1, int y1, int x2, int y2, int x3, int y3, int color){

	setcolor(color+1);

	line(x1, y1, x2, y2);
	line(x2, y2, x3, y3);
	line(x3, y3, x1, y1);

	//char *fname[] = { "EMPTY_FILL", "SOLID_FILL", "LINE_FILL", "LTSLASH_FILL", "SLASH_FILL", "BKSLASH_FILL", "LTBKSLASH_FILL", "HATCH_FILL", "XHATCH_FILL", "INTERLEAVE_FILL", "WIDE_DOT_FILL", "CLOSE_DOT_FILL", "USER_FILL" };
	setfillstyle(XHATCH_FILL, color);
	floodfill((x1+x2+x3)/3, (y1+y2+y3)/3, color+1);
}


void sierpinski(int x1, int y1, int x2, int y2, int x3, int y3, int n){

	int x4 = (x1 + x2)/2;
	int x5 = (x2 + x3)/2;
	int x6 = (x3 + x1)/2;

	int y4 = (y1 + y2)/2;
	int y5 = (y2 + y3)/2;
	int y6 = (y3 + y1)/2;

	if (n==1){
		haromszog(x1, y1, x2, y2, x3, y3, 13);
	}
	else{
		if (n%2 == 1) {
			haromszog(x1, y1, x2, y2, x3, y3, 9);
		}
		else{
			haromszog(x1, y1, x2, y2, x3, y3, 4);
		}

		sierpinski(x1, y1, x4, y4, x6, y6, n-1);
		sierpinski(x4, y4, x2, y2, x5, y5, n-1);
		sierpinski(x6, y6, x5, y5, x3, y3, n-1);
	}
}


int main()
{
	int graphdriver, graphmode;
	int x, y, hossz;
	graphdriver = DETECT;
	initgraph(&graphdriver, &graphmode, " ");

	x=getmaxx()/2;
	y=getmaxy()/2;

	printf("Kerem a haromszog oldal-hosszat: ");
	scanf("%d", &hossz);

	/// ====== RAJZOLAS KOZEPRE (amennyire lehetseges)!!! ================ ///
	int magassag = (int) hossz * 0.866;		// ===== 0.866 = sin(60) ===== ///
	sierpinski(x, y-magassag/2, x-hossz/2, y+magassag/2, x+hossz/2, y+magassag/2, 6);

	getch();
	return 0;
}
