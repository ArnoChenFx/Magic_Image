#pragma once
#include <QColor>
#include <QPointF>
#include <json.hpp>
#include <string>
#include "mi_core_global.h"
using json = nlohmann::json;

json config_Load();

MI_CORE_EXPORT extern json config;
MI_CORE_EXPORT extern size_t global_id;
MI_CORE_EXPORT extern json clipboard;
MI_CORE_EXPORT extern json history;
MI_CORE_EXPORT extern int history_index;
MI_CORE_EXPORT extern int history_max_index;
MI_CORE_EXPORT extern json Menus;
MI_CORE_EXPORT extern bool isModified;

MI_CORE_EXPORT QColor getColor(std::string name);

MI_CORE_EXPORT QString getRGB(std::string name);

MI_CORE_EXPORT QString getString(std::string name);

MI_CORE_EXPORT std::string getFilename(std::string filePath);

MI_CORE_EXPORT std::string getFormat(std::string fileName);

MI_CORE_EXPORT bool isUsefulFormat(std::string name,std::string format);

MI_CORE_EXPORT qreal Qdistance(QPointF a,QPointF b);

MI_CORE_EXPORT void saveHistory(std::string name,json info);

MI_CORE_EXPORT void undo();

MI_CORE_EXPORT void redo();
