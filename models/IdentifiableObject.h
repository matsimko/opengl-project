#pragma once
#include "Renderable.h"
#include <vector>

class IdentifiableObject : public Renderable {
private:
	GLuint id;

	//I could use a std::map as well

	static int maxObjectsWithId;
	static std::vector<IdentifiableObject*> objectsWithId;
	static std::vector<int> freeIndexes;

public:
	IdentifiableObject(bool uniqueId = false);

	static IdentifiableObject* getObjectById(GLuint id);
	static IdentifiableObject* removeObjectById(GLuint id);

	// Inherited via Renderable
	virtual GLuint getId() override;

	bool hasUniqueId();
};
