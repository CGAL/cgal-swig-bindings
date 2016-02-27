// ------------------------------------------------------------------------------
// Copyright (c) 2016 GeometryFactory (FRANCE)
// Distributed under the Boost Software License, Version 1.0. (See accompany-
// ing file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
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
