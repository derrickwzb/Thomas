


#define _USE_MATH_DEFINES
#include <limits>
#include "Vector2D.h"
float DegToRad(float deg);

float RadToDeg(float rad);


float Sin(float angle);

float Cos(float angle);

float Tan(float angle);
	
float ArcSin(float angle);

float ArcCos(float angle);

float ArcTan(float angle);



float SinDeg(float angle);

float CosDeg(float angle);

float TanDeg(float angle);

float ArcSinDeg(float angle);

float ArcCosDeg(float angle);

float ArcTanDeg(float angle);


float Max(float x, float y);

float DistRectToRect(Vector2D center0, float width0, float height0, Vector2D center1, float width1, float height1, Vector2D normal);

float DistPointToRect(Vector2D point, Vector2D centre, float width, float height);

float DistPointToLineSeg(Vector2D center0, float width0, float height0, Vector2D center1, float width1, float height1, Vector2D normal);



