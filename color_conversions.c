// http://www.easyrgb.com/index.php?X=MATH&H=02#text2
#include <stdio.h>
#include <math.h>

float ref_X = 95.047;
float ref_Y = 100.0;
float ref_Z = 108.883;


void convertRGBtoXYZ(int inR, int inG, int inB, float * outX, float * outY, float * outZ) {


	float var_R = (inR / 255.0f); //R from 0 to 255
	float var_G = (inG / 255.0f); //G from 0 to 255
	float var_B = (inB / 255.0f); //B from 0 to 255

	if (var_R > 0.04045f)
		var_R = powf(( (var_R + 0.055f) / 1.055f), 2.4f);
	else 
		var_R = var_R / 12.92f;

	if (var_G > 0.04045)
		var_G = powf(( (var_G + 0.055f) / 1.055f), 2.4f);
	else
		var_G = var_G / 12.92f;

	if (var_B > 0.04045f)
		var_B = powf(( (var_B + 0.055f) / 1.055f), 2.4f);
	else
		var_B = var_B / 12.92f;

	var_R = var_R * 100;
	var_G = var_G * 100;
	var_B = var_B * 100;

	//Observer. = 2°, Illuminant = D65
	*outX = var_R * 0.4124f + var_G * 0.3576f + var_B * 0.1805f;
	*outY = var_R * 0.2126f + var_G * 0.7152f + var_B * 0.0722f;
	*outZ = var_R * 0.0193f + var_G * 0.1192f + var_B * 0.9505f;
}

void convertXYZtoLab(float inX, float inY, float inZ, float * outL, float * outa, float * outb) {

	float var_X = (inX / ref_X); //ref_X = 95.047
	float var_Y = (inY / ref_Y); //ref_Y = 100.0
	float var_Z = (inZ / ref_Z); //ref_Z = 108.883

	if ( var_X > 0.008856 ) 
		var_X = powf(var_X , ( 1.0f/3 )); 
	else 
		var_X = ( 7.787 * var_X ) + ( 16.0f/116 );

	if ( var_Y > 0.008856 )
		var_Y = powf(var_Y , ( 1.0f/3 )); 
	else
	    var_Y = ( 7.787 * var_Y ) + ( 16.0f/116 );

	if ( var_Z > 0.008856 )
		var_Z = powf(var_Z , ( 1.0f/3 )); 
	else 
		var_Z = ( 7.787 * var_Z ) + ( 16.0f/116 );

	*outL = ( 116 * var_Y ) - 16;
	*outa = 500 * ( var_X - var_Y );
	*outb = 200 * ( var_Y - var_Z );
}

void convertLabtoXYZ( float inL, float ina, float  inb, float * outX, float * outY, float * outZ) {

	float var_Y = ( inL + 16 ) / 116;
	float var_X = (ina/500) + var_Y;
	float var_Z = var_Y - (inb/200);

	if ( powf(var_Y,3.f) > 0.008856 ) 
		var_Y = powf(var_Y,3.f);
	else
		var_Y = ( var_Y - (16/116) ) / 7.787;

	if ( powf(var_X,3.f) > 0.008856 ) 
		var_X = powf(var_X,3.f);
	else 
		var_X = ( var_X - (16/116) ) / 7.787;
	
	if ( powf(var_Z,3.f) > 0.008856 )
		var_Z = powf(var_Z,3.f);
	else
		var_Z = ( var_Z - (16/116) ) / 7.787;

	*outX = ref_X * var_X;     //ref_X =  95.047     Observer= 2°, Illuminant= D65
	*outY = ref_Y * var_Y;     //ref_Y = 100.000
	*outZ = ref_Z * var_Z;     //ref_Z = 108.883
}

void convertXYZtoRGB(float inX, float inY, float inZ, int * outR, int * outG, int * outB) {


	float var_X = inX/100;
	float var_Y = inY/100;
	float var_Z = inZ/100;

	float var_R = var_X *  3.2406 + (var_Y * -1.5372) + var_Z * (-0.4986);
	float var_G = var_X * (-0.9689) + var_Y *  1.8758 + var_Z *  0.0415;
	float var_B = var_X *  0.0557 + var_Y * (-0.2040) + var_Z *  1.0570;

	if ( var_R > 0.0031308 )
		var_R = 1.055 * powf(var_R, ( 1.0f / 2.4 ) )  - 0.055;
	else 
		var_R = 12.92 * var_R;

	if ( var_G > 0.0031308 ) 
		var_G = 1.055 * powf(var_G, ( 1.0f / 2.4 ) ) - 0.055;
	else 
		var_G = 12.92 * var_G;

	if ( var_B > 0.0031308 )
		var_B = 1.055 * powf(var_B, ( 1.0f / 2.4 ) ) - 0.055;
	else
		var_B = 12.92 * var_B;

	*outR = (int)(var_R * 255);
	*outG = (int)(var_G * 255);
	*outB = (int)(var_B * 255);


}


void main(int argc, char const *argv[])
{
	int R=0,G=0,B=0;
	float x=0.f,y=0.f,z=0.f;
	float l=0.f,a=0.f,b=0.f;

	R = 20;
	G = 32;
	B = 60; 

	convertRGBtoXYZ(R, G, B, &x, &y, &z);
	printf("R =%d,G =%d,B =%d,x =%lf,y =%lf,z =%lf\n",R,G,B,x,y,z );

	convertXYZtoLab(x, y, z, &l, &a, &b);
	printf("x =%lf,y =%lf,z =%lf, l =%lf,a =%lf,b =%lf\n",x,y,z, l,a,b );

	convertLabtoXYZ( l, a, b ,&x, &y, &z);
	printf("x =%lf,y =%lf,z =%lf, l =%lf,a =%lf,b =%lf\n",x,y,z, l,a,b );

	convertXYZtoRGB( x, y, z,&R, &G, &B);
	printf("R =%d,G =%d,B =%d,x =%lf,y =%lf,z =%lf\n",R,G,B,x,y,z );

}