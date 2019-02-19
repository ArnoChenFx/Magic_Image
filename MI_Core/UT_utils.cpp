#include "UT_utils.h"
#include <QDebug>
#include <QString>
#include <fstream>
#include <iostream>
#include <string>
#include <json.hpp>
using json = nlohmann::json;
using namespace std;

json config = config_Load();
size_t global_id = 0;
json clipboard = json::array();
json history = json::array();
json Menus = json::array();

int history_index = 0;
int history_max_index = 10;

json config_Load(){

    std::fstream ifs("defalut_config.json");
    if (!ifs) {
        std::cout << "*ERROR** Could not read input file " << "defalut_config" << "\n"<<std::endl;;
      }
    qDebug()<<"config load.....";

    return json::parse(ifs);
}

QColor getColor(string name)
{
    auto a = config[name];
    return QColor(a[0],a[1],a[2]);
}

QString getRGB(string name)
{
    auto a = config[name];
    int r = a[0];
    int g = a[0];
    int b = a[0];
    return QString("rgb(%1,%2,%3)").arg(r).arg(g).arg(b);
}

QString getString(string name)
{
    string a = config[name];
    return QString::fromStdString(a);
}

string getFilename(string filePath)
{
    string name = filePath.substr(filePath.find_last_of("/") + 1);
    name = name.substr(0,name.find_last_of("."));
    return name;
}

string getFormat(string fileName)
{
    string format = fileName.substr(fileName.find_last_of(".") + 1);
    return format;
}



bool isUsefulFormat(string name, string format)
{
    auto formats = config[name];
    foreach(string fmt,formats){
        //std::cout <<fmt<<std::endl;
        if(format.compare(fmt)==0){
            return true;
        }
    }
    return false;
}

qreal Qdistance(QPointF a, QPointF b)
{
    return sqrt(pow(a.x()-b.x(),2)+pow(a.y()-b.y(),2));
}

void undo()
{

}

void redo()
{

}

//move_item
//create_node
//create_line
//delete_node
//delete_line

void saveHistory(string name,json info)
{
    json a = json::object();
    a["history_name"] = name;
    a[name] = info;

//    history.insert(history.begin(),a);
//    if(int(history.size()) > history_max_index) history.erase(history.end()-1);
//    cout<<history[0]<<endl;
//    history_index = 0;

    history.push_back(a);
    if(int(history.size()) > history_max_index) history.erase(0);
    cout<<history[history.size()-1]<<endl;
    history_index = int(history.size())-1;
    //history.push_back(a);
    //json::iterator it = history.end();
    //--it;
    //json::iterator it = history.begin();
}
