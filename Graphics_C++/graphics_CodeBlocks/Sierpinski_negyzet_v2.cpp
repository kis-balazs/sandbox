#include <graphics.h> 
#include <stdlib.h>
#include <stdio.h>
#include <iostream.h>
#include <conio.h>

// ====================================================================================== //
// =============================== Sierpinski Negyzet V2 ================================ //
// ====================================================================================== //



void negyzet(int x0, int y0, int h, int color){
	x0 = x0 - h/2;
	y0 = y0 - h/2;
	
	rectangle(x0, y0, x0+h, y0+h);
	
	
	//char *fname[] = { "EMPTY_FILL", "SOLID_FILL", "LINE_FILL", "LTSLASH_FILL", "SLASH_FILL", "BKSLASH_FILL", "LTBKSLASH_FILL", "HATCH_FILL", "XHATCH_FILL", "INTERLEAVE_FILL", "WIDE_DOT_FILL", "CLOSE_DOT_FILL", "USER_FILL" };
	setfillstyle(BKSLASH_FILL, color);
	floodfill(x0+h/2, y0+h/2, WHITE);
}


void sierpinski(int x0, int y0, int h, int n){
	if (n==1){
		negyzet(x0, y0, h, 9);
	}
	else{		
		if (n%2 == 1) {
			negyzet(x0, y0, h, 9);
		}
		else{
			negyzet(x0, y0, h, 4);
		}
		
		sierpinski(x0-h/3, y0-h/3, h/3, n-1);
		sierpinski(x0+h/3, y0-h/3, h/3, n-1);
		sierpinski(x0-h/3, y0+h/3, h/3, n-1);
		sierpinski(x0+h/3, y0+h/3, h/3, n-1);
		
		sierpinski(x0-h/3, y0, h/3, n-1);
		sierpinski(x0+h/3, y0, h/3, n-1);
		sierpinski(x0, y0+h/3, h/3, n-1);
		sierpinski(x0, y0-h/3, h/3, n-1);
		
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
    
	printf("Kerem a negyzet oldal-hosszat: ");
	scanf("%d", &hossz);
    
	sierpinski(x, y, hossz, 5);
  
	getch();
	return 0;
}