#ifndef __VECUTILS_H__
#define __VECUTILS_H__

//***************************************************************************************************************

class CVec
{
public:
    explicit CVec() : x(0), y(0)
    {}

    explicit CVec(int nx, int ny) : x(nx), y(ny)
    {}

public:
    int x;
    int y;
};

//***************************************************************************************************************

inline CVec operator+(CVec lh, CVec rh)
{ return CVec(lh.x + rh.x, lh.y + rh.y); }

inline CVec operator*(int val, CVec vec)
{ return CVec(vec.x * val, vec.y * val); }

inline CVec operator*(CVec vec, int val)
{ return CVec(vec.x * val, vec.y * val); }

//***************************************************************************************************************

#endif
