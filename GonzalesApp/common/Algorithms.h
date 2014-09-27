#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#endif // ALGORITHMS_H

namespace Common
{

template<class ITER, class VALUE>
ITER right_outer_bound(ITER begin, ITER end, const VALUE& val)
{
    ITER it = end;

    do
    {
        --it;
        if(*it <= val)
            return it;

    } while(it != begin);

    return end;
}



}
