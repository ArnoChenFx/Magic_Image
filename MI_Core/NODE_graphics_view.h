#pragma once

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <NODE_item.h>
#include <QMouseEvent>
#include <NODE_graphics_scene.h>
#include <NODE_socket.h>
#include <NODE_line.h>
#include <NODE_cutline.h>
#include "mi_core_global.h"
#include <qlineedit.h>
#include <qmenu.h>

class MI_CORE_EXPORT NODE_graphics_view : public QGraphicsView
{
    Q_OBJECT

public:
    NODE_graphics_scene *NODE_scene;

    explicit NODE_graphics_view();

    QPointF mousePos = QPointF(0,0);
	NODE_item *viewportNode=nullptr;


    void onCopy();
    void onPase(bool move=false);
    void onCopyPase();
    void onCut();
    void onDeleteSelected();
    void onDisable();
    void onConnectToViewport();
    void onIndependent();
    void onFocus();

    void deleteNode(NODE_item *node);
	void deleteLine(NODE_line *line = nullptr);
    bool canUseKey = true;
	void createLine(NODE_graphics_view *nodeV, NODE_socket *startS, NODE_socket *endS, bool isCook=true);

	void showContextMenu();
	void createContextMenu();

	QLineEdit *searchLine;
	QMenu *contextMenu;
	QList<QMenu*> allMenus;
	QList<QAction*> allActions;
	int state = 0;//default state
	bool lineType = true;////false:linear;true:cubic

	QList<std::string> files;

protected:
    virtual void wheelEvent(QWheelEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event)override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event)override;
    virtual void keyPressEvent(QKeyEvent *event)override;

    void leftMousePressEvent(QMouseEvent *event);
    void leftMouseReleaseEvent(QMouseEvent *event);

    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;

private:
    //attribute
    const qreal zoomInFactor = 1.15;
    bool zoomClamp = false;
    qreal zoom = 10;
    qreal zoomStep = 1;
    qreal zoomRange_min = 0;
    qreal zoomRange_max = 10;
    QPoint initMousePos;
    QPointF prevPos;
    QPointF zoomInitialPos;
    qreal previousMouseOffset = 0;
    int zoomDirection = 0;
    qreal zoomIncr = 0;
    qreal width = 62000;
    qreal height = 62000;

    int MODE = 0;
    int MODE_NOOP = 0;
    int MODE_LINE_DRAG = 1;
    int MODE_LINE_CUT = 2;

    NODE_socket *startSocket;
    NODE_line *dragLine;
    NODE_cutline *cutline;

    void initFlags();
    bool dragEnd(NODE_socket *socket);

	QRectF _getSelectionBoundingbox();

    QList<NODE_item*> getSelectedNodes();
    QList<NODE_line*> getSelectedLines();

    bool canChangeDrag=false;
    QPointF prePos;

	void searchNode();
	void applySearch();
	void clearSearch();

	QList<QAction*> searchedActions;

	bool adsorb = false;
	NODE_socket *adsorbSocket=nullptr;

signals:
	void drop();
};