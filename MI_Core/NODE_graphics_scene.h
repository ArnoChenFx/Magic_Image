#pragma once
#include <QGraphicsScene>
#include <NODE_line.h>
#include <NODE_item.h>
#include <json.hpp>
#include "mi_core_global.h"

using json = nlohmann::json;

class NODE_graphics_view;

class MI_CORE_EXPORT NODE_graphics_scene:public QGraphicsScene
{
    Q_OBJECT
public:
    NODE_graphics_view *nodeView;
    NODE_graphics_scene(NODE_graphics_view *nodeV=nullptr);
	~NODE_graphics_scene();
    bool drawGrid = false;

    QList<NODE_line*> sceneLines;
    QList<NODE_item*> sceneNodes;

protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

private:
    //settings
    int gridSize = 20;
    QColor color_light = QColor("#2f2f2f");
    QColor color_dark = QColor("#292929");

    QPen pen_light;
    QPen pen_dark;

};
