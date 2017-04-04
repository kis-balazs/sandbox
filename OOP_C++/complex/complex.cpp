#include <iostream>
#include <math.h>
using namespace std;

class   Complex
{
    private:
        float real;
        float imag;
        friend istream & operator>>(istream &, Complex&);
        friend ostream & operator<<(ostream &, const Complex&);

    public:
        Complex(float r = 0, float im = 0)
        {
            real = r;
            imag = im;
        }
        void    write()
        {
            cout<<real;
            if (imag > 0)
            {
                cout<<"+"<<imag<<"i";
            }
            if (imag < 0)
            {
                cout<<imag<<"i";
            }
            cout<<endl;
        }
        Complex read()
        {
            cout<<"real"<<endl; cin>>real;
            cout<<"imaginary"<<endl; cin>>imag;
        }
        Complex operator+(Complex& z1)
        {
            Complex z;
            z.real = real + z1.real;
            z.imag = imag + z1.imag;
            return z;

        }
        Complex operator-(Complex& z1)
        {
            Complex z;
            z.real = real - z1.real;
            z.imag = imag - z1.imag;
            return z;
        }
        Complex operator*(Complex& z1)
        {
            Complex z;
            z.real = real * z1.real - imag * z1.imag;
            z.imag = real * z1.imag + imag * z1.real;
            return z;
        }
        Complex operator/(Complex& z1)
        {
            Complex z;
            float den = (z1.real * z1.real + z1.imag *  z1.imag);
            z.real = (real * z1.real + imag * z1.imag) / den;
            z.imag = (z1.imag * real + real * z1.imag) / den;
            return z;
        }
        /*void    sum(Complex z1, Complex z2)
        {
            real = z1.real + z2.real;
            imag = z1.imag + z2.imag;
        }
        void    substr(Complex z1, Complex z2)
        {
            real = z1.real - z2.real;
            imag = z1.imag - z2.imag;
        }
        void    multipl(Complex z1, Complex z2)
        {
            real = z1.real * z2.real - z1.imag * z2.imag;
            imag = z1.real * z2.imag + z1.imag * z2.real;
        }
        void    divide(Complex z1, Complex z2)
        {
            float den = (z2.real * z2.real + z2.imag *  z2.imag);
            real = (z1.real * z2.real + z1.imag * z2.imag) / den;
            imag = (z2.imag * z1.real + z1.real * z2.imag) / den;
        }*/
        float   modul()
        {
            return (sqrt(real * real + imag * imag));
        }

};
istream & operator>>(istream & is, Complex & c) {
    is>>c.real;
    is>>c.imag;
    is.get();
    return is;
 }

ostream & operator<<(ostream & os, const Complex & c) {
   os<<c.real;
   if (c.imag >= 0) os<<"+"<<c.imag<<"i";
    else os<<c.imag<<"i";
   return os;
 }

int     main()
{
    Complex z0(1,2);
    Complex z1(2,3);
    Complex z2,z3;
    Complex z;

    /*z1.read();
    cout<<"z2(z0 + z1) = "; z2.sum(z0,z1);
    z2.write();
    cout<<"z3(z0 - z1) = "; z2.substr(z0,z1);
    z2.write();
    cout<<"z4(z0 * z1) = "; z2.multipl(z0,z1);
    z2.write();
    cout<<"z4(z0 / z1) = "; z2.divide(z0,z1);
    z2.write();*/
    //z3 = z0 / z1;
    //z3.write();
    cin>>z;
    cout<<z;
    return (0);
}
