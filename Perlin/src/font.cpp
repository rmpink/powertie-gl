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

#include "../lib/font.h"
#include FT_BITMAP_H

FT_Library Font::mLibrary;


////////////////////////////////////
//			  PRIVATE			  //
////////////////////////////////////
GLfloat Font::CalcStringWidth( const char* newString ) {

	GLfloat strWidth = 0.f;

	for ( int i = 0; newString[i] != '\0' && newString[i] != '\n'; ++i ) {

		if ( newString[i] == ' ' ) {

			strWidth += mSpaceWidth;

		} else {

			strWidth += GetClip(i).w;

		}

	}

	return strWidth;

}


GLfloat Font::CalcStringHeight( const char* newString ) {

	GLfloat strHeight = mLineHeight;

	for ( int i = 0; newString[i] != '\0'; ++i ) {

		if ( newString[i] == '\n' ) {

			strHeight += mLineHeight;

		}

	}

	return strHeight;

}


////////////////////////////////////
//			   PUBLIC			  //
////////////////////////////////////
bool Font::InitFreeType() {

	bool success = true;

	printf("Font::InitFreeType()\n");

	//Init FreeType for single threaded applications
    #ifndef __FREEGLUT_H__
        FT_Error error = FT_Init_FreeType( &mLibrary );
        if( error )
        {
            printf( "FreeType error:%X", error );
            success false;
        }
    #endif

	return success;

}


Font::Font() {

	printf("Font::Font()\n");

	mSpaceWidth = 0.f;
	mLineHeight = 0.f;
	mNewLine	= 0.f;

}


Font::~Font() {

	printf("Font::~Font()\n");

	FreeFont();

}


bool Font::LoadFromBitmap( std::string path ) {

	bool success = true;

	printf("Font::LoadFromBitmap()\n");

	FreeFont();
	SetPixelFormat( GL_ALPHA );

	if ( LoadFromFile( path ) ) {

		GLfloat cellWidth = GetImageWidth() / FONT_CELL_COLS;
		GLfloat cellHeight = GetImageHeight() / FONT_CELL_ROWS;

		GLuint glyphTop 	 = cellHeight;
		GLuint glyphBottom 	 = 	   0;
		GLuint glyphBaseline =     0;

		int currentX = 0;
		int currentY = 0;
		int offsetX  = 0;
		int offsetY  = 0;

		GLuint glyphChar = 0;
		Clip   glyphClip = { 0.f, 0.f, cellWidth, cellHeight };

		for ( unsigned int row = 0; row < FONT_CELL_ROWS; ++row ) {

			for ( unsigned int col = 0; col < FONT_CELL_COLS; ++col ) {

				offsetX = cellWidth * col;
				offsetY = cellHeight * row;

				glyphClip.x = offsetX;
				glyphClip.y = offsetY;
				glyphClip.w = cellWidth;
				glyphClip.h = cellHeight;

				//Left side of glyph
				for ( int clipX = 0; clipX < cellWidth; ++clipX ) {

					for ( int clipY = 0; clipY < cellHeight; ++clipY ) {

						currentX = offsetX + clipX;
						currentY = offsetY + clipY;

						if ( GetPixel( currentX, currentY ) != FONT_BLACK_PIXEL ) {

							glyphClip.x = currentX;

							clipX = cellWidth;
							clipY = cellHeight;

						}

					}

				}

				//Right side of glyph
				for ( int clipX = cellWidth-1; clipX >= 0; --clipX ) {

					for ( int clipY = 0; clipY < cellHeight; ++clipY ) {

						currentX = offsetX + clipX;
						currentY = offsetY + clipY;

						if ( GetPixel( currentX, currentY ) != FONT_BLACK_PIXEL ) {

							glyphClip.w = ( currentX - glyphClip.x ) + 1;

							clipX = -1;
							clipY = cellHeight;

						}

					}

				}

				//Top side of tallest glyph
				for ( GLuint clipY = 0; clipY < cellHeight; ++clipY ) {

					for ( GLuint clipX = 0; clipX < cellWidth; ++clipX ) {

						currentX = offsetX + clipX;
						currentY = offsetY + clipY;

						if ( GetPixel( currentX, currentY ) != FONT_BLACK_PIXEL ) {

							if ( clipY < glyphTop ) {
								
								glyphTop = clipY;

							}

							clipX = cellWidth;
							clipY = cellHeight;

						}

					}

				}

				//Bottom of lowest glyph & baseline
				for ( GLuint clipY = cellHeight - 1; clipY >= 0; --clipY ) {

					for ( GLuint clipX = 0; clipX < cellWidth; ++clipX ) {

						currentX = offsetX + clipX;
						currentY = offsetY + clipY;

						if ( GetPixel( currentX, currentY ) != FONT_BLACK_PIXEL ) {

							if ( glyphChar == 'A' ) {

								glyphBaseline = clipY;

							}

							if ( clipY > glyphBottom ) {

								glyphBottom = clipY;

							}

							clipX = cellWidth;
							clipY = -1;

						}

					}

				}

				AddSprite( glyphClip );
				glyphChar++;

			}

		}

		//Set glyph tops according to tallest glyph
		for ( unsigned int i = 0; i < ( FONT_CELL_COLS * FONT_CELL_ROWS ); ++i ) {

			SetClipY( i, GetClip(i).y + glyphTop );
			SetClipHeight( i, GetClip(i).h - glyphTop );

		}

		if ( LoadFromPixels() ) {

			if ( !GenerateVBO( SPRITE_ORIGIN_TOP_LEFT ) ) {
				//Some error code: FONT_VBO_CREATION_FAIL
				printf("FONT_VBO_CREATION_FAIL\n");
				success = false;
			}
		} else {
			//Some error code: FONT_PIXELS_LOAD_FAIL
			printf("FONT_PIXELS_LOAD_FAIL\n");
			success = false;
		}

		glBindTexture( GL_TEXTURE_2D, GetID() );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
		glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

		mSpaceWidth = cellWidth / 2;
		mLineHeight = glyphBottom - glyphTop;
		mNewLine	= glyphBaseline - glyphTop;

	} else {
		//Some error code: FONT_BITMAP_LOAD_ERROR
		printf("FONT_BITMAP_LOAD_ERROR\n");
		success = false;
	}

	return success;

}


