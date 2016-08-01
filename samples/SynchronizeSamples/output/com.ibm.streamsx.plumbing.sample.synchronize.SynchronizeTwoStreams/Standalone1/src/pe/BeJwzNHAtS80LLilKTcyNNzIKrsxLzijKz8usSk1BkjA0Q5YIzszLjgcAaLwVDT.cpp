// eJwzYHQsLclnNGZ0LUvNCy4pSk3MZQyuzEvOKMrPy6xKTcEhHJyZlw0AW7MVCL


#include "BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

using namespace SPL;

#define MYPE BeJwzNHAtS80LLilKTcyNNzIKrsxLzijKz8usSk1BkjA0Q5YIzszLjgcAaLwVDT



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}

MAKE_PE(SPL::MYPE);

