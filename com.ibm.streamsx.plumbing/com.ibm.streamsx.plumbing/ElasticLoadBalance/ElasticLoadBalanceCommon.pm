# Copyright (C) 2015 International Business Machines Corporation. 
# All Rights Reserved.

package ElasticLoadBalanceCommon;
use strict;
use warnings;

sub verify($) 
{
    my ($model) = @_;
    my $numOutputPorts = $model->getNumberOfOutputPorts();
    my $inputPort = $model->getInputPortAt(0);

    # check matching schemas
    my $inputTupleType = $inputPort->getCppTupleType();
    for (my $i = 0; $i < $numOutputPorts; $i++) {
        my $op = $model->getOutputPortAt($i);
        SPL::CodeGen::exitln(SPL::Msg::STDTK_OUTPUT_SCHEMA_NOT_MATCHING_INPUT($i, 0),
                           $op->getSourceLocation()) 
            if $inputTupleType ne $op->getCppTupleType();
    }
}

1;