bool Font::LoadFromFile( std::string path, GLuint fontSize ) {

	bool success = true;
	FT_Error error = (FT_Error)NULL;

	printf("Font::LoadFromFile()\n");

	#ifdef __FREEGLUT_H__

		error = FT_Init_FreeType( &mLibrary );

		if ( error ) {
			//Some error code: FONT_INIT_FREETYPE_FAIL
			printf("FONT_INIT_FREETYPE_FAIL\n");
			success = false;
		}

	#endif

	if ( success ) {

		GLuint cellWidth  = 0;
		GLuint cellHeight = 0;
		int maxBearing    = 0;
		int minHang		  = 0;

		Texture bitmaps[ FONT_CELL_COLS * FONT_CELL_ROWS ];
		FT_Glyph_Metrics metrics[ FONT_CELL_COLS * FONT_CELL_ROWS ];
		FT_Face face = NULL;

		error = FT_New_Face( mLibrary, path.c_str(), 0, &face );

		if ( !error ) {

			error = FT_Set_Pixel_Sizes( face, 0, fontSize );

			if ( !error ) {

				for ( unsigned int i = 0; i < (FONT_CELL_COLS * FONT_CELL_ROWS ); ++i ) {

					error = FT_Load_Char( face, i, FT_LOAD_RENDER );

					if ( !error ) {

						metrics[i] = face->glyph->metrics;
						bitmaps[i].SetPixelData( face->glyph->bitmap.buffer, face->glyph->bitmap.width, face->glyph->bitmap.rows );
						int glyphHang = ( metrics[i].horiBearingY - metrics[i].height )/64;

						if ( metrics[i].horiBearingY/64 > maxBearing ) {

							maxBearing = metrics[i].horiBearingY/64;

						}

						if ( metrics[i].width/64 > cellWidth ) {

							cellWidth = metrics[i].width/64;

						}

						if ( glyphHang < minHang ) {

							minHang = glyphHang;

						}

					} else {
						//Some error code: FONT_FT_LOAD_CHAR_FAIL
						printf("FONT_FT_LOAD_CHAR_FAIL\n");
						success = false;
					}

				}

				cellHeight = maxBearing - minHang;

				CreatePixels( cellWidth * FONT_CELL_COLS, cellHeight * FONT_CELL_ROWS );

				GLuint glyphChar = 0;
				Clip   glyphClip = { 0.f, 0.f, (GLfloat)cellWidth, (GLfloat)cellHeight };

				int offsetX = 0;
				int offsetY = 0;

				for ( unsigned int clipY = 0; clipY < FONT_CELL_ROWS; ++clipY ) {

					for ( unsigned int clipX = 0; clipX < FONT_CELL_COLS; ++clipX ) {

						offsetX = cellWidth * clipX;
						offsetY = cellHeight * clipY;

						glyphClip.x = offsetX;
						glyphClip.y = offsetY;
						glyphClip.w = metrics[glyphChar].width/64;
						glyphClip.h = cellHeight;

						bitmaps[glyphChar].BlitPixels( offsetX, offsetY + maxBearing - metrics[glyphChar].horiBearingY/64, *this );

						AddSprite( glyphClip );
						glyphChar++;

					}

				}

				PadPixels();

				if ( LoadFromPixels() ) {

					if ( !GenerateVBO( SPRITE_ORIGIN_TOP_LEFT ) ) {
						//Some error code: FONT_GENERATE_VBO_FAIL
						printf("FONT_GENERATE_VBO_FAIL\n");
						success = false;
					}
				} else {
					//Some error code: FONT_LOAD_PIXELS_FAIL
					printf("FONT_LOAD_PIXELS_FAIL\n");
					success = false;
				}

				glBindTexture( GL_TEXTURE_2D, GetID() );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
				glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE );

				mSpaceWidth = cellWidth / 2;
				mLineHeight = cellHeight;
				mNewLine    = maxBearing;

			} else {
				//Some error code: FONT_SET_FONT_SIZE_FAIL
				printf("FONT_SET_FONT_SIZE_FAIL\n");
				success = false;
			}

			FT_Done_Face( face );

		} else {
			//Some error code: FONT_FT_NEW_FACE_FAILED
			printf("FONT_FT_NEW_FACE_FAILED\n");
			success = false;
		}

		#ifdef __FREEGLUT_H__
			FT_Done_FreeType( mLibrary );
		#endif

	}

	return success;

}


