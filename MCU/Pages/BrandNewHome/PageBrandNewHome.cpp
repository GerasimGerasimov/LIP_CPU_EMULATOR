#include "PageBrandNewHome.h"
#include "Router.h"
#include "ValueVerticalDiagram.h"
#include <IniResources.h>

void TPageBrandNewHome::view() {
    for (auto& e : List) {
        e->view();
    }
};

void TPageBrandNewHome::onOpen() {
    fillPageContainer();
    SubscriberID = HandlerSubscribers::set("U1/RAM/", [this](TSlotHandlerArsg args) { SlotUpdate(args); });
}

void TPageBrandNewHome::startToClose() {
    HandlerSubscribers::remove("U1/RAM/", SubscriberID);
    Clear();
    isOpen = false;
}

bool TPageBrandNewHome::ProcessMessage(TMessage* m) {
    TVisualObject* e = { nullptr };
    switch (m->Event) {
        case (u32)EventSrc::KEYBOARD: {
            switch (m->p1) {
                case (u32)KeyCodes::ESC:
                    TRouter::setTask({ false, "MainMenu", nullptr });
                    break;
                case (u32)KeyCodes::F1:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        ISignal* p = IniResources::getSignalByTag(((TValueRefVerticalDiagram*)(e))->Tag);
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "Help", p });
                    }
                    break;
                case (u32)KeyCodes::ENT:
                    e = getSignalOfFocusedChild();
                    if (e) {
                        TRouter::PageValueEditEntryData.tag = ((TValueRefVerticalDiagram*)(e))->Tag;
                        TRouter::PageValueEditEntryData.value = ((TValueRefVerticalDiagram*)(e))->Value->getCaption();
                        TRouter::PageValueEditEntryData.backPage = Name;
                        TRouter::setTask({ false, "EditValue", nullptr });
                    }
                    break;
            }
        }
    }

    for (auto& element : List) {
        element->ProcessMessage(m);
    }
    return false;
};

TVisualObject* TPageBrandNewHome::getSignalOfFocusedChild() {
    for (auto& element : List) {
        TVisualObject* e = element->getFocusedElement();
        TParameter* p = (e) ? (TParameter*) e->getDataSrc() : nullptr;
        if (p) return e;
    }
    return nullptr;
}

void TPageBrandNewHome::fillPageContainer(void) {
    Clear();
    AddList({
        new TValueRefVerticalDiagram("I, mA", "U1/RAM/Iref/"),
    });
}

TPageBrandNewHome::TPageBrandNewHome(std::string Name)
    :TPage(Name) {
};

void TPageBrandNewHome::SlotUpdate(TSlotHandlerArsg args) {
    /*
    for (auto& e : List) {
        TValueVerticalDiagram* tag = (TValueVerticalDiagram*)e;
        TParameter* p = (TParameter*)tag->getDataSrc();
        tag->Value->setCaption(p->getValue(args, ""));
    }
    Msg::send_message((u32)EventSrc::REPAINT, 0, 0);
    */
}

TPageBrandNewHome::~TPageBrandNewHome() {
    Clear();
};
