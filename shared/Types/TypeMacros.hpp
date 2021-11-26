#pragma once

#include "beatsaber-hook/shared/config/rapidjson-utils.hpp"

class JSONClass {
    public:
        virtual void Deserialize(const rapidjson::Value& jsonValue) = 0;
        virtual rapidjson::Value Serialize(rapidjson::Document::AllocatorType& allocator) = 0;
};

#define DECLARE_JSON_CLASS(namespaze, name, impl) \
namespace namespaze { \
    class name : public JSONClass { \
        public: \
            void Deserialize(const rapidjson::Value& jsonValue); \
            rapidjson::Value Serialize(rapidjson::Document::AllocatorType& allocator); \
            impl \
    }; \
}

#define DESERIALIZE_METHOD(namespaze, name, impl) \
void namespaze::name::Deserialize(const rapidjson::Value& jsonValue) { \
    impl \
}

#define DESERIALIZE_VALUE(name, jsonName, type) \
if (!jsonValue.HasMember(#jsonName)) throw #jsonName " not found"; \
if (!jsonValue[#jsonName].Is##type()) throw #jsonName ", type expected was: " #type; \
name = jsonValue[#jsonName].Get##type();

#define DESERIALIZE_VALUE_OPTIONAL(name, jsonName, type) \
if(jsonValue.HasMember(#jsonName) && jsonValue[#jsonName].Is##type()) { \
    name = jsonValue[#jsonName].Get##type(); \
} else { \
    name = std::nullopt; \
}

#define DESERIALIZE_CLASS(name, jsonName) \
if (!jsonValue.HasMember(#jsonName)) throw #jsonName " not found"; \
if (!jsonValue[#jsonName].IsObject()) throw #jsonName ", type expected was: JsonObject"; \
name.Deserialize(jsonValue[#jsonName]);

// seems to assume vector is of another json class
#define DESERIALIZE_VECTOR(name, jsonName, type) \
if (!jsonValue.HasMember(#jsonName)) throw #jsonName " not found"; \
name.clear(); \
auto& jsonName = jsonValue[#jsonName]; \
if(jsonName.IsArray()) { \
    for (auto it = jsonName.Begin(); it != jsonName.End(); ++it) { \
        type value; \
        value.Deserialize(*it); \
        name.push_back(value); \
    } \
} else throw #jsonName ", type expected was: JsonArray";

#define DESERIALIZE_VECTOR_BASIC(name, jsonName, type) \
if (!jsonValue.HasMember(#jsonName)) throw #jsonName " not found"; \
name.clear(); \
auto& jsonName = jsonValue[#jsonName]; \
if(jsonName.IsArray()) { \
    for (auto it = jsonName.Begin(); it != jsonName.End(); ++it) { \
        name.push_back(it->Get##type()); \
    } \
} else throw #jsonName ", type expected was: JsonArray";

#define SERIALIZE_METHOD(namespaze, name, impl) \
rapidjson::Value namespaze::name::Serialize(rapidjson::Document::AllocatorType& allocator) { \
    rapidjson::Value jsonObject(rapidjson::kObjectType); \
    impl \
    return jsonObject; \
}

#define SERIALIZE_VALUE(name, jsonName) \
jsonObject.AddMember(#jsonName, name, allocator);

#define SERIALIZE_VALUE_OPTIONAL(name, jsonName) \
if(name) jsonObject.AddMember(#jsonName, name.value(), allocator);

#define SERIALIZE_CLASS(name, jsonName) \
jsonObject.AddMember(#jsonName, name.Serialize(allocator), allocator);

// assumes vector is of json serializables
#define SERIALIZE_VECTOR(name, jsonName) \
rapidjson::Value name##_jsonArray(rapidjson::kArrayType); \
for(auto jsonClass : name) { \
    name##_jsonArray.GetArray().PushBack(jsonClass.Serialize(allocator), allocator); \
} \
jsonObject.AddMember(#jsonName, name##_jsonArray, allocator);

#define SERIALIZE_VECTOR_BASIC(name, jsonName) \
rapidjson::Value name##_jsonArray(rapidjson::kArrayType); \
for(auto member : name) { \
    name##_jsonArray.GetArray().PushBack(rapidjson::Value(member, allocator).Move(), allocator); \
} \
jsonObject.AddMember(#jsonName, name##_jsonArray, allocator);