void Font::FreeFont() {

	printf("Font::FreeFont()\n");

	FreeTexture();

	mSpaceWidth = 0.f;
	mLineHeight = 0.f;
	mNewLine	= 0.f;

}


bool Font::Render( GLfloat x, GLfloat y, std::string text, Clip* area, GLuint fontAlign ) {

	bool success = true;

	//printf("Font::Render()\n");

	if ( GetID() ) {

		GLfloat drawX = 0.f;
		GLfloat drawY = 0.f;

		if ( area ) {

			if ( fontAlign & FONT_ALIGN_LEFT ) {

				drawX = area->x;

			} else if ( fontAlign & FONT_ALIGN_CENTER ) {

				drawX = area->x + ( area->w - CalcStringWidth( text.c_str() ) ) / 2.f;

			} else if ( fontAlign & FONT_ALIGN_RIGHT ) {

				drawX = area->x + ( area->w - CalcStringWidth( text.c_str() ) );

			} else {

				drawX = area->x;

			}

			if ( fontAlign & FONT_ALIGN_TOP ) {

				drawY = area->y;

			} else if ( fontAlign & FONT_ALIGN_MIDDLE ) {

				drawY = area->y + ( area->h - CalcStringHeight( text.c_str() ) ) / 2.f;

			} else if ( fontAlign & FONT_ALIGN_BOTTOM ) {

				drawY = area->y + ( area->h - CalcStringHeight( text.c_str() ) );

			} else {

				drawY = area->y;

			}

		}

		glTranslatef( drawX, drawY, 0.f );

		glBindTexture( GL_TEXTURE_2D, GetID() );
		glEnableClientState( GL_VERTEX_ARRAY );
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );

			glBindBuffer( GL_ARRAY_BUFFER, GetVBOID() );

			glTexCoordPointer( 2, GL_FLOAT, sizeof( VertexData2D), (GLvoid*)offsetof( VertexData2D, tPos ) );
			glVertexPointer( 2, GL_FLOAT, sizeof( VertexData2D ), (GLvoid*)offsetof( VertexData2D, vPos ) );

			for ( int i = 0; i < (int)text.length(); ++i ) {

				GLfloat targetX = 0.f;

				switch( text[i] ) {
				case ' ':
					glTranslatef( mSpaceWidth, 0.f, 0.f );
					drawX += mSpaceWidth;

					break;
				case '\n':
					targetX = x;

					if ( area ) {

						if ( fontAlign & FONT_ALIGN_LEFT ) {

							targetX = area->x;

						} else if ( fontAlign & FONT_ALIGN_CENTER ) {

							targetX = area->x + ( area->w - CalcStringWidth( text.c_str() ) ) / 2.f;

						} else if ( fontAlign & FONT_ALIGN_RIGHT ) {

							targetX = area->x + ( area->w - CalcStringWidth( text.c_str() ) );

						} else {

							targetX = area->x;

						}

					}

					glTranslatef( targetX - drawX, mNewLine, 0.f );

					drawX += targetX - drawX;
					drawY += mNewLine;

					break;
				default:
					glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, GetIBOIDs()[ (int)text[i] ] );
					glDrawElements( GL_QUADS, 4, GL_UNSIGNED_INT, NULL );

					glTranslatef( GetClip( text[i] ).w, 0.f, 0.f );

					drawX += GetClip( text[i] ).w;

					break;
				}

			}

		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
		glDisableClientState( GL_VERTEX_ARRAY );

	} else {
		//Some error code: FONT_RENDER_NO_ID
		printf("FONT_RENDER_NO_ID\n");
		success = false;
	}

	return success;

}


GLfloat Font::GetLineHeight() {

	return mLineHeight;

}


GLfloat Font::GetNewLine() {

	return mNewLine;

}


GLfloat Font::GetSpaceWidth() {

	return mSpaceWidth;

}


Clip Font::GetStringArea( std::string text ) {

	GLfloat strWidth = 0.f;
	Clip area = { 0.f, 0.f, strWidth, mLineHeight };

	for ( int i = 0; i < (int)text.length(); ++i ) {

		switch ( text[i] ) {

			case ' ':
				strWidth += mSpaceWidth;

				break;
			case '\n':
				area.h += mLineHeight;

				if ( strWidth > area.w ) {

					area.w = strWidth;
					strWidth = 0.f;

				}

				break;
			default:
				strWidth += GetClip( text[i] ).w;

				break;

		}

	}

	if ( strWidth > area.w ) {

		area.w = strWidth;

	}

	return area;

}