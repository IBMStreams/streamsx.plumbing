package com.ibm.streamsx.plumbing.control;

import com.ibm.streams.operator.PERuntime;
import com.ibm.streams.operator.control.ControlPlaneContext;

public class Controls {
	
	public static ControlPlaneContext getControlPlaneContext() {
		
		ControlPlaneContext cpc =
				PERuntime.getCurrentContext().getOptionalContext(ControlPlaneContext.class);
		
		if (cpc == null)
			throw new IllegalStateException("No Job Control Plane");
		
		return cpc;
	}

}
