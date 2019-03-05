#pragma once

#include <QDebug>
#include <QAction>
#include <QMenuBar>



QAction *createAct(QMenu *menu,QString name,QString tooltip,QString shortcut=""){
    QAction *act = new QAction;
    if(shortcut != "") act->setShortcut(QKeySequence(shortcut));
    act->setText(name);
    act->setToolTip(tooltip);
    menu->addAction(act);
    return act;
}
