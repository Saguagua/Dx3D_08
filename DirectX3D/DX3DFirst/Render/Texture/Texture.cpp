#include "framework.h"
#include "Texture.h"

map<wstring, Texture*> Texture::_textures = {};

Texture::Texture(ID3D11ShaderResourceView* srv, ScratchImage& image)
	:_srv(srv), _image(std::move(image))
{
}

Texture::~Texture()
{
	_srv->Release();
}

Texture* Texture::Get(wstring file)
{
	wstring path = file;

	if (!StartsWith(file, L"_Texture"))
		file = L"_Texture/" + file;

	assert(PathFileExists(file.c_str()));

	if (_textures.count(file) > 0)
		return _textures[file];

	wstring extension = GetExtension(file);

	ScratchImage image;

	if (extension == L"tga")
		LoadFromTGAFile(file.c_str(), nullptr, image);
	else if (extension == L"dds")
		LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);


	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	_textures[file] = new Texture(srv, image);
	_textures[file]->_path = path;

	return _textures[file];
}

Texture* Texture::Load(wstring file)
{
	wstring path = file;

	file = L"_Texture/" + file;

	assert(PathFileExists(file.c_str()));

	if (_textures.count(file) > 0)
	{

		_textures.erase(file);
	}

	wstring extension = GetExtension(file);

	ScratchImage image;

	if (extension == L"tga")
		LoadFromTGAFile(file.c_str(), nullptr, image);
	else if (extension == L"dds")
		LoadFromDDSFile(file.c_str(), DDS_FLAGS_NONE, nullptr, image);
	else
		LoadFromWICFile(file.c_str(), WIC_FLAGS_NONE, nullptr, image);


	ID3D11ShaderResourceView* srv = nullptr;

	CreateShaderResourceView(
		DEVICE,
		image.GetImages(),
		image.GetImageCount(),
		image.GetMetadata(),
		&srv
	);

	_textures[file] = new Texture(srv, image);
	_textures[file]->_path = path;

	return _textures[file];
}

void Texture::Delete()
{
	for (pair<wstring, Texture*> pair : _textures)
		delete pair.second;

	_textures.clear();
}

void Texture::PSSetShaderResoureces(UINT slot)
{
	DC->PSSetShaderResources(slot, 1, &_srv);
}

vector<Vector4> Texture::ReadPixels()
{
	unsigned char* pixels = _image.GetPixels();

	UINT size = _image.GetPixelsSize() * 0.25f;

	vector<Vector4> colors(size);

	float scale = 1.0f / 255.0f;

	UINT count = 0;

	for (Vector4& color : colors)
	{
		color.x = pixels[count++] * scale;
		color.y = pixels[count++] * scale;
		color.z = pixels[count++] * scale;
		color.w = pixels[count++] * scale;
	}

	return colors;
}

