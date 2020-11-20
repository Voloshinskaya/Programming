#ifndef _FACTORIAL_H_
#define _FACTORIAL_H_

int fac(int s)
{
    int answer = 1;
    for (int i = 1; i <= s; i++)
    {
        answer = answer * i;
    }
    return answer;
}

#endif