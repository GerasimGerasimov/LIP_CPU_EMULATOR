#ifndef T_PAGE_BRAND_NEW_HOME_H
#define T_PAGE_BRAND_NEW_HOME_H

#include "Pages.h"
#include "HandleSubscribers.h"

class TPageBrandNewHome : public TPage
{
public:
    virtual void view();
    virtual const u16 getHeight(void) { return 0; };
    void onOpen();
    void startToClose();
    bool ProcessMessage(TMessage* m);
    TPageBrandNewHome(std::string Name);
    ~TPageBrandNewHome();
private:
    void fillPageContainer(void);
    void SlotUpdate(TSlotHandlerArsg args);
    TVisualObject* getSignalOfFocusedChild();
    int SubscriberID = 0;
};

#endif