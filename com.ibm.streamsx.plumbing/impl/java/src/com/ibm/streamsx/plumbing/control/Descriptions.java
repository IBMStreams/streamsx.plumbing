/*
*******************************************************************************
* Copyright (C) 2015, International Business Machines Corporation. 
* All Rights Reserved. *
*******************************************************************************
*/
package com.ibm.streamsx.plumbing.control;

class Descriptions {
	
	static final String DOUBLE_CREATE_DESC = "Create a `float64` control variable named `name`. " +
			"If `shared` is `true` then the control variable is intended for use by multiple operators," +
			"if `false` then the control variable is intended for use for a single operator." +
			" A control variable may be created by multiple operators, the first will create the MXBean" +
			"representing the control variable, subsequent creates will just reference the exisitng MXBean.";
	
	static final String DOUBLE_GET_DESC = "Get the value of `name` `float64` control variable." +
			" Any operator invoking this function must call `createFloat64ControlVariable`, typically" +
			" in its `logic state` clause, before invoking this function.";
	
	static final String DOUBLE_SET_DESC = "Set the value of `name` `float64` control variable to `value`." +
			" Any operator invoking this function must call `createFloat64ControlVariable`, typically" +
			" in its `logic state` clause, before invoking this function.";
	
	static final String BOOLEAN_CREATE_DESC = "Create a `boolean` control variable named `name`. " +
			"If `shared` is `true` then the control variable is intended for use by multiple operators," +
			"if `false` then the control variable is intended for use for a single operator." +
			" A control variable may be created by multiple operators, the first will create the MXBean" +
			"representing the control variable, subsequent creates will just reference the exisitng MXBean.";
	
	static final String BOOLEAN_GET_DESC = "Get the value of `name` `boolean` control variable." +
			" Any operator invoking this function must call `createBooleanControlVariable`, typically" +
			" in its `logic state` clause, before invoking this function.";
	
	static final String BOOLEAN_SET_DESC = "Set the value of `name` `boolean` control variable to `value`." +
			" Any operator invoking this function must call `createBooleanControlVariable`, typically" +
			" in its `logic state` clause, before invoking this function.";
}
