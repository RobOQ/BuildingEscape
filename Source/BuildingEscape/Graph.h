// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"

class Vertex;
class GraphEdge;
class AActor;

/**
 * Implementation of a graph data structure.
 * This could probably be templated, but no need to get fancy for a class that won't see any re-use.
 */
class BUILDINGESCAPE_API Graph
{
public:
	Graph();
	~Graph();

	void AddVertex(AActor* actor);
	void RemoveVertex(AActor* actor);
	bool HasVertexWithActor(AActor* actor);
	Vertex* GetVertex(AActor* actor);

	inline TArray<Vertex*>& GetVertices() { return vertices_; }

	void AddEdge(AActor* first, AActor* second);
	void RemoveEdge(AActor* first, AActor* second);
	bool HasEdge(AActor* first, AActor* second);
	GraphEdge* GetEdge(AActor* first, AActor* second);

private:
	TArray<Vertex*> vertices_;
	TArray<GraphEdge*> edges_;
};
