#include "T5N8.h"
#include "IniResources.h"

bool T5N8::ProcessMessage(TMessage* m) {
    return false;
}

const std::string T5N8::ComponentName() {
    return "T5N8";
}

T5N8::T5N8(std::string Format, std::string tag, TLabelInitStructure init)
    : format(Format)
    , Value(new TLabel(init))
    , Tag(tag) {
    DataSrc = (TParameter*)IniResources::getSignalByTag(tag);
    Value->setCaption("--.--");
}

T5N8::~T5N8() {
    delete Value;
}

const u16 T5N8::getHeight(void) {
    TTextSizes tsizes = Value->getSize();
    return tsizes.height;
}

void T5N8::view(void) {
    if (DataSrc) {/*TODO 2-й раз пишу нужен пустой объект для отлавливания несуществующих тегов*/
        Value->inFocus = inFocus;
        Value->ElementRect.Top = ElementRect.Top;
        Value->ElementRect.Left = 55;//ElementRect.Left;
        Value->view();
    }
}
