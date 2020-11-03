// :--------------------------------------------------------------------------:
// : Copyright (C) Image Guided Therapy, Pessac, France. All Rights Reserved. :
// :--------------------------------------------------------------------------:

#include "Vector3.h"
#include "Matrix3.h"
#include "../Tools.h"
//#include <wx/xml/xml.h>
#include <fstream>
#include <limits>

namespace core {

extern TGCORE_API const Vector3 V3_NULL = Vector3(0.0, 0.0, 0.0);
extern TGCORE_API const Vector3 V3_X    = Vector3(1.0, 0.0, 0.0);
extern TGCORE_API const Vector3 V3_Y    = Vector3(0.0, 1.0, 0.0);
extern TGCORE_API const Vector3 V3_Z    = Vector3(0.0, 0.0, 1.0);
extern TGCORE_API const Vector3 P3_NULL = V3_NULL;

Vector3::Vector3(const Vector4 & v)
{
	elements[0] = v[0];
	elements[1] = v[1];
	elements[2] = v[2];
}


bool Vector3::isCollinear (const Vector3 & other, double epsilon) const
{
	return this->isNull(epsilon)
	       || other.isNull(epsilon)
	       || this->isClose(other, epsilon)
	       || (*this ^ other).isNull(epsilon);

	// return std::abs(elements[0] * other[1] - other[0] * elements[1]) < epsilon
	//	&& std::abs(elements[1] * other[2] - other[1] * elements[2]) < epsilon
	//	&& std::abs(elements[2] * other[0] - other[2] * elements[0]) < epsilon;
}


Vector3 Vector3::rotate (double xAngle, double yAngle, double zAngle) const
{
	Matrix3 matXRot(1, 0, 0, 0, cos(xAngle), -sin(xAngle), 0, sin(xAngle), cos(xAngle));
	Matrix3 matYRot(cos(yAngle), 0, sin(yAngle), 0, 1, 0, -sin(yAngle), 0, cos(yAngle));
	Matrix3 matZRot(cos(zAngle), -sin(zAngle), 0, sin(zAngle), cos(zAngle), 0, 0, 0, 1);
	return matZRot * matYRot * matXRot * (*this);
}


Vector3 Vector3::rotate (const Vector3 & axis, double rotation) const
{
	double cosR = cos(rotation);
	double sinR = sin(rotation);
	Matrix3 matRot(
		axis[0] * axis[0] * (1 - cosR) + cosR, axis[0] * axis[1] * (1 - cosR) - axis[2] * sinR, axis[0] * axis[2] * (1 - cosR) + axis[1] * sinR,
		axis[0] * axis[1] * (1 - cosR) + axis[2] * sinR, axis[1] * axis[1] * (1 - cosR) + cosR, axis[1] * axis[2] * (1 - cosR) - axis[0] * sinR,
		axis[0] * axis[2] * (1 - cosR) - axis[1] * sinR, axis[1] * axis[2] * (1 - cosR) + axis[0] * sinR, axis[2] * axis[2] * (1 - cosR) + cosR);
	return matRot * (*this);
}


double Vector3::getAngle (const Vector3 & vector) const
{
	double normThis   = this->length();
	double normVector = vector.length();

	if ((normThis == 0) || (normVector == 0)) {
		throw IGTDivideByZeroErr("angleBetweenRad");
	}

	double cosAngle = ((*this) * vector) / (normThis * normVector);
	cosAngle = getValueInRange(cosAngle, -1.0, 1.0);  // because of rounding issues. acos(1.000000000001) is undefined -_-...

	return acos(cosAngle);
}


const Vector3 & Vector3::getMainAxis() const
{
	double absX = std::abs(x());
	double absY = std::abs(y());
	double absZ = std::abs(z());

	if (absX >= absY && absX >= absZ)
		return V3_X;
	else if (absY >= absX && absY >= absZ)
		return V3_Y;
	else
		return V3_Z;

}


std::ostream & operator<< (std::ostream & os, const Vector3 & vec)
{
	os << vec.elements[0] << " " << vec.elements[1] << " " << vec.elements[2];
	return os;
}


std::istream & operator>> (std::istream & is, Vector3 & vec)
{
	is >> vec.elements[0] >> vec.elements[1] >> vec.elements[2];
	return is;
}


//wxXmlNode * Vector3::exportToXML() const
//{
	//wxXmlNode * vectorNode = new wxXmlNode(wxXML_ELEMENT_NODE, "vector3");
	//wxXmlNode * xFromNode  = new wxXmlNode(wxXML_ELEMENT_NODE, "x");
	//xFromNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, "x", wxString::Format("%.16g", elements[0])));
	//wxXmlNode * yFromNode  = new wxXmlNode(wxXML_ELEMENT_NODE, "y");
	//yFromNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, "y", wxString::Format("%.16g", elements[1])));
	//wxXmlNode * zFromNode  = new wxXmlNode(wxXML_ELEMENT_NODE, "z");
	//zFromNode->AddChild(new wxXmlNode(wxXML_TEXT_NODE, "z", wxString::Format("%.16g", elements[2])));
	//vectorNode->AddChild(xFromNode);
	//vectorNode->AddChild(yFromNode);
	//vectorNode->AddChild(zFromNode);

//	return vectorNode;
//}

//
//void Vector3::appendToStream (std::ofstream & file) const
//{
//	file << "<vector3>" << std::endl;
//	file << "<x>" << wxString::Format("%.16g", elements[0]) << "</x>" << std::endl;
//	file << "<y>" << wxString::Format("%.16g", elements[1]) << "</y>" << std::endl;
//	file << "<z>" << wxString::Format("%.16g", elements[2]) << "</z>" << std::endl;
//	file << "</vector3>" << std::endl;
//}


//void Vector3::loadFromXmlNode (wxXmlNode * vectorNode)
//{
	//if (vectorNode && vectorNode->GetName() == std::string("vector3")) {
	//	wxXmlNode * coordNode = vectorNode->GetChildren();
	//	double x = 0.0f, y = 0.0f, z = 0.0f;
	//	if (! coordNode || ! coordNode->GetNodeContent().ToDouble(&x)) {
	//		x = 0;
	//		throw IGTInvalidParameterErr("Vector3", "XML definition of Vector3: Unable to read x coordinates");
	//	}
	//	elements[0] = x;
	//	coordNode   = coordNode->GetNext();

	//	if (! coordNode || ! coordNode->GetNodeContent().ToDouble(&y)) {
	//		y = 0;
	//		throw IGTInvalidParameterErr("Vector3", "XML definition of Vector3: Unable to read y coordinates");
	//	}
	//	elements[1] = y;
	//	coordNode   = coordNode->GetNext();

	//	if (! coordNode || ! coordNode->GetNodeContent().ToDouble(&z)) {
	//		z = 0;
	//		throw IGTInvalidParameterErr("Vector3", "XML definition of Vector3: Unable to read z coordinates");
	//	}
	//	elements[2] = z;
	//}
//}


};  // namespace core
