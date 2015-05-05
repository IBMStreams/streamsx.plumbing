package com.ibm.streamsx.plumbing.control;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.ibm.streams.function.model.Function;
import com.ibm.streams.operator.control.variable.ControlVariableAccessor;


/*
*******************************************************************************
* Copyright (C) 2015, International Business Machines Corporation. 
* All Rights Reserved. *
*******************************************************************************
*/
public class Float64Variables {
	
	private static final Map<String,ControlVariableAccessor<Double>> doubleVariables
	  = new HashMap<String,ControlVariableAccessor<Double>>();
	
	@Function(stateful=true, description=Descriptions.DOUBLE_CREATE_DESC)
	public static boolean createFloat64ControlVariable(String name, boolean shared, double initialValue) {		
		ControlVariableAccessor<Double> variable =
				Controls.getControlPlaneContext().createDoubleControlVariable(name, shared, initialValue);
		doubleVariables.put(name, variable);
		return false;
	}
	
	@Function(stateful=true, description=Descriptions.DOUBLE_SET_DESC)
	public static void setFloat64ControlVariable(String name, double value) throws IOException, InterruptedException {		
		getAccessor(name).setValue(value);
	}
	
	@Function(description=Descriptions.DOUBLE_GET_DESC)
	public static double getFloat64ControlVariable(String name) throws IOException, InterruptedException {		
		return (double) getAccessor(name).getValue();
	}
	
	private static ControlVariableAccessor<Double> getAccessor(String name) {
		ControlVariableAccessor<Double> accessor = doubleVariables.get(name);
		if (accessor != null)
			return accessor;
		
		throw new IllegalStateException("Control variable " + name + " not created!");
	}
}
