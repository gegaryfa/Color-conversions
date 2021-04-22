// http://www.easyrgb.com/index.php?X=MATH&H=02#text2
#include <stdio.h>
#include <math.h>

float ref_X = 95.047;
float ref_Y = 100.0;
float ref_Z = 108.883;

/***************************************************
 *  Name:        convertRGBtoXYZ
 *
 *  Returns:     Nothing
 *
 *  Parameters:  RGB values and XYZ references
 *
 *  Description: Given a color in RGB values converts  
 *               to the corresponding XYZ values
 *
 ***************************************************/
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


/***************************************************
 *  Name:        convertXYZtoLab
 *
 *  Returns:     Nothing
 *
 *  Parameters:  XYZ values and Lab references
 *
 *  Description: Given a color in XYZ values converts  
 *               to the corresponding Lab values
 *
 ***************************************************/
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


/***************************************************
 *  Name:        convertLabtoXYZ
 *
 *  Returns:     Nothing
 *
 *  Parameters:  Lab values and XYZ references
 *
 *  Description: Given a color in Lab values converts  
 *               to the corresponding XYZ values
 *
 ***************************************************/
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

/***************************************************
 *  Name:        convertXYZtoRGB
 *
 *  Returns:     Nothing
 *
 *  Parameters:  XYZ values and RGB references
 *
 *  Description: Given a color in XYZ values converts  
 *               to the corresponding RGB values
 *
 ***************************************************/
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

/***************************************************
 *  Name:        Lab_color_difference_CIE76
 *
 *  Returns:     float
 *
 *  Parameters:  2 Lab color values
 *
 *  Description: Calculates and returns the difference 
 *				 between 2 Lab colors based on the CIE76 formula
 *
 ***************************************************/
float Lab_color_difference_CIE76( float inL1, float ina1, float  inb1, float inL2, float ina2, float  inb2){
	return( sqrt( powf(inL1 - inL2, 2.f) + powf(ina1 - ina2, 2.f) + powf(inb1 - inb2, 2.f) ) );//CIE76
}

/***************************************************
 *  Name:        RGB_color_Lab_difference_CIE76
 *
 *  Returns:     float
 *
 *  Parameters:  2 RGB color values
 *
 *  Description: Converts RGB values to Lab values and returns  
 *				 the difference between 2 Lab colors based on 
 *				 the CIE76 formula
 *
 ***************************************************/
float RGB_color_Lab_difference_CIE76( int R1, int G1, int B1, int R2, int G2, int B2){
	float x1=0,y1=0,z1=0;
	float x2=0,y2=0,z2=0;
	float l1=0,a1=0,b1=0;
	float l2=0,a2=0,b2=0;

	convertRGBtoXYZ(R1, G1, B1, &x1, &y1, &z1);
	convertRGBtoXYZ(R2, G2, B2, &x2, &y2, &z2);

	convertXYZtoLab(x1, y1, z1, &l1, &a1, &b1);
	convertXYZtoLab(x2, y2, z2, &l2, &a2, &b2); 

	return( Lab_color_difference_CIE76(l1 ,a1 ,b1 ,l2 ,a2 ,b2) );
}

/***************************************************
 *  Name:        Lab_color_difference_CIE94
 *
 *  Returns:     float
 *
 *  Parameters:  2 Lab color values
 *
 *  Description: Calculates and returns the difference 
 *				 between 2 Lab colors based on the CIE94 formula
 *
 ***************************************************/
float Lab_color_difference_CIE94( float inL1, float ina1, float  inb1, float inL2, float ina2, float  inb2){
	// case Application.GraphicArts:
		float Kl = 1.0;
		float K1 = 0.045;
		float K2 = 0.015;
	// 	break;
	// case Application.Textiles:
	// 	Kl = 2.0;
	// 	K1 = .048;
	// 	K2 = .014;
	// break;

	float deltaL = inL1 - inL2;
	float deltaA = ina1 - ina2;
	float deltaB = inb1 - inb2;

	float c1 = sqrt(pow(ina1, 2) + pow(inb1, 2));
	float c2 = sqrt(pow(ina2, 2) + pow(inb2, 2));
	float deltaC = c1 - c2;

	float deltaH = pow(deltaA,2) + pow(deltaB,2) - pow(deltaC,2);
	deltaH = deltaH < 0 ? 0 : sqrt(deltaH);

	const float sl = 1.f;
	const float kc = 1.f;
	const float kh = 1.f;

	float sc = 1.f + K1*c1;
	float sh = 1.f + K2*c1;

	float i = pow(deltaL/(Kl*sl), 2) +
	                pow(deltaC/(kc*sc), 2) +
	                pow(deltaH/(kh*sh), 2);

	float finalResult = i < 0 ? 0 : sqrt(i);
	return (finalResult);
}

/***************************************************
 *  Name:        RGB_color_Lab_difference_CIE94
 *
 *  Returns:     float
 *
 *  Parameters:  2 RGB color values
 *
 *  Description: Converts RGB values to Lab values and returns  
 *				 the difference between 2 Lab colors based on 
 *				 the CIE94 formula
 *
 ***************************************************/
float RGB_color_Lab_difference_CIE94( int R1, int G1, int B1, int R2, int G2, int B2){
	float x1=0,y1=0,z1=0;
	float x2=0,y2=0,z2=0;
	float l1=0,a1=0,b1=0;
	float l2=0,a2=0,b2=0;

	convertRGBtoXYZ(R1, G1, B1, &x1, &y1, &z1);
	convertRGBtoXYZ(R2, G2, B2, &x2, &y2, &z2);

	convertXYZtoLab(x1, y1, z1, &l1, &a1, &b1);
	convertXYZtoLab(x2, y2, z2, &l2, &a2, &b2); 

	return( Lab_color_difference_CIE94(l1 ,a1 ,b1 ,l2 ,a2 ,b2) );
}


/***************************************************
 *  Name:        main
 *
 *  Returns:     Nothing
 *
 *  Parameters:  argc, **argv
 *
 *  Description: Running some tests
 *
 ***************************************************/
void main(int argc, char const *argv[])
{
	int R1,G1,B1,R2,G2,B2;
	float x=0.f,y=0.f,z=0.f;
	float l=0.f,a=0.f,b=0.f;

	R1 = 200;
	G1 = 2;
	B1 = 50; 

	R2 = 200;
	G2 = 2;
	B2 = 70; 

	printf("LAB DISTANCE = %lf \n", RGB_color_Lab_difference_CIE94(R1,G1,B1,R2,G2,B2) );

}
