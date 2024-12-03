#pragma once

#include <vector>
#include <memory>
#include "Model.h"

class ObjectManager
{
public:
    ObjectManager() {};
    ~ObjectManager();
    int object_nId = 0;
    unsigned int current_selected_object = 0;

    void addObject(std::string& path);

    void update();

    void clear();

    std::vector <std::shared_ptr<Model>>& getObjects()
    {
        return m_objects;
    }

private:
    std::vector <std::shared_ptr<Model>> m_objects;
    std::vector<std::shared_ptr<Model>> m_objectsToAdd;
};
