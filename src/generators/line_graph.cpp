/* vim:set ts=4 sw=4 sts=4 et: */

#include <igraph/igraph_structural.h>
#include <igraph/cpp/error.h>
#include <igraph/cpp/graph.h>
#include <igraph/cpp/generators/line_graph.h>

namespace igraph {

Graph line_graph(const Graph& graph) {
    std::auto_ptr<igraph_t> result(new igraph_t);
    IGRAPH_TRY(igraph_linegraph(graph.c_graph(), result.get()));
    return Graph(result.release());
}

}         // end of namespaces
