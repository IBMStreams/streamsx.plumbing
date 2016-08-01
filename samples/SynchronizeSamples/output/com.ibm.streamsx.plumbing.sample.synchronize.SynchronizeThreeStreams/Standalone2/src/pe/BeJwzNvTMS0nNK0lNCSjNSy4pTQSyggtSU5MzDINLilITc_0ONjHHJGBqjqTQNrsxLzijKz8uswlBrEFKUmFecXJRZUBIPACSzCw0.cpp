// eJwzYHQsLclnNGX0zEtJzStJTQkozUsuKU0EsoILUlOTMwyDS4pSE3MZcYmj8SrzkjOK8vMyq9DVhRQl5hUnF2UWlAAAWPAqBp


#include "BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

using namespace SPL;

#define MYPE BeJwzNvTMS0nNK0lNCSjNSy4pTQSyggtSU5MzDINLilITc_0ONjHHJGBqjqTQNrsxLzijKz8uswlBrEFKUmFecXJRZUBIPACSzCw0



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}

MAKE_PE(SPL::MYPE);

