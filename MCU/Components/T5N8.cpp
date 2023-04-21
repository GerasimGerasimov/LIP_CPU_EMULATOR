#include "T5N8.h"
#include "IniResources.h"

bool T5N8::ProcessMessage(TMessage* m) {
    return false;
}

const std::string T5N8::ComponentName() {
    return "TTagLine";
}

T5N8::T5N8(std::string caption, std::string tag, TLabelInitStructure init)
    : Caption(new TLabel(init))
    , Value(new TLabel(init))
    , msu(new TLabel(init))
    , Tag(tag) {
    Caption->setCaption(caption);
    DataSrc = (TParameter*)IniResources::getSignalByTag(tag);
    Value->setCaption(((TParameter*)DataSrc)->getDefaultValue());
}

T5N8::~T5N8() {
    delete Caption;
    delete Value;
    delete msu;
}

const u16 T5N8::getHeight(void) {
    TTextSizes tsizes = Caption->getSize();
    return tsizes.height;
}

void T5N8::view(void) {
    Caption->inFocus = inFocus;
    Caption->ElementRect.Top = ElementRect.Top;
    Caption->ElementRect.Left = ElementRect.Left;
    Caption->view();//выводит Coption

    if (DataSrc) {/*TODO 2-й раз пишу нужен пустой объект для отлавливания несуществующих тегов*/
        Value->inFocus = inFocus;
        Value->ElementRect.Top = ElementRect.Top;
        Value->ElementRect.Left = 55;//ElementRect.Left;
        Value->view();
    }

    if (DataSrc) {/*TODO 2-й раз пишу нужен пустой объект для отлавливания несуществующих тегов*/
        msu->setCaption(((TParameter*) DataSrc)->getMSU());
        msu->inFocus = inFocus;
        msu->ElementRect.Top = ElementRect.Top;
        msu->ElementRect.Left = 105;//ElementRect.Left;
        msu->view();
    }
}
