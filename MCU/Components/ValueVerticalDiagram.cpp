#include "ValueVerticalDiagram.h"
#include "IniResources.h"

bool TValueRefVerticalDiagram::ProcessMessage(TMessage* m) {
    return false;
}

const std::string TValueRefVerticalDiagram::ComponentName() {
    return "TValueVerticalDiagram";
}

TValueRefVerticalDiagram::TValueRefVerticalDiagram(std::string caption, std::string tag)
    : Tag(tag) 
    , BarMaxHeight(0)
    , BarBearHeight(0)
    , BarNormalHeight(0)
    , RefPosition(30)
    , uValue(0)
    , uRef(50)
    , uMaxValue(100) {
    ElementRect = { 0, 0, 63, 54 };
    TLabelInitStructure init;
    init.style = LabelsStyle::WIDTH_DINAMIC;
    init.Rect = { 10, 10, 10, 10 };
    init.focused = false;

    init.font = "Verdana12";
    Name = new TLabel(init);

    init.font = "MSSansSerifBold14";
    Value = new TLabel(init);

    init.font = "Verdana12";
    Ref = new TLabel(init);

    Name->setCaption(caption);
    Value->setCaption("XXX.X");
    Ref->setCaption("XXX.X");
}

TValueRefVerticalDiagram::~TValueRefVerticalDiagram() {
    delete Name;
    delete Value;
    delete Ref;
}

const u16 TValueRefVerticalDiagram::getHeight(void) {
    TTextSizes tsizes = Name->getSize();
    return tsizes.height;
}

void TValueRefVerticalDiagram::view(void) {
    Name->inFocus = inFocus;
    Name->ElementRect.Top = ElementRect.Top;
    Name->ElementRect.Left = ElementRect.Left;
    Name->view();

    Value->inFocus = inFocus;
    Value->ElementRect.Top = ElementRect.Top + 50;
    Value->ElementRect.Left = ElementRect.Left;
    Value->view();

    Ref->inFocus = inFocus;
    Ref->ElementRect.Top = ElementRect.Top + 20;
    Ref->ElementRect.Left = ElementRect.Left;
    Ref->view();


    TFillRect rect;
    //покажу рамку
    rect = { (s16)(ElementRect.Left), (s16)(ElementRect.Top) , (u16)(ElementRect.Width), (u16)(ElementRect.Height), 1 };
    TGraphics::Rect(rect);
    
    rect = { (s16)(ElementRect.Left + 40), (s16)(ElementRect.Top + 10) , 1, 42, 1 };
    TGraphics::fillRect(rect);
    rect = { (s16)(ElementRect.Left + 40 + 11), (s16)(ElementRect.Top + 10) , 1, 42, 1 };
    TGraphics::fillRect(rect);
    rect = { (s16)(ElementRect.Left + 40), (s16)(ElementRect.Top + 10) , 12, 1, 1 };
    TGraphics::fillRect(rect);

    /*TODO
    * Ќормализаци€: uValue и uRef не должно превышать uMaxValue
    *   если uValue превышет или равен uMaxValue то 
    *   надо весь индикатор закрасить сплошным цветом (Filled-пр€моугольником)
    * ≈сли же uValue меньше uMaxValue то индикатор может разбиватьс€ на два участка
    * 1) uValue меньше или равно uRef, тогда:
    *   вычисл€етс€ высота Dashed-пр€моугольника как соотношение uValue к uMaxValue,
        а высота Filled-пр€моугольника = 0 (что есть призак его не рисовать)
    * 2) uValue больше uRef, тогда:
    *   высота Dashed-пр€моугольника равна отношению uRef к uMaxValue, 
    *   а высота Filled-пр€моугольника равна отношению разности (uValue - uRef) к uMaxValue.
    * Ќапрашивает функци€, котора€ обработав uValue, uRef, uMaxValue на выходе
    * выдаЄт высоты Filled и Dashed-индикаторов. 
    */
    /*TODO терерь, когда известны 
    */
    //FillRect показывает положение Value над Ref
    /*TODO если Value не превышает Ref то данный элемент не отображаетс€*/
    rect = { (s16)(ElementRect.Left + 40 + 2), (s16)(ElementRect.Top + 24) , 8, 6, 1 };
    TGraphics::fillRect(rect);

    //DashedFillRect показывает положение Value под Ref
    rect = { (s16)(ElementRect.Left + 40 + 2), (s16)(ElementRect.Top + 30) , 8, 22, 1 };
    TGraphics::DashedfillRect(rect);

    //Dashed line показывает положение Ref
    TGraphics::DashedLine((u8)(ElementRect.Left + 40 - 2), (s16)(ElementRect.Top + RefPosition),
        (u8)(ElementRect.Left + 40 + 14), (s16)(ElementRect.Top + RefPosition), 1);

}
