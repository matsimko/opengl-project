#include "IdentifiableObject.h"

int IdentifiableObject::maxObjectsWithId = 0xFF; //stencil buffer is usually limited to 8 bits...

//first index is reserved for null obj (id = 0)
std::vector<IdentifiableObject*> IdentifiableObject::objectsWithId = { nullptr };

std::vector<int> IdentifiableObject::freeIndexes;

IdentifiableObject::IdentifiableObject(bool uniqueId)
{
    if (uniqueId) {
        id = objectsWithId.size();
        if (id >= maxObjectsWithId) {
            if (!freeIndexes.empty()) {
                id = freeIndexes.back();
                freeIndexes.pop_back();
            }
            else {
                //there is no free id (I could maybe at least put them to a waiting queue)
                id = 0;
                return;
            }
        }
        objectsWithId.push_back(this);
    }
    else {
        id = 0;
    }
}

IdentifiableObject* IdentifiableObject::getObjectById(GLuint id)
{
    return objectsWithId.at(id); //at throws exception when out of bounds compared to [ ]
}

IdentifiableObject* IdentifiableObject::removeObjectById(GLuint id)
{
    IdentifiableObject* object = objectsWithId.at(id);
    objectsWithId[id] = nullptr;
    freeIndexes.push_back(id); //make the id available
    return object;
}


GLuint IdentifiableObject::getId()
{
    return id;
}

bool IdentifiableObject::hasUniqueId()
{
    return id != 0;
}
