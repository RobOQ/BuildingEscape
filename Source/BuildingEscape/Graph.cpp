// Copyright Robert O'Quinn 2017

#include "Graph.h"
#include "Vertex.h"
#include "GraphEdge.h"

Graph::Graph() :
	vertices_(),
	edges_()
{
}

Graph::~Graph()
{
	for (auto * vert : vertices_)
	{
		delete vert;
	}

	for (auto * edge : edges_)
	{
		delete edge;
	}
}

void Graph::AddVertex(AActor* actor)
{
	vertices_.Add(new Vertex(actor));
}

void Graph::RemoveVertex(AActor* actor)
{
	Vertex** vert = vertices_.FindByPredicate([=](Vertex* v) { return v->GetActor() == actor; });
	
	edges_.RemoveAll([=](GraphEdge* e) { return e->GetFirst() == *vert || e->GetSecond() == *vert; });

	if(*vert)
	{
		vertices_.Remove(*vert);
	}

	delete (*vert);
}

bool Graph::HasVertexWithActor(AActor* actor)
{
	return vertices_.ContainsByPredicate([=](Vertex* v) { return v->GetActor() == actor; });
}

Vertex* Graph::GetVertex(AActor* actor)
{
	Vertex** vert = vertices_.FindByPredicate([=](Vertex* v) { return v->GetActor() == actor; });

	return *vert;
}

void Graph::AddEdge(AActor* first, AActor* second)
{
	if (!HasEdge(first, second))
	{
		Vertex* firstVert = GetVertex(first);
		Vertex* secondVert = GetVertex(second);

		edges_.Add(new GraphEdge(firstVert, secondVert));
	}
}

void Graph::RemoveEdge(AActor* first, AActor* second)
{
	GraphEdge* edge = GetEdge(first, second);

	if (edge)
	{
		edges_.Remove(edge);
	}
}

bool Graph::HasEdge(AActor* first, AActor* second)
{
	return edges_.ContainsByPredicate([=](GraphEdge* e)
	{
		return (e->GetFirst()->GetActor() == first && e->GetSecond()->GetActor() == second)
			|| (e->GetSecond()->GetActor() == first && e->GetFirst()->GetActor() == second);
	});
}

GraphEdge* Graph::GetEdge(AActor* first, AActor* second)
{
	GraphEdge** edge = edges_.FindByPredicate([=](GraphEdge* e)
	{
		return (e->GetFirst()->GetActor() == first && e->GetSecond()->GetActor() == second)
			|| (e->GetSecond()->GetActor() == first && e->GetFirst()->GetActor() == second);
	});

	return *edge;
}
