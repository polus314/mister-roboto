//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in GameMenu.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "GameMenu.h"

GameMenu::GameMenu(Panel^ _panel):
   panel(_panel)
{
   
}

GameMenu::GameMenu()
{
   regBrush = gcnew SolidBrush(Color::Black);
   selBrush = gcnew SolidBrush(Color::Red);
   backBrush = gcnew SolidBrush(Color::White);
   pen = gcnew Pen(Color::Black);
   headerFont = gcnew Font("Arial", 12, FontStyle::Bold);
   otherFont = gcnew Font("Arial", 12, FontStyle::Regular);
   child = NULL;
   selIndex = 0;
}
