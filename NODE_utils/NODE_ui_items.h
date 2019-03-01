#pragma once

#include "node_utils_global.h"
#include <qlayout.h>
#include <qlineedit.h>
#include <qpushbutton.h>

NODE_UTILS_EXPORT void addFileUI(QHBoxLayout *hbox, QLineEdit *pathLine, QPushButton *button,QString name);

NODE_UTILS_EXPORT void addHline(QVBoxLayout *mainLayout);

NODE_UTILS_EXPORT void addSpacer(QVBoxLayout *mainLayout);

NODE_UTILS_EXPORT void addHboxs(QVBoxLayout *mainLayout,QList<QHBoxLayout*> hboxs);