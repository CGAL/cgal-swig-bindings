// ------------------------------------------------------------------------------
// Copyright (c) 2016 GeometryFactory (FRANCE)
// SPDX-License-Identifier: GPL-3.0-or-later OR LicenseRef-Commercial
// ------------------------------------------------------------------------------ 

package CGAL.Java;

import java.lang.RuntimeException;

public class SWIGCGALException extends java.lang.RuntimeException {
  private String message;

  public SWIGCGALException(String msg)
  {
    message=msg;
  }

  public String getMessage()
  {
    return message;
  }
}
