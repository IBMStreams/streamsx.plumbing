// eJwzYHQsLclnNGP0zEtJzStJTQkozUsuKU0EsoILUlOTMwyDS4pSE3MZcYlj4xkFZ_0ZlMwZX5iVnFOXnZVah6wkpSswrTi7KLCgBAF4lC6K


#include "BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqj8Q0hfKPgzLzseCPT4Mq85Iyi_1LzMKgydBiFFiXnFyUWZBSXxAJ6_1DEU.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

using namespace SPL;

#define MYPE BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqj8Q0hfKPgzLzseCPT4Mq85Iyi_1LzMKgydBiFFiXnFyUWZBSXxAJ6_1DEU



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}

MAKE_PE(SPL::MYPE);

