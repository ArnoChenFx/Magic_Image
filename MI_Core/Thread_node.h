#pragma once
#include <qthread.h>
#include <qmutex.h>

class NODE_item;
class Thread_node: public QObject
{
	Q_OBJECT

public:
	Thread_node(NODE_item *nd);
	~Thread_node();
	NODE_item *node;

	void updateImage();
	void stopImmediately();

	void run();

	void setStop(bool flag = true);
protected:
	QMutex m_lock;
	bool m_isCanRun;

private:
	bool stop;

signals:
	void done();
};

