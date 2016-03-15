//-----------------------------------------------------------------------------
// Project: Mister Roboto
// 
// Purpose: This file implements the methods declared in Sprite.h
//
// Created: 2/6/2016
//
// Changed: 2/6/2016 
//-----------------------------------------------------------------------------

#include "stdafx.h"
#include "Sprite.h"

void Sprite::createSprites()
{
   int width = sheet->Width / 3;
   int height = sheet->Height / 4;
   allocateBitmaps(width, height);
   copyBitmaps(width, height);
   makeTransparent();
   resizeBitmaps(50, 50);
}

void Sprite::allocateBitmaps(int width, int height)
{
   walkDL = gcnew Bitmap(width, height);
   walkDR = gcnew Bitmap(width, height);
   standD = gcnew Bitmap(width, height);
   walkLL = gcnew Bitmap(width, height);
   walkLR = gcnew Bitmap(width, height);
   standL = gcnew Bitmap(width, height);
   walkRL = gcnew Bitmap(width, height);
   walkRR = gcnew Bitmap(width, height);
   standR = gcnew Bitmap(width, height);
   walkUL = gcnew Bitmap(width, height);
   walkUR = gcnew Bitmap(width, height);
   standU = gcnew Bitmap(width, height);
}

void Sprite::copyBitmaps(int width, int height)
{
   for(int i = 0; i < width; i++)
      for(int j = 0; j < height; j++)
      {
         walkDL->SetPixel(i,j, sheet->GetPixel(i,j));
         standD->SetPixel(i,j, sheet->GetPixel(i + width,j));
         walkDR->SetPixel(i,j, sheet->GetPixel(i + 2 * width,j));
         walkLL->SetPixel(i,j, sheet->GetPixel(i,j + height));
         standL->SetPixel(i,j, sheet->GetPixel(i + width,j + height));
         walkLR->SetPixel(i,j, sheet->GetPixel(i + 2 * width,j + height));
         walkRL->SetPixel(i,j, sheet->GetPixel(i,j + 2 * height));
         standR->SetPixel(i,j, sheet->GetPixel(i + width,j + 2 * height));
         walkRR->SetPixel(i,j, sheet->GetPixel(i + 2 * width,j + 2 * height));
         walkUL->SetPixel(i,j, sheet->GetPixel(i,j + 3 * height));
         standU->SetPixel(i,j, sheet->GetPixel(i + width,j + 3 * height));
         walkUR->SetPixel(i,j, sheet->GetPixel(i + 2 * width,j + 3 * height));
      }
}

void Sprite::resizeBitmaps(int width, int height)
{
   walkDL = gcnew Bitmap(walkDL, width, height);
   walkDR = gcnew Bitmap(walkDR, width, height);
   standD = gcnew Bitmap(standD, width, height);
   walkLL = gcnew Bitmap(walkLL, width, height);
   walkLR = gcnew Bitmap(walkLR, width, height);
   standL = gcnew Bitmap(standL, width, height);
   walkRL = gcnew Bitmap(walkRL, width, height);
   walkRR = gcnew Bitmap(walkRR, width, height);
   standR = gcnew Bitmap(standR, width, height);
   walkUL = gcnew Bitmap(walkUL, width, height);
   walkUR = gcnew Bitmap(walkUR, width, height);
   standU = gcnew Bitmap(standU, width, height);
}

void Sprite::makeTransparent()
{
   walkDL->MakeTransparent();
   walkDR->MakeTransparent();
   standD->MakeTransparent();
   walkLL->MakeTransparent();
   walkLR->MakeTransparent();
   standL->MakeTransparent();
   walkRL->MakeTransparent();
   walkRR->MakeTransparent();
   standR->MakeTransparent();
   walkUL->MakeTransparent();
   walkUR->MakeTransparent();
   standU->MakeTransparent();
}


