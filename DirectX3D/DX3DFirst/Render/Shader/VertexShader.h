#pragma once
class VertexShader : public Shader
{
	friend class Shader;

private:
	VertexShader(wstring path);
	~VertexShader();

	void CreateInputLaout();

public:
	virtual void SetShader() override;


private:
	ID3D11InputLayout* _inputLayout;


	ID3D11VertexShader* _vertexShader;

};

