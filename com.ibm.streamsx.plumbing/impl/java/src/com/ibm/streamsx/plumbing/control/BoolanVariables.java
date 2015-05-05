package com.ibm.streamsx.plumbing.control;

import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import com.ibm.streams.function.model.Function;
import com.ibm.streams.operator.control.variable.ControlVariableAccessor;


public class BoolanVariables {
	
	private static final Map<String,ControlVariableAccessor<Boolean>> variables = new HashMap<>();
	
	@Function(stateful=true, description=Descriptions.BOOLEAN_CREATE_DESC)
	public static boolean createBooleanControlVariable(String name, boolean shared, boolean initialValue) {		
		ControlVariableAccessor<Boolean> variable =
				Controls.getControlPlaneContext().createBooleanControlVariable(name, shared, initialValue);
		variables.put(name, variable);
		return false;
	}
	
	@Function(stateful=true, description=Descriptions.BOOLEAN_SET_DESC)
	public static void setBooleanControlVariable(String name, boolean value) throws IOException, InterruptedException {		
		getAccessor(name).setValue(value);
	}
	
	@Function(description=Descriptions.BOOLEAN_GET_DESC)
	public static boolean getBooleanControlVariable(String name) throws IOException, InterruptedException {		
		return (boolean) getAccessor(name).getValue();
	}
	
	private static ControlVariableAccessor<Boolean> getAccessor(String name) {
		ControlVariableAccessor<Boolean> accessor = variables.get(name);
		if (accessor != null)
			return accessor;
		
		throw new IllegalStateException("Control variable " + name + " not created!");
	}
}
