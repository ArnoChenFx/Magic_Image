#include "NODE_graphics_scene.h"
#include <QPainter>
#include <QtDebug>
#include <QStyle>
#include <string>


NODE_graphics_scene::NODE_graphics_scene(NODE_graphics_view *nodeV):QGraphicsScene ()
{
    nodeView = nodeV;
    pen_light.setColor(color_light);
    pen_light.setWidth(1);
    pen_dark.setColor(color_dark);
    pen_dark.setWidth(2);
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

