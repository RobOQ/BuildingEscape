// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"

class GraphEdge;
class AActor;

/**
 * Vertex in a graph.
 */
class BUILDINGESCAPE_API Vertex
{
public:
	Vertex(AActor* actor);
	~Vertex();

	inline AActor* GetActor() { return actor_; }

private:
	AActor* actor_;
	TArray<GraphEdge*> edges_;
};
