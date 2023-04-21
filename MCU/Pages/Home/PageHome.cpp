#include "PageHome.h"
#include "Router.h"
#include "T5N8.h"
#include <IniResources.h>

void TPageHome::view() {
    TagList->view();
};

void TPageHome::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    TagList->Clear();
    isOpen = false;
}

bool TPageHome::ProcessMessage(TMessage* m) {
    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TVisualObject* TPageHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

/* TODO в таком виде хранится информация о наполнении страницы
1, 5N, PF1, U1/RAM/Iexc,
2, 5N, MA2, U1/RAM/Uexc,
3, 5N, NF0, U1/RAM/Ist,
4, 5N, PF1, U1/RAM/Q,
*/

void TPageHome::fillPageContainer(void) {
    TagList->Clear();
    TLabelInitStructure LabelInit;
    LabelInit.style = LabelsStyle::WIDTH_DINAMIC;
    LabelInit.Rect = { 10, 10, 10, 10 };
    LabelInit.focused = false;
    TagList->AddList({
        new T5N8("PF1", "U1/RAM/Uref/", LabelInit),
        new T5N8("MA2", "U1/RAM/Iref/", LabelInit),
        new T5N8("NF0", "U1/RAM/UoutAve/", LabelInit),
        new T5N8("PF2", "U1/RAM/IoutAve/", LabelInit),
    });
}

TPageHome::TPageHome(std::string Name)
    :TPage(Name) {
    TVerticalContainerProps props = { false };
    TagList = new TVerticalContainer(props, {});
    AddList({ TagList });
};

void TPageHome::SlotUpdate(TSlotHandlerArsg args) {
    for (auto& e : TagList->List) {
        T5N8* tag = (T5N8*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
}

TPageHome::~TPageHome() {
    TagList->Clear();
    delete TagList;
};
