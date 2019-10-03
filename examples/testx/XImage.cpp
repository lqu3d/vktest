#include "XImage.h"
#include "FreeImage.h"

bool XImage::Load(const char* file, VkImageView& view)
{
	auto fif =FreeImage_GetFileType(file, 0);
	if (fif == FIF_UNKNOWN) return false;

	auto dib = FreeImage_Load(fif, file);
	if (!dib) return false;

	auto bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	if (!bits || !width || !height) return false;





}
