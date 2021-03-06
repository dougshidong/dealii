// ---------------------------------------------------------------------
//
// Copyright (C) 2005 - 2018 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE.md at
// the top level directory of deal.II.
//
// ---------------------------------------------------------------------


// test Utilities::fixed_power

#include <deal.II/base/utilities.h>

#include "../tests.h"


template <int dim>
void
test()
{
  deallog << Utilities::fixed_power<dim>(2) << std::endl;
  deallog << Utilities::fixed_power<dim>(-2) << std::endl;
  deallog << Utilities::fixed_power<dim>(2.5) << std::endl;
  deallog << Utilities::fixed_power<dim>(-2.5) << std::endl;
  deallog << std::endl;
}



int
main()
{
  initlog();

  test<1>();
  test<2>();
  test<3>();
  test<4>();
}
