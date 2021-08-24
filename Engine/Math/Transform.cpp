#include "Transform.h"

namespace glds
{
	void Transform::Update()
	{
		Matrix33 mtxS;
		mtxS.Scale(scale);

		Matrix33 mtxR;
		mtxR.Rotate(rotation);

		Matrix33 mtxT;
		mtxT.Translate(position);

		matrix = mtxS * mtxR * mtxT;
	}

	void Transform::Update(const Matrix33& mtx)
	{
		Matrix33 mtxS;
		mtxS.Scale(localScale);

		Matrix33 mtxR;
		mtxR.Rotate(localRotation);

		Matrix33 mtxT;
		mtxT.Translate(localPosition);

		matrix = mtxS * mtxR * mtxT * mtx;

		position = matrix.GetTranslate();
		rotation = matrix.GetRotation();
		scale = matrix.GetScale();
	}

	bool Transform::Write(const rapidjson::Value& value) const
	{
		return false;
	}

	bool Transform::Read(const rapidjson::Value& value)
	{
		JSON_READ(value, position);
		JSON_READ(value, rotation);
		JSON_READ(value, scale);

		return true;
	}
}