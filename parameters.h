#ifndef PARAMETERS_H
#define PARAMETERS_H
//face detection parameters
const unsigned char FACE_COLORMODEL=0x01;
const unsigned char FACE_USINGOPENCV=0x02;
const unsigned char FACE_USING_CLUSTER=0x04;
const unsigned char FACE_CASCADE_HAS_LOAD=0x01;
const unsigned char NOSE_CASCADE_HAS_LOAD=0x02;
const unsigned char EYE_CASCADE_HAS_LOAD=0x04;
const unsigned char FACE_PIXEL_VALUE=255;
const unsigned char NOTFACE_PIXEL_VALUE=0;
const double colorModelCbMean=117.4361;
const double colorModelCrMean=156.5599;
const double colorModelCov00=160.1301;
const double colorModelCov01=12.143;
const double colorModelCov10=12.143;
const double colorModelCov11=299.4574;
//Triangle
const unsigned char RENDER_ONLY_ONE_SIDE=0x01;
const unsigned char RENDER_BOTH_TWO_SIDES=0x02;
//highlight detection parameters
const unsigned char HIGHLIGHT_PIXEL_VALUE=255;
const unsigned char NOTHIGHLIGHT_PIXEL_VALUE=0;
const unsigned char HIGHLIGHT_PIXEL_CANDIDATE=128;
const unsigned char HIGHLIGHT_GLOSSY_REFLECTION_METHOD=0x01;
const unsigned char HIGHLIGHT_VALUE_SATURATION_METHOD=0x02;
const unsigned char HIGHLIGHT_LOCAL_GRADIENT_METHOD=0x04;
const unsigned char FACE_DETECTION_DONE=0x01;
const unsigned char HIGHLIGHT_DETECTION_DONE=0x02;
const unsigned char AUTOMATIC_COLOR_CORRECTION_DONE=0x04;
const unsigned char HIGHLIGHT_REMOVAL_DONE=0x08;
//highlight removal parameters
#ifdef POSSION_HSV
const double possionAttenuationRatio=0.65;
#else
const double possionAttenuationRatio=0.65;
#endif
const unsigned char HIGHLIGHT_REMOVAL_POSSION_MATHOD=0x01;
const unsigned char HIGHLIGHT_REMOVAL_INPAINTING_MATHOD=0x02;
const unsigned char HIGHLIGHT_REMOVAL_MAPPING_MATHOD=0x04;
const unsigned char HIGHLIGHT_REMOVAL_COLOR_LEVEL_METHOD=0x08;
const int patchWindowSize=7;
const double initPathError=100000000;
const int candidatePathNumber=25;
const int neighborhoodWindowSize=51;
const double sigma=5.0;
const double kesi=0.2;
const double weightFunctionH=0.0001;
//ordinary
const unsigned char INTERACTIVE_LOCAL_ENHENCEMENT_SELECTED=0x01;
const unsigned char INTERACTIVE_COLOR_CORRECTION_SELECTED=0x02;
const unsigned char INTERACTIVE_HIGHLIGHT_SELECTED=0x04;
const unsigned char INTERACTIVE_FACE_SELECTED=0x08;
const unsigned char INTERACTIVE_COLOR_LEVEL_SELECTED=0x10;
const unsigned char INTERACTIVE_COLOR_BALANCE_SELECTED=0x20;
const unsigned char INTERACTIVE_TRIANGLE_SELECTED=0x40;
const unsigned int INTERACTIVE_PIXEL_VALUE=0xff00ff00;
const double pai=3.1415926;
const unsigned char GRADIENT_ORIENTATION_HORIZONTAL=0x01;
const unsigned char GRADIENT_ORIENTATION_VERTICAL=0x02;
const unsigned char GRADIENT_MATLAB=0x01;
const unsigned char GRADIENT_NORMAL=0x02;
const int MEAN_FILTER_WINDOW_SIZE=3;
const unsigned char PIXEL_SELECTED_VALUE=255;
const unsigned char PIXEL_NOT_SELECTED_VALUE=0;
#endif