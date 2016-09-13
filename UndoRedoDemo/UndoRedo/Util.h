#include "stdafx.h"

template <typename T>
void ContainerDeleter(T& Container)
{
    for (T::iterator iter = Container.begin(); iter != Container.end(); iter++)
    {
        delete (*iter);
    }
    Container.clear();
}
