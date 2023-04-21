#ifndef T5N8_H
#define T5N8_H

#include "common.h"
#include "Label.h"
#include "Events.hpp"
#include "parameters.h"

//строка текста
class T5N8 : public TVisualObject {
public:
    virtual bool ProcessMessage(TMessage* m);
    virtual const u16 getHeight(void);
    T5N8(std::string Format, std::string tag, TLabelInitStructure init);//конструктор
    ~T5N8();//деструктор
    void view(void);//вывести строку на экране
    TLabel* Value;
    const std::string Tag;
    const std::string ComponentName();
    std::string format;
private:
    
};

#endif