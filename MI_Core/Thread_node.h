#pragma once
#include <qthread.h>
#include <qmutex.h>

class NODE_item;
class Thread_node: public QThread
{
	Q_OBJECT

public:
	Thread_node(NODE_item *nd);
	~Thread_node();
	NODE_item *node;

	void updateImage();
	void stopImmediately();

protected:
	void run();

	QMutex m_lock;
	bool m_isCanRun;

signals:
	void done();
};

