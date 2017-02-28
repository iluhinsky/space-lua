#include "PngLoader.h"


PngLoader::PngLoader(const char* aFileName)
	:
	mData_(0),
	mWidth_(0),
	mHeight_(0)
{
	FILE* file = fopen(aFileName, "rb");
	assert(file);
	Load_(file);
	fclose(file);
}

PngLoader::~PngLoader()
{
	delete[](char*) mData_;
}

unsigned PngLoader::GetTexture()
{
	unsigned ScaledWidth = ClosestPowerOf2_(mWidth_);
	unsigned ScaledHeight = ClosestPowerOf2_(mHeight_);
	void* ScaledPngImage = new char[ScaledWidth * ScaledHeight * 4];
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	gluScaleImage(GL_RGBA, mWidth_, mHeight_, GL_UNSIGNED_BYTE, mData_,
		ScaledWidth, ScaledHeight, GL_UNSIGNED_BYTE, ScaledPngImage);
	unsigned TextureID = 0;
	glGenTextures(1, &TextureID);
	glBindTexture(GL_TEXTURE_2D, TextureID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ScaledWidth, ScaledHeight,
		0, GL_RGBA, GL_UNSIGNED_BYTE, ScaledPngImage);

	return TextureID;
	return 0;
}

void PngLoader::ValidatePng_(FILE* aFile)
{
	png_byte Signature[8] = {};
	assert(fread(Signature, 8, 1, aFile) == 1);
	bool IsPng = !png_sig_cmp(Signature, 0, 8);

	assert(IsPng);
}

unsigned PngLoader::ClosestPowerOf2_(unsigned aNumber)
{
	unsigned x = aNumber;
	x--;
	x |= x >> 1;
	x |= x >> 2;
	x |= x >> 4;
	x |= x >> 8;
	x |= x >> 16;
	return x + 1;
}

void PngLoader::ReadData_(png_structp aPng, png_bytep aData, png_size_t aSize)
{
	FILE* Source = (FILE*)png_get_io_ptr(aPng);
	assert(fread(aData, aSize, 1, Source) == 1);
}

PngLoader::tPngAttr PngLoader::GetPngAttr_(png_structp aPng, png_infop aInfo)
{
	tPngAttr PngAttr =
	{
		png_get_image_width(aPng, aInfo),
		png_get_image_height(aPng, aInfo),
		png_get_bit_depth(aPng, aInfo),
		png_get_color_type(aPng, aInfo),
		png_get_filter_type(aPng, aInfo),
		png_get_compression_type(aPng, aInfo),
		png_get_interlace_type(aPng, aInfo)
	};
	return PngAttr;
}

void PngLoader::Load_(FILE* aFile)
{
	ValidatePng_(aFile);
	png_structp Png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!Png) printf("Couldn't initialize png read struct");
	png_infop Info = png_create_info_struct(Png);
	if (!Info)
	{
		png_destroy_read_struct(&Png, (png_infopp)0, (png_infopp)0);
		printf("Couldn't initialize png info struct");
	}
	png_set_read_fn(Png, (png_voidp)aFile, ReadData_);
	png_set_sig_bytes(Png, 8);
	png_read_info(Png, Info);

	tPngAttr PngAttr = GetPngAttr_(Png, Info);

	switch (PngAttr.ColorType)
	{
	case PNG_COLOR_TYPE_GRAY:
	case PNG_COLOR_TYPE_GRAY_ALPHA:
		png_set_gray_to_rgb(Png);
		png_read_update_info(Png, Info);
		PngAttr = GetPngAttr_(Png, Info);
		break;

	case PNG_COLOR_TYPE_PALETTE:
		png_set_palette_to_rgb(Png);
		png_read_update_info(Png, Info);
		PngAttr = GetPngAttr_(Png, Info);
		break;

	case PNG_COLOR_TYPE_RGB:
	case PNG_COLOR_TYPE_RGBA:
		break;

	default:
		printf("Unsupported png color format");
		break;
	}

	if (PngAttr.ColorType == PNG_COLOR_TYPE_RGB)
	{
		png_set_add_alpha(Png, 255, PNG_FILLER_AFTER);
		png_read_update_info(Png, Info);
		PngAttr = GetPngAttr_(Png, Info);
	}
	if (PngAttr.BitDepth == 16)
	{
		png_set_strip_16(Png);
		png_read_update_info(Png, Info);
		PngAttr = GetPngAttr_(Png, Info);
	}
	if (PngAttr.BitDepth < 8)
	{
		png_set_packing(Png);
		png_read_update_info(Png, Info);
		PngAttr = GetPngAttr_(Png, Info);
	}

	unsigned Stride = PngAttr.Width * 4;
	png_bytep* RowPointers = new png_bytep[PngAttr.Height];
	mData_ = new char[PngAttr.Height * Stride];
	mWidth_ = PngAttr.Width;
	mHeight_ = PngAttr.Height;

	for (size_t i = 0; i < PngAttr.Height; i++)
	{
		int Offset = (PngAttr.Height - i - 1) * Stride;
		RowPointers[i] = (png_bytep)mData_ + Offset;
	}
	png_read_image(Png, RowPointers);
	delete[] RowPointers;
	png_destroy_read_struct(&Png, &Info, (png_infopp)0);
}