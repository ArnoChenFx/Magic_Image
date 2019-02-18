#pragma once
#include <QColor>
#include <string>
#include <QPointF>
#include <json.hpp>

#include "mi_core_global.h"
using json = nlohmann::json;
using namespace std;

json config_Load();

MI_CORE_EXPORT extern json config;
MI_CORE_EXPORT extern size_t global_id;
MI_CORE_EXPORT extern json clipboard;
MI_CORE_EXPORT extern json history;
MI_CORE_EXPORT extern int history_index;
MI_CORE_EXPORT extern int history_max_index;

MI_CORE_EXPORT QColor getColor(string name);

MI_CORE_EXPORT QString getRGB(string name);

MI_CORE_EXPORT QString getString(string name);

MI_CORE_EXPORT string getFilename(string filePath);

MI_CORE_EXPORT string getFormat(string fileName);

MI_CORE_EXPORT bool isUsefulFormat(string name,string format);

MI_CORE_EXPORT qreal Qdistance(QPointF a,QPointF b);

MI_CORE_EXPORT void saveHistory(string name,json info);

MI_CORE_EXPORT void undo();

MI_CORE_EXPORT void redo();
