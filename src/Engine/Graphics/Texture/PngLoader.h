#pragma once
#include "../../../Include.h"
#include <png.h>


class PngLoader
{
public:
	PngLoader(const char* aFileName);
	~PngLoader();

	unsigned	GetTexture();

	void* 		Data  () { return mData_;   }
	unsigned	Width () { return mWidth_;  }
	unsigned 	Height() { return mHeight_; }

private:
	struct tPngAttr
	{
		unsigned Width;
		unsigned Height;
		unsigned BitDepth;
		unsigned ColorType;
		unsigned FilterType;
		unsigned CompressionType;
		unsigned InterlaceType;
	};

	void Load_(FILE* aFile);
	void ValidatePng_(FILE* aFile);
	tPngAttr GetPngAttr_(png_structp aPng, png_infop aInfo);

	static void ReadData_(png_structp aPng, png_bytep aData, png_size_t aSize);
	static unsigned ClosestPowerOf2_(unsigned aNumber);


	void*		mData_;
	unsigned	mWidth_;
	unsigned	mHeight_;
};