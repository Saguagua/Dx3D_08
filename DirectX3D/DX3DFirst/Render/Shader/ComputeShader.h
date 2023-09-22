#pragma once
class ComputeShader:public Shader
{
	friend class Shader;

	ComputeShader(wstring path);
	~ComputeShader();
public:

	virtual void SetShader() override;

private:
	ID3D11ComputeShader* _shader;
};

