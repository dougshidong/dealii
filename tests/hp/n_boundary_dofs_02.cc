// ---------------------------------------------------------------------
//
// Copyright (C) 2008 - 2015 by the deal.II authors
//
// This file is part of the deal.II library.
//
// The deal.II library is free software; you can use it, redistribute
// it, and/or modify it under the terms of the GNU Lesser General
// Public License as published by the Free Software Foundation; either
// version 2.1 of the License, or (at your option) any later version.
// The full text of the license can be found in the file LICENSE at
// the top level of the deal.II distribution.
//
// ---------------------------------------------------------------------



// test that hp::DoFHandler::n_boundary_dofs() yields the correct
// results in 1d, even if there are more than two boundary vertices


#include "../tests.h"
#include <deal.II/base/logstream.h>
#include <deal.II/base/tensor.h>
#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/intergrid_map.h>
#include <deal.II/base/utilities.h>
#include <deal.II/hp/dof_handler.h>
#include <deal.II/fe/fe_system.h>
#include <deal.II/fe/fe_q.h>
#include <deal.II/fe/fe_dgq.h>
#include <deal.II/hp/fe_collection.h>

#include <fstream>
#include <cstdlib>


template <int spacedim>
void test()
{
  // create a triangulation that spans the disjoint interval [0,1] \union [2,3]
  Triangulation<1,spacedim> triangulation_1;
  GridGenerator::hyper_cube(triangulation_1, 0, 1);

  Triangulation<1,spacedim> triangulation_2;
  GridGenerator::hyper_cube(triangulation_2, 2, 3);

  Triangulation<1,spacedim> triangulation;
  GridGenerator::merge_triangulations(triangulation_1,
                                      triangulation_2,
                                      triangulation);


  hp::FECollection<1,spacedim> fe;
  fe.push_back (FESystem<1,spacedim>(FE_Q<1,spacedim>(1),1,
                                     FE_DGQ<1,spacedim>(1), 1));
  fe.push_back (FESystem<1,spacedim>(FE_Q<1,spacedim>(2),2));

  hp::DoFHandler<1,spacedim> dof_handler (triangulation);

  unsigned int index=0;
  for (typename hp::DoFHandler<1,spacedim>::active_cell_iterator
       cell = dof_handler.begin_active();
       cell != dof_handler.end(); ++cell, ++index)
    cell->set_active_fe_index (index);

  dof_handler.distribute_dofs (fe);

  const unsigned int N = dof_handler.n_boundary_dofs();
  deallog << N << std::endl;
}


int main()
{
  initlog();
  deallog.threshold_double(1.e-10);

  deallog.push("2d");
  test<2>();
  deallog.pop();

  deallog.push("3d");
  test<3>();
  deallog.pop();
}
