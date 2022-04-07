#include "DisplayController.h"
#include "config.h"

DisplayController displayController = DisplayController();

DisplayController::DisplayController() : 
    DisplayObject(DISPLAY_CLK, DISPLAY_DATA) 
{
    segments_black[0] = 0x0;
    segments_black[1] = 0x0;
    segments_black[2] = 0x0;
    segments_black[3] = 0x0;
    //DisplayObject = TM1637Display();
};

void DisplayController::init(){
    pinMode (DISPLAY_CLK, OUTPUT);
    pinMode (DISPLAY_DATA, OUTPUT);
    DisplayObject.setBrightness(0x0f);
    DisplayObject.setSegments(segments_black);





}
void DisplayController::setNbDisplayed (int NbToDisplay){
    DisplayObject.showNumberDec(NbToDisplay);
};

int DisplayController::getNbDisplayed(){
    return NbDisplayed;
};

void DisplayController::setBlack(){
    DisplayObject.setSegments(segments_black);
};
