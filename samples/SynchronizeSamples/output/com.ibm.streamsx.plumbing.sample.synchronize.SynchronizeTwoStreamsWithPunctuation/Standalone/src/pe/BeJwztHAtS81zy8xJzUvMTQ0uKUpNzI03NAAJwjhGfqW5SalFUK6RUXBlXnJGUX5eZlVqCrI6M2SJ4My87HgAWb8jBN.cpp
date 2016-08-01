// eJwzYHQsLclnNGV0LUvNc8vMSc1LzE0NLilKTcwFC0GZfqW5SalFUE5wZV5yRlF_0XmZVagqSGmTh4My8bAC5_0iF_1


#include "BeJwztHAtS81zy8xJzUvMTQ0uKUpNzI03NAAJwjhGfqW5SalFUK6RUXBlXnJGUX5eZlVqCrI6M2SJ4My87HgAWb8jBN.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

using namespace SPL;

#define MYPE BeJwztHAtS81zy8xJzUvMTQ0uKUpNzI03NAAJwjhGfqW5SalFUK6RUXBlXnJGUX5eZlVqCrI6M2SJ4My87HgAWb8jBN



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}

MAKE_PE(SPL::MYPE);

