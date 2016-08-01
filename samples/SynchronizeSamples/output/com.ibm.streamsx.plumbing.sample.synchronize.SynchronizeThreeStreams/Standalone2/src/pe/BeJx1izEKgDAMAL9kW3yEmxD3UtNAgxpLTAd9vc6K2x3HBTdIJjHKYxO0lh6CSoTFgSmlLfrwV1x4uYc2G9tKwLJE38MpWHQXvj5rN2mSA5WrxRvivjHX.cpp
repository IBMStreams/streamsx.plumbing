// eJx1izEKgDAMAMmPdHF3dBPiB2oaaFDTEpNBX6_0z4HZ3cB2M4RUGmDSzOuc5lDzSS9iYqfToxumAv_16xWF18ZxTdAC_0lYlXl_1k6LJT3JpPkDnXwvBM


#include "BeJx1izEKgDAMAL9kW3yEmxD3UtNAgxpLTAd9vc6K2x3HBTdIJjHKYxO0lh6CSoTFgSmlLfrwV1x4uYc2G9tKwLJE38MpWHQXvj5rN2mSA5WrxRvivjHX.h"
#include <dst-config.h>
#include <SPL/Runtime/Utility/BackoffSpinner.h>

using namespace SPL;

#define MYPE BeJx1izEKgDAMAL9kW3yEmxD3UtNAgxpLTAd9vc6K2x3HBTdIJjHKYxO0lh6CSoTFgSmlLfrwV1x4uYc2G9tKwLJE38MpWHQXvj5rN2mSA5WrxRvivjHX



MYPE::MYPE(bool isStandalone/*=false*/) 
    : SPL::PE(isStandalone, NULL)
{
   BackoffSpinner::setYieldBehaviour(BackoffSpinner::Auto);
}

MAKE_PE(SPL::MYPE);

