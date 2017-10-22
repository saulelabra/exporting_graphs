#include <iostream>
#include <fstream>
#include <chrono>
#include "stdafx.h"


void GraphML(PUNGraph graph);
void GEXF(PUNGraph graph);
void GDF(PUNGraph graph);
void JSON(PUNGraph graph);


using namespace std::chrono;

//Un main para exportar un grafo a formatos como JSON,
//GraphML, GDF y GEXF. Esto para abrirlos en Gephi



int main(int argc, char* argv[]) {

	PUNGraph g = TSnap::LoadEdgeList<PUNGraph>("migrafo.txt", 0, 1);

	high_resolution_clock::time_point t1 = high_resolution_clock::now();
	GraphML(g);
	high_resolution_clock::time_point t2 = high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "GraphML: " << duration << std::endl;

	t1 = high_resolution_clock::now();
	GEXF(g);
	t2 = high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "GEXF: " << duration << std::endl;

	t1 = high_resolution_clock::now();
	GDF(g);
	t2 = high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "GDF: " << duration << std::endl;

	t1 = high_resolution_clock::now();
	JSON(g);
	t2 = high_resolution_clock::now();
	duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
	std::cout << "JSON: " << duration << std::endl;



	return 0;
}



void GraphML(PUNGraph graph)
{
	std::ofstream file("output/grafo.graphml");
	if (file.is_open())
	{
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<graphml xmlns=\"http://graphml.graphdrawing.org/xmlns\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://graphml.graphdrawing.org/xmlns http://graphml.graphdrawing.org/xmlns/1.0/graphml.xsd\">\n";
		file << "<graph id=\"G\" edgedefault=\"directed\">\n";

		for (PUNGraph::TObj::TNodeI NI = graph->BegNI(); NI < graph->EndNI(); NI++)
		{
			file << "<node id=\"" << NI.GetId() << "\"/>\n";
		}

		int i = 1;
		for (PUNGraph::TObj::TEdgeI EI = graph->BegEI(); EI < graph->EndEI(); EI++, ++i)
		{
			file << "<edge id=\"e" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\"/>\n";
		}

		file << "</graph>\n";
		file << "</graphml>\n";
		file.close();
	}
}


void GEXF(PUNGraph graph)
{
	std::ofstream file("output/grafo.gexf");
	if (file.is_open())
	{
		file << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
		file << "<gexf xmlns=\"http://www.gexf.net/1.2draft\" version=\"1.2\">\n";
		file << "<graph mode=\"static\" defaultedgetype=\"directed\">\n";

		file << "<nodes>\n";
		for (PUNGraph::TObj::TNodeI NI = graph->BegNI(); NI < graph->EndNI(); NI++)
		{
			file << "<node id=\"" << NI.GetId() << "\" />\n";
		}
		file << "</nodes>\n";

		file << "<edges>\n";
		int i = 1;
		for (PUNGraph::TObj::TEdgeI EI = graph->BegEI(); EI < graph->EndEI(); EI++, ++i)
		{
			file << "<edge id=\"" << i << "\" source=\"" << EI.GetSrcNId() << "\" target=\"" << EI.GetDstNId() << "\" />\n";
		}
		file << "</edges>\n";

		file << "</graph>\n";
		file << "</gexf>\n";
		file.close();
	}
}

void GDF(PUNGraph graph)
{
	std::ofstream file("output/grafo.gdf");
	if (file.is_open())
	{
		file << "nodedef>name VARCHAR\n";
		for (PUNGraph::TObj::TNodeI NI = graph->BegNI(); NI < graph->EndNI(); NI++)
		{
			file << NI.GetId() << "\n";
		}

		file << "edgedef>source VARCHAR, destination VARCHAR\n";
		for (PUNGraph::TObj::TEdgeI EI = graph->BegEI(); EI < graph->EndEI(); EI++)
		{
			file << EI.GetSrcNId() << ", " << EI.GetDstNId() << "\n";
		}

		file.close();
	}
}

void JSON(PUNGraph graph)
{
	std::ofstream file("output/grafo.json");
	if (file.is_open())
	{
		file << "{ \"graph\": {\n";
		file << "\"nodes\": [\n";
		for (PUNGraph::TObj::TNodeI NI = graph->BegNI(); NI < graph->EndNI();)
		{
			file << "{ \"id\": \"" << NI.GetId() << "\" }";
			if (NI++ == graph->EndNI())
				file << " ],\n";
			else
				file << ",\n";
		}

		file << "\"edges\": [\n";
		for (PUNGraph::TObj::TEdgeI EI = graph->BegEI(); EI < graph->EndEI(); )
		{
			file << "{ \"source\": \"" << EI.GetSrcNId() << "\", \"target\": \"" << EI.GetDstNId() << "\" }";
			if (EI++ == graph->EndEI())
			{
				file << " ]\n";
			}
			else
			{
				file << ",\n";
			}
		}
		file << "} }";

		file.close();
	}
}
