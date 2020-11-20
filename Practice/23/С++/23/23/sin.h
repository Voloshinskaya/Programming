#ifndef SIN_H
#define SIN_H

double sin(double x, double k)
{
double M = x, summa = x, i;

for(i=1;i<=k;i+=1){
	M = - ((x * x)/(  (2 * i)*(2 * i + 1) ))*M;
	summa = summa + M;
	}
return summa;
}

#endif