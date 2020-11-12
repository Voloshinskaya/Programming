
#ifndef SO4ET_H
#define SO4ET_H

int so4et(int j, int h)
{
	return (factor(j)) / ((factor(h)) * (factor(10 - h)));
}