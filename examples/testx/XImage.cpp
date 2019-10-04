#include "XImage.h"
#include "FreeImage.h"

XImage::XImage()
{
}

XImage::~XImage()
{
	Destroy();
}

bool XImage::Load(const char* file, VkImageView& view)
{
	//step1, ����ͼƬ�ļ�
	auto fif =FreeImage_GetFileType(file, 0);
	if (fif == FIF_UNKNOWN) return false;

	auto dib = FreeImage_Load(fif, file);
	if (!dib) return false;

	auto bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	if (!bits || !width || !height) return false;
	auto imageSize = sizeof(bits);

	//step2������buffer����
	XVkBuffer xvkStagingBuf;
	VkBufferUsageFlagBits usage = VK_BUFFER_USAGE_TRANSFER_SRC_BIT;
	VkFlags memFlags = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT;
	xvk.CreateBuffer(imageSize, usage, memFlags, xvkStagingBuf);

	//step3, ��ͼƬ������仺����
	vkMapMemory(xvk.vkDevice, xvkStagingBuf.mem, 0, VK_WHOLE_SIZE, 0, &xvkStagingBuf.pMaped);
	memcpy(xvkStagingBuf.pMaped, bits, imageSize);
	vkUnmapMemory(xvk.vkDevice, xvkStagingBuf.mem);
	FreeImage_Unload(dib);

	//step4������image����
	XVkImage xvkImg;
	VkImageUsageFlags imgUsage = VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT;
	VkMemoryPropertyFlags memProps = VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT; //���Դ��ϴ���
	xvk.CreateImage(width, height, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, imgUsage, memProps, xvkImg);

	//step5, imageת�������ʺ���Ϊ����Ŀ��ĸ�ʽ
	xvk.TransImageLayout(xvkImg.image, xvkImg.format, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);

	//step6������buffer���ݵ�image
	xvk.CopyBufferToImage(xvkStagingBuf.buffer, xvkImg.image, width, height);

	//step7��imageת�����ʺ�shader��ȡ�ĸ�ʽ
	xvk.TransImageLayout(xvkImg.image, xvkImg.format, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);


}

void XImage::Destroy()
{
	if (destroyed) return;

	vkDestroyImage(xvk.vkDevice, xvkImage.image, NULL);
	vkDestroyImageView(xvk.vkDevice, xvkImage.view, NULL);
	vkFreeMemory(xvk.vkDevice, xvkImage.mem, NULL);

}
