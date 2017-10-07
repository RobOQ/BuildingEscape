// Copyright Robert O'Quinn 2017

#pragma once

#include "CoreMinimal.h"

class Vertex;

/**
 * Edge in a graph.
 */
class BUILDINGESCAPE_API GraphEdge
{
public:
	GraphEdge(Vertex* first, Vertex* second);
	~GraphEdge();

	inline Vertex* GetFirst() { return first_; }
	inline Vertex* GetSecond() { return second_; }

private:
	Vertex* first_;
	Vertex* second_;
};
