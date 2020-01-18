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

#include <stdio.h>
#include <string>
#include <iostream>
#define FREEIMAGE_LIB
#include "FreeImage.h"
#include "fip_ImageOperations.h"

fipImage * convertToGreyScale(fipImage * src){

	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_Initialise();
#endif // FREEIMAGE_LIB

    fipImage *fip = src;
    if(src) {
		// Create a transparent image from the lightness image of src
		//FIBITMAP *dst = CreateAlphaFromLightness(src);

        int width = src->getWidth();
        int height = src->getHeight();

  		for (int i = 0; i < width; i++) {
  			for (int j = 0; j < height; j++) {
  				RGBQUAD getColor;
                  src->getPixelColor(i, j, &getColor);
  				//printf("red - %i : green - %i : blue - %i : alpha - %i \n", color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
  				RGBQUAD setColor;
  				setColor.rgbRed			= (getColor.rgbRed + getColor.rgbGreen + getColor.rgbBlue) / 3;
  				setColor.rgbBlue		= (getColor.rgbRed + getColor.rgbGreen + getColor.rgbBlue) / 3;
  				setColor.rgbGreen		= (getColor.rgbRed + getColor.rgbGreen + getColor.rgbBlue) / 3;
  				setColor.rgbReserved	= 0x00;
  				src->setPixelColor(i, j, &setColor);

  			}
  		}
    }

	// call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
	FreeImage_DeInitialise();
#endif // FREEIMAGE_LIB

	return src;
}

fipImage * invertPixelColors(fipImage * src){
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif // FREEIMAGE_LIB

    if(src) {

        int width = src->getWidth();
        int height = src->getHeight();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                RGBQUAD getColor;
                src->getPixelColor(i, j, &getColor);
                printf("red - %i : green - %i : blue - %i : alpha - %i \n", getColor.rgbRed, getColor.rgbGreen, getColor.rgbBlue, getColor.rgbReserved);
                RGBQUAD setColor;
                setColor.rgbRed            = -getColor.rgbRed;
                setColor.rgbBlue        = -getColor.rgbBlue;
                setColor.rgbGreen        = -getColor.rgbGreen;
                setColor.rgbReserved    = 0xff;
                src->setPixelColor(i, j, &setColor);

            }

        }

    }

    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif // FREEIMAGE_LIB

    return src;
}

fipImage * subtractPixelColors(fipImage * src, fipImage * input){
    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_Initialise();
#endif // FREEIMAGE_LIB

    if(src && input) {

        int width = src->getWidth();
        int height = src->getHeight();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                RGBQUAD srcgetColor, inputgetColor;
                src->getPixelColor(i, j, &srcgetColor);
                input->getPixelColor(i, j, &inputgetColor);
                //printf("red - %i : green - %i : blue - %i : alpha - %i \n", color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
                RGBQUAD setColor;
                setColor.rgbRed            = srcgetColor.rgbRed-inputgetColor.rgbRed;
                setColor.rgbBlue        = srcgetColor.rgbBlue-inputgetColor.rgbBlue;
                setColor.rgbGreen        = srcgetColor.rgbGreen-inputgetColor.rgbGreen;
                setColor.rgbReserved    = srcgetColor.rgbReserved-inputgetColor.rgbReserved;
                input->setPixelColor(i, j, &setColor);

            }

        }

    }

    // call this ONLY when linking with FreeImage as a static library
#ifdef FREEIMAGE_LIB
    FreeImage_DeInitialise();
#endif // FREEIMAGE_LIB

    return input;
}

/**
 Creates a 32-bit transparent image using the black channel of the source image
 @param src Source image
 @return Returns a 32-bit transparent image
 */
FIBITMAP* CreateAlphaFromLightness(FIBITMAP *src) {
    // create a 32-bit image from the source
    FIBITMAP *dst = FreeImage_ConvertTo32Bits(src);

    // create a 8-bit mask
    FreeImage_Invert(src);
    FIBITMAP *mask = FreeImage_ConvertTo8Bits(src);
    FreeImage_Invert(src);

    // insert the mask as an alpha channel
    FreeImage_SetChannel(dst, mask, FICC_ALPHA);

    // free the mask and return
    FreeImage_Unload(mask);

    return dst;
}


void printRGBValues(fipImage * src)
{
    if(src) {

        int width = src->getWidth();
        int height = src->getHeight();

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                RGBQUAD getColor;
                src->getPixelColor(i, j, &getColor);
                //printf("red - %i : green - %i : blue - %i : alpha - %i \n", color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
                std::cout <<"RGB values at "
                    << i << " " << j << " "
                    << int(getColor.rgbRed) << " "
                    << int(getColor.rgbGreen) << " "
                    << int(getColor.rgbBlue) << " "
                    << int(getColor.rgbReserved) << " "
                    << std::endl;
            }
        }
    }
}

void PrintRGBValues(FIBITMAP * src)
{
    if(src) {

        int width = FreeImage_GetWidth(src);;
        int height = FreeImage_GetHeight(src);

        for (int i = 0; i < width; i++) {
            for (int j = 0; j < height; j++) {
                RGBQUAD getColor;
                FreeImage_GetPixelColor(src, i, j, &getColor);
                //printf("red - %i : green - %i : blue - %i : alpha - %i \n", color.rgbRed, color.rgbGreen, color.rgbBlue, color.rgbReserved);
                std::cout <<"RGB values at "
                    << i << " " << j << " "
                    << int(getColor.rgbRed) << " "
                    << int(getColor.rgbGreen) << " "
                    << int(getColor.rgbBlue) << " "
                    << int(getColor.rgbReserved) << " "
                    << std::endl;
            }

        }

    }
}

void FreeImageErrorHandler(FREE_IMAGE_FORMAT fif, const char *message) {
  	printf("\n*** ");
  	if(fif != FIF_UNKNOWN) {
  		printf("%s Format\n", FreeImage_GetFormatFromFIF(fif));
  	}
  	printf(message);
  	printf(" ***\n");
}
