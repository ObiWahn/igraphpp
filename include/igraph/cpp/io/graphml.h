/* vim:set ts=4 sw=4 sts=4 et: */

#ifndef IGRAPHPP_IO_GRAPHML_H
#define IGRAPHPP_IO_GRAPHML_H

#include <igraph/cpp/graph.h>

namespace igraph {

/// Reads a graph from a GraphML file
Graph read_graphml(FILE* instream, int index=0);

}         // end of namespace

#endif    // IGRAPHPP_IO_GRAPHML_H

