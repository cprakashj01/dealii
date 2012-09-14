//----------------------------------------------------------------------
//    $Id$
//    Version: $Name$
//
//    Copyright (C) 2007, 2008, 2010, 2012 by the deal.II authors
//
//    This file is subject to QPL and may not be  distributed
//    without copyright and license information. Please refer
//    to the file deal.II/doc/license.html for the  text  and
//    further information on this license.
//
//----------------------------------------------------------------------
//
// Compute support points

#include "../tests.h"
#include "fe_prolongation_common.h"



int
main()
{
  initlog(__FILE__);
  deallog.threshold_double(1.e-10);

  CHECK_ALL(DGP,0,2);
  CHECK_ALL(DGP,1,2);
  CHECK_ALL(DGP,2,2);
  CHECK_ALL(DGP,3,2);
  CHECK_ALL(DGP,4,2);

  CHECK_ALL(DGP,0,3);
  CHECK_ALL(DGP,1,3);
  CHECK_ALL(DGP,2,3);
}
