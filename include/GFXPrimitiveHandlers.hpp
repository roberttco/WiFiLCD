#ifndef __GFX_HANDLER_H_
#define __GFX_HANDLER_H_

#include <CmdCallback.hpp>
#include <CmdParser.hpp>

// primitive functions
#ifdef DEBUG
void dumpParams(CmdParser *myParser);
#endif

void functFill(CmdParser *myParser);
void functString(CmdParser *myParser); 
void functStringExtended(CmdParser *myParser);
void functRectangle(CmdParser *myParser);
void functCircle(CmdParser *myParser);
void functTriangle(CmdParser *myParser);
void functPixel(CmdParser *myParser);
void functLine(CmdParser *myParser);

#endif