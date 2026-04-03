#pragma once

#include <memory>
#include <string>
#include <concepts>
#include <unordered_map>
#include <fstream>
#include <algorithm>
#include <format>
#include <iostream>
#include <ios>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

template<typename T>
concept serializable = requires(T t, nlohmann::json & j, const nlohmann::json & cj)
{
    { t.Id } -> std::convertible_to<int>;
};

template <serializable T>
class DataHandler
{
private:
    std::unordered_map<int, T> data_;

	std::string filepath_;

    void CreateTemplateJsonFile();
	
    void SaveToFile(const json& data);

    json ReadFromFile();

    int GetNextId(const json& data);

    json ResolvePrototype(json& item, json& data);

    static bool IsEmpty(std::ifstream& pFile)
    {
        return pFile.peek() == std::ifstream::traits_type::eof();
    }

public:
    DataHandler(std::string filepath);
    T& GetById(int id);
    
    std::unordered_map<int, T>& GetAll();
    void Create(T& newItem);
    void DeleteById(int id);
    void UpdateById(const T& toItem);
};

template<serializable T>
inline void DataHandler<T>::CreateTemplateJsonFile()
{
    json oldData = ReadFromFile();

    bool hasData = oldData.size() > 0;

    if (hasData)
    {
        return;
    }

    T item;
    item.Id = 0;

    json data;
    data[std::to_string(item.Id)] = item;

    SaveToFile(data);
}

template<serializable T>
void DataHandler<T>::SaveToFile(const json& data)
{
    std::ofstream outputFile(filepath_);
    outputFile << data.dump(DataHandlingConstants::IndentAmount);
    outputFile.close();
}

template<serializable T>
json DataHandler<T>::ReadFromFile()
{
    std::ifstream inputFile(filepath_);

    if (!IsEmpty(inputFile))
    {
        json data;
        inputFile >> data;
        return data;
    }

    return json();
}

template<serializable T>
inline int DataHandler<T>::GetNextId(const json& data)
{
    int nextId = 0;
    for (auto& [id, val] : data.items()) 
    {
        nextId = std::max(nextId, std::stoi(id) + 1);
    }
    return nextId;
}

template<serializable T>
inline json DataHandler<T>::ResolvePrototype(json& item, json& data)
{
    std::string prototypeId = item[DataHandlingConstants::PrototypeFieldKey];
    if (!data.contains(prototypeId))
    {
#ifdef _DEBUG
        std::cout << std::format("prototype id `{}` not found!", prototypeId);
#endif // _DEBUG
        return json();
    }

    json resolved = data[prototypeId];
    for (auto& [key, value] : item.items())
    {
        if (key == DataHandlingConstants::PrototypeFieldKey)
        {
            continue;
        }
        resolved[key] = value;
    }

    return resolved;
}

template<serializable T>
inline DataHandler<T>::DataHandler(std::string filepath) : filepath_(filepath)
{
    CreateTemplateJsonFile();
}

template<serializable T>
T& DataHandler<T>::GetById(int id)
{
    auto result = data_.find(id);
    if (result != data_.end())
    {
        return result->second;
    }

    json data = ReadFromFile();

    if (data.find(std::to_string(id)) == data.end())
    {
        return nullptr;
    }

    json item = data[std::to_string(id)];

    bool isPrototype = item.contains(DataHandlingConstants::PrototypeFieldKey);
    T entity = isPrototype ? ResolvePrototype(item, data) : item;
    entity.Id = id;

    data_[id] = entity;
    return data_[id];
}

template<serializable T>
inline std::unordered_map<int, T>& DataHandler<T>::GetAll()
{
    return data_;
}

template<serializable T>
void DataHandler<T>::Create(T& newItem)
{
    json oldData = ReadFromFile();

    newItem.Id = GetNextId(oldData);    

    data_[newItem.Id] = newItem;

    json data = newItem;
    oldData[std::to_string(newItem.Id)] = data;

    SaveToFile(oldData);
}

template<serializable T>
inline void DataHandler<T>::DeleteById(int id)
{
    json data = ReadFromFile();

    std::string key = std::to_string(id);
    if (data.contains(key))
    {
        data.erase(key);
        SaveToFile(data);  
        return;
    }

#ifdef _DEBUG
    std::cout << std::format("{}: entity with id `{}` not found for delete!", filepath_, id);
#endif // _DEBUG

}

template<serializable T>
inline void DataHandler<T>::UpdateById(const T& toItem)
{
    json data = ReadFromFile();

    std::string key = std::to_string(toItem.Id);
    if (data.contains(key))
    {
        data[key] = toItem;
        SaveToFile(data);
        return;
    }

#ifdef _DEBUG
    std::cout << std::format("{}: entity with id `{}` not found for update!", filepath_, toItem.Id);
#endif // _DEBUG
}
