#include <iostream>
#include "ImageBase.h"
#include <stdio.h>
#include <cmath>

using namespace std;


int * getLuminance(ImageBase img);
ImageBase getPersonalizedImage(int * Cy, ImageBase img);

int main(int argc, char **argv)
{
	char logo[250], qrcode[250];
	
	if (argc != 3) 
	{
		printf("Usage: logo.ppm QrCode.pgm \n"); 
		return 1;
	}
	sscanf (argv[1],"%s",logo) ;
	sscanf (argv[2],"%s",qrcode);
	
	//ImageBase imIn, imOut;
	ImageBase imIn;
	imIn.load(logo);

	ImageBase imOut(imIn.getWidth(), imIn.getHeight(), true);
	
	int h = imIn.getHeight();
	int w = imIn.getWidth();
	int * y;
	y = (int*) malloc(sizeof(int) * h * w * 3);
	
	y = getLuminance(imIn);
	int k = 0;
	
	// 2 création des images en luminance y
	cout << " h = " << h << ", w = " << w << endl;
	for (int j = 0; j < h; j++) {
		for (int i = 0; i < w; i++) {
			imOut[j*3][i*3+0] = y[k];
			imOut[j*3][i*3+1] = y[k];
			imOut[j*3][i*3+2] = y[k];
			k+=1;
			
		}
	}
	
	ImageBase * R = imOut.getPlan(imOut.PLAN_R);
	R->save("imgResult.pgm");
	delete R;
	
	ImageBase imIn2;
	imIn2.load(qrcode);
	ImageBase img2 = getPersonalizedImage(y, imIn2);
	
	return 0;
}

int * getLuminance(ImageBase img) {
	int height = img.getHeight();
	int width = img.getWidth();
	
	int * luminance;
	luminance = (int*) malloc(sizeof(int)*height*width);
	
	int counter = 0;
	for (int j = 0; j < height; j++){
		for (int i = 0; i < width; i++) {
			int y = 0.29 * img[j*3][i*3+0] + 0.59 * img[j*3][i*3+1] + 0.12 * img[j*3][i*3+2];
			luminance[counter] = y;
			counter++;
		}
	}
	cout << " taille " << counter << endl;
	return luminance;
}


ImageBase getPersonalizedImage(int * Cy, ImageBase img) {
	int height = img.getHeight();
	int width = img.getWidth();
	int tau_u = 70;
	int tau_l = 100;
	int counter = 0;
	
	ImageBase imOut(width, height, false);
	
	for (int j = 0; j < height; j++) {
		for (int i = 0; i < width; i++) {
			if (img[j][i] == 0) {
				imOut[j][i] = Cy[counter] < tau_l ? Cy[counter] : tau_l;
			} else {
				imOut[j][i] = Cy[counter] > tau_u ? Cy[counter] : tau_u;
			}
			counter ++;
		}
	}
	return imOut;
}