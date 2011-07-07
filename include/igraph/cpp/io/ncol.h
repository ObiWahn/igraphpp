/* vim:set ts=4 sw=4 sts=4 et: */

#ifndef IGRAPHPP_IO_NCOL_H
#define IGRAPHPP_IO_NCOL_H

#include <igraph/cpp/graph.h>

namespace igraph {

/// Reads a graph from an NCOL file
/**
 * \todo  handle the predefnames argument
 */
Graph read_ncol(FILE* instream, bool names=true,
        AddWeights weights = IGRAPH_ADD_WEIGHTS_IF_PRESENT,
        bool directed=true);

}         // end of namespace

#endif    // IGRAPHPP_IO_NCOL_H
