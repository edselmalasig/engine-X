// ==========================================================
// Alpha channel manipulation example
//
// Design and implementation by
// - Edsel Malasig
//
// This file is part of FreeImage 3
//
// COVERED CODE IS PROVIDED UNDER THIS LICENSE ON AN "AS IS" BASIS, WITHOUT WARRANTY
// OF ANY KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING, WITHOUT LIMITATION, WARRANTIES
// THAT THE COVERED CODE IS FREE OF DEFECTS, MERCHANTABLE, FIT FOR A PARTICULAR PURPOSE
// OR NON-INFRINGING. THE ENTIRE RISK AS TO THE QUALITY AND PERFORMANCE OF THE COVERED
// CODE IS WITH YOU. SHOULD ANY COVERED CODE PROVE DEFECTIVE IN ANY RESPECT, YOU (NOT
// THE INITIAL DEVELOPER OR ANY OTHER CONTRIBUTOR) ASSUME THE COST OF ANY NECESSARY
// SERVICING, REPAIR OR CORRECTION. THIS DISCLAIMER OF WARRANTY CONSTITUTES AN ESSENTIAL
// PART OF THIS LICENSE. NO USE OF ANY COVERED CODE IS AUTHORIZED HEREUNDER EXCEPT UNDER
// THIS DISCLAIMER.
//
// Use at own risk!
// ==========================================================

//   This example shows how to create a transparent image from any input image
//   using the greyscale version of the input image as the alpha channel mask.
//   The alpha channel is set using the FreeImage_SetChannel function.
//
//
// ==========================================================

#ifndef FIP_IMAGEOPERATIONS
#define FIP_IMAGEOPERATIONS

#include <stdio.h>
#include <string>
#include <iostream>
#define FREEIMAGE_LIB

#include "FreeImage.h"

#if defined (MACOS) || defined (LINUX)
#include "FreeImagePlus.h"
fipImage * invertPixelColors(fipImage * src);

fipImage * subtractPixelColors(fipImage * src, fipImage * input);

void printRGBValues(fipImage * src);
#endif

/**
 Creates a 32-bit transparent image using the black channel of the source image
 @param src Source image
 @return Returns a 32-bit transparent image
 */
FIBITMAP* CreateAlphaFromLightness(FIBITMAP *src);



void PrintRGBValues(FIBITMAP * src);

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message);

#endif
