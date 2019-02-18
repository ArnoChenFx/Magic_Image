#include "NODE_graphics_scene.h"
#include <QPainter>
#include <QtDebug>
#include <QStyle>
#include <NODE_item.h>
#include <NODE_line.h>
#include <string>
#include <json.hpp>
using json = nlohmann::json;

NODE_graphics_scene::NODE_graphics_scene(NODE_graphics_view *nodeV):QGraphicsScene ()
{
    nodeView = nodeV;
    pen_light.setColor(color_light);
    pen_light.setWidth(1);
    pen_dark.setColor(color_dark);
    pen_dark.setWidth(2);
}

json NODE_graphics_scene::save()
{
    qDebug()<<"start save";
    json sceneInfo = json::object();
    json nodeInfo = json::array();
    json lineInfo = json::array();
    foreach(NODE_item* node,sceneNodes){
        json nodeJson = node->save();
        nodeInfo.push_back(nodeJson);
    }
    qDebug()<<"nodes saved";
    foreach(NODE_line* line,sceneLines){
        json lineJson = line->save();
        lineInfo.push_back(lineJson);
    }
    qDebug()<<"lines saved";
    sceneInfo["Nodes"] = nodeInfo;
    sceneInfo["Lines"] = lineInfo;
    return sceneInfo;
}

void NODE_graphics_scene::load(json sceneInfo)
{
    json nodeInfo = sceneInfo["Nodes"];
    json lineInfo = sceneInfo["Lines"];

    for (auto& info : nodeInfo.items())
    {
        auto ndInfo = info.value();
        loadNode(ndInfo);
    }

    for (auto& info : lineInfo.items())
    {
        auto liInfo = info.value();
        loadLine(liInfo);
    }
}

void NODE_graphics_scene::loadLine(json liInfo)
{
    size_t inNode = liInfo["inputNode"];
    size_t outNode = liInfo["outputNode"];
    QString inSocketName = QString::fromStdString(liInfo["inputSocket"]);
    QString outSocketName = QString::fromStdString(liInfo["outputSocket"]);
    NODE_socket *inSocket = nullptr;
    NODE_socket *outSocket = nullptr;
    int count=0;

    foreach(NODE_item* node,sceneNodes){
        if(count==2) break;
        else if(node->id==inNode){
            foreach(NODE_socket *socket,node->output_sockets){
                if(socket->name==inSocketName) inSocket = socket;
                count ++;
                //break;
            }
        }
        else if(node->id==outNode){
            foreach(NODE_socket *socket,node->input_sockets){
                if(socket->name==outSocketName) outSocket = socket;
                count ++;
                //break;
            }
        }

    }
    if(count==2) new NODE_line(nodeView,inSocket,outSocket);
    else qDebug()<<"create Line error!!";
}

void NODE_graphics_scene::loadNode(json ndInfo)
{
    auto node = new NODE_item(nodeView);
    node->load(ndInfo);
}

void NODE_graphics_scene::drawBackground(QPainter *painter, const QRectF &rect)
{
    if(drawGrid){
        painter->setPen(pen_light);

        //here we create our grid
        int left = int(floor(rect.left()));
        int right = int(ceil(rect.right()));
        int top = int(floor(rect.top()));
        int bottom = int(ceil(rect.bottom()));

        int first_left = left - (left % gridSize);
        int first_top = top - (top % gridSize);

        for(int x= first_left;x<right;x+=gridSize)
        {
            QLine ss(x, top, x, bottom);
            painter->drawLine(ss);
        }

        for(int y=first_top;y<bottom;y+=gridSize){
            QLine kk(left, y, right, y);
            painter->drawLine(kk);
        }
    }

}

