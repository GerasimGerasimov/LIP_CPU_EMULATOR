#ifndef VALUE_REF_VERTICAL_DIAGRAM_H
#define VALUE_REF_VERTICAL_DIAGRAM_H

#include "common.h"
#include "Label.h"
#include "Events.hpp"
#include "parameters.h"

//строка текста
class TValueRefVerticalDiagram : public TVisualObject {
public:
    virtual bool ProcessMessage(TMessage* m);
    virtual const u16 getHeight(void);
    TValueRefVerticalDiagram(std::string name, std::string tag);//конструктор
    ~TValueRefVerticalDiagram();//деструктор
    void view(void);//вывести строку на экране
    TLabel* Name;
    TLabel* Value;
    TLabel* Ref;
    const std::string Tag;
    const std::string ComponentName();
private:
    u16 uValue;
    u16 uRef;
    u16 uMaxValue;
    u16 BarMaxHeight;
    u16 BarBearHeight;
    u16 BarNormalHeight;
    u16 RefPosition;

};

#endif