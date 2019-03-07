#include "node_Curve.h"
#include <qdebug.h>
#include <NODE_ui_items.h>
#include <QtCharts/QChartView>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QAbstractAxis>

QT_CHARTS_USE_NAMESPACE

node_Curve::node_Curve(NODE_graphics_view* NODE_v) :
	NODE_item(NODE_v, "Curve")
{
	initSocket();
	color_title_bar = getColor("Color");
	updateParamUI();
}

void node_Curve::updateParamUI()
{
	QHBoxLayout *hbox = new QHBoxLayout();

	
	QSplineSeries *serial = new QSplineSeries();
	QList<QPointF>list;
	list << QPointF(0, 0) << QPointF(0.7, 0.5) << QPointF(1, 1);
	serial->append(list);

	//��ʼ������
	QtCharts::QChart *chart = new QtCharts::QChart;
	chart->addSeries(serial);
	//����Ĭ������,
	chart->createDefaultAxes();
	chart->axisY()->setLabelsVisible(false);
	chart->axisX()->setLabelsVisible(false);
	chart->axisY()->setRange(0, 1);
	chart->axisX()->setRange(0, 1);

	chart->setPlotAreaBackgroundBrush(QBrush(Qt::black));
	chart->setPlotAreaBackgroundVisible(true);
	chart->setBackgroundRoundness(0);
	chart->setMargins(QMargins(0, 0, 0, 0));
	//chart->layout()->setMargins(QMargins(0, 0, 0, 0));
	//��������ȥ����һ��,�������ɻ����һ��С����.
	chart->legend()->hide();// clear up bar
   //�Զ����ķ�ʽ��ʾ,��ʾ��һ˲���Ƕ�̬��
	//chart->setAnimationOptions(QChart::SeriesAnimations);
	QChartView *vieww = new QChartView(chart);
	//���Ӧ�ò���˵��,�������
	vieww->setRenderHint(QPainter::Antialiasing);
	vieww->setBackgroundBrush(QBrush(Qt::black));
	vieww->setContentsMargins(QMargins(0, 0, 0, 0));
	//vieww.setba


	hbox->addWidget(vieww);
	addHboxs(mainLayout, { hbox });
}


void node_Curve::cook()
{
	if (!checkActive()) return;

	getPreImage();
	updateImage();
	cookNext();
}



REGISTER_NODE(node_Curve, "Curve", "Color", "");
