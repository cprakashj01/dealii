// ---------------------------------------------------------------------
//
// Copyright (C) 2014 - 2018 by the deal.II authors
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


// Read the file side.iges, attach it to a projector, create a
// single-cell Triangulation, ask the center of the single cell, and
// then repeat by using the version which queries the manifold.

#include "../tests.h"

#include <deal.II/opencascade/boundary_lib.h>

#include <deal.II/grid/tria.h>
#include <deal.II/grid/tria_accessor.h>
#include <deal.II/grid/grid_out.h>
#include <deal.II/grid/tria_iterator.h>
#include <deal.II/grid/grid_generator.h>
#include <deal.II/grid/manifold_lib.h>

#include <gp_Pnt.hxx>
#include <gp_Dir.hxx>
#include <gp_Ax2.hxx>
#include <GC_MakeCircle.hxx>
#include <BRepBuilderAPI_MakeEdge.hxx>
#include <BRepBuilderAPI_MakeFace.hxx>
#include <BRepBuilderAPI_MakeWire.hxx>
#include <TopoDS_Wire.hxx>
#include <TopoDS_Edge.hxx>
#include <TopoDS_Face.hxx>
#include <BRepPrimAPI_MakeSphere.hxx>


using namespace OpenCASCADE;

int main ()
{
  initlog();

  TopoDS_Shape sh = read_IGES(SOURCE_DIR "/iges_files/wigley.iges", 0.001);
  std::vector<TopoDS_Face> faces;
  std::vector<TopoDS_Edge> edges;
  std::vector<TopoDS_Vertex> vertices;

  extract_geometrical_shapes(sh, faces, edges, vertices);


  // Create a boundary projector on the first face.
  DirectionalProjectionBoundary<2,3> boundary(faces[0], Point<3>(0.,1.,0.));

  // Create a Triangulation with a single cell
  Triangulation<2,3> tria;
  create_triangulation(faces[0], tria);

  // Set the boundary
  tria.set_manifold(1, boundary);
  tria.begin()->set_all_manifold_ids(1);

  deallog << "Ncells: " << tria.n_active_cells() << std::endl
          << "Cell[0] center: " << tria.begin()->center() << std::endl
          << "Projected center: " << tria.begin()->center(true) << std::endl;


  return 0;
}
