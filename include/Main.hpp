#pragma once

#define USE_CODEGEN_FIELDS

//#define LOG_INFO(value...)
#define LOG_INFO(value...) getLogger().info(value) 
#define LOG_DEBUG(value...)
//#define LOG_DEBUG(value...) getLogger().debug(value) 
//#define LOG_ERROR(value...)
#define LOG_ERROR(value...) getLogger().error(value)

#define STR(il2cpp_str) to_utf8(csstrtostr(il2cpp_str))
#define CSTR(string) il2cpp_utils::newcsstr(string)
#define STATIC_CSTR(name, string) static auto name = il2cpp_utils::newcsstr<il2cpp_utils::CreationType::Manual>(string)

#include "beatsaber-hook/shared/utils/utils.h"
Logger& getLogger();

std::string GetPlaylistsPath();
std::string GetConfigPath();
std::string GetCoversPath();