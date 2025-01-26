#pragma once

#include <vector>
#include <memory>
#include "Model.h"

class ObjectManager
{
public:
    ObjectManager(): object_nId(0), current_selected_object(0) {}
    ~ObjectManager();

    int object_nId;
    unsigned int current_selected_object;

    void AddObject(const std::string& path);

    void DeleteObject(const int& n);

    void Update();

    void Clear();

    std::vector <std::shared_ptr<Model>>& GetObjects() { return m_Objects; }

private:
    std::vector <std::shared_ptr<Model>> m_Objects;
    std::vector<std::shared_ptr<Model>> m_ObjectsToAdd;
    std::vector<int> m_ObjectsToDelete;
};
