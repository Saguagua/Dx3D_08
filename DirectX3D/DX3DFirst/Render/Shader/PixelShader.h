#pragma once
class PixelShader : public Shader
{
	friend class Shader;

private:
	PixelShader(wstring path);
	~PixelShader();

public:
	// Shader��(��) ���� ��ӵ�
	virtual void SetShader() override;

private:
	ID3D11PixelShader* _pixelShader;
};

