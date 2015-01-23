# begin_generated_IBM_copyright_prolog                             
#                                                                  
# This is an automatically generated copyright prolog.             
# After initializing,  DO NOT MODIFY OR MOVE                       
# **************************************************************** 
# Licensed Materials - Property of IBM                             
# 5724-Y95                                                         
# (C) Copyright IBM Corp.  2010, 2010    All Rights Reserved.      
# US Government Users Restricted Rights - Use, duplication or      
# disclosure restricted by GSA ADP Schedule Contract with          
# IBM Corp.                                                        
#                                                                  
# end_generated_IBM_copyright_prolog                               
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
