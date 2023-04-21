#ifndef RAMDATA_H
#define RAMDATA_H

#include "Intmash_bastypes.h"//содержит описания базовых типов
///////////////////////////////////////////////////////////////////////////////
//параметры расположеные в RAM
typedef  struct {
    tU16Union FLAGS;    //00
    tU16 Last_lnk_error;//01
    
    tU16 var1; //02
    tU16 var2; //03
    tU16 var3; //04
    tU16 var4; //05
    tU16 KeyCode;
    tU16 DIO;
        
} TRAM_DATA;

#ifdef __cplusplus
    extern "C" TRAM_DATA RAM_DATA;
#else
    extern TRAM_DATA RAM_DATA;
#endif

#endif