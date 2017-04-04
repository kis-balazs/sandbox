#include <graphics.h>
#include <iostream>
using namespace std;

class   PontG
{
    protected :
        int x;
        int y;
        int szin;

    public :
        PontG(int x1 = 100, int y1 = 100, int sz = 6)
        {
            x = x1;
            y = y1;
            szin = sz;
        }
        void    draw()
        {
            putpixel(x,y,szin);
        }
        void    erase()
        {
            putpixel(x,y,0);
        }
        void    fel()
        {
            y -= 5;
        }
        void    le()
        {
            y += 5;
        }
        void    bal()
        {
            x -= 5;
        }
        void    jobb()
        {
            x += 5;
        }
        int    x_get()
        {
            return x;
        }
        int     y_get()
        {
            return y;
        }
};
class KorG : public PontG
{
    private:
    int sug;
    public:
        KorG(int ksug=100)
        {
            sug=ksug;
        }
        void draw()
        {
            setcolor(szin);
            circle(x,y,sug);
        }
};
int     main()
{
    int gdriver = DETECT, gmode;
    initgraph(&gdriver, &gmode, "");
    KorG p;
    while(true){
         if(GetAsyncKeyState( VK_UP ) & 0x8000) p.fel();
         if(GetAsyncKeyState( VK_DOWN ) & 0x8000) p.le();
         if(GetAsyncKeyState( VK_LEFT ) & 0x8000) p.bal();
         if(GetAsyncKeyState( VK_RIGHT ) & 0x8000) p.jobb();
         //if(GetAsyncKeyState( 'C' ) & 0x8000)
          Sleep(10);
          p.draw();
    }
    getch();
    return (0);
}
