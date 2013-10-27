/*
 * PROJECT:
 * FILEPATH:
 * AUTHOR:
 * DATE CREATED:
 * DATE MODIFIED:
 *
 * DESCRIPTION:
 *
 *
 */

#ifndef COLOUR_H
#define COLOUR_H

#include "initGL.h"


struct Colour {

	GLfloat r, g, b, a;
};


const Colour PT_RED     = { 0.6f, 0.0f, 0.0f, 1.f };
const Colour PT_ORANGE  = { 1.0f, 0.6f, 0.0f, 1.f };
const Colour PT_YELLOW  = { 0.6f, 0.6f, 0.0f, 1.f };
const Colour PT_GREEN   = { 0.0f, 0.6f, 0.0f, 1.f };
const Colour PT_CYAN    = { 0.0f, 0.6f, 0.6f, 1.f };
const Colour PT_BLUE    = { 0.0f, 0.0f, 0.6f, 1.f };
const Colour PT_INDIGO  = { 0.5f, 0.0f, 1.0f, 1.f };
const Colour PT_MAGENTA = { 0.6f, 0.0f, 0.6f, 1.f };
const Colour PT_WHITE   = { 1.0f, 1.0f, 1.0f, 1.f };
const Colour PT_GRAY    = { 0.4f, 0.4f, 0.4f, 1.f };
const Colour PT_BLACK   = { 0.0f, 0.0f, 0.0f, 1.f };
const Colour PT_SAND    = { 0.8f, 0.6f, 0.4f, 1.f };
const Colour PT_FIRE    = { 1.0f, 0.3f, 0.0f, 1.f };


#endif