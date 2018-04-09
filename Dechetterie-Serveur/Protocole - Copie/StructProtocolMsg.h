#pragma once
using namespace System;
using namespace System::Text;

ref class ProtocolMsg
{
	Encoding^ encoder = Encoding::ASCII;
public:
	int lenght;
	int type;
	array<Byte>^ data1;
	array<Byte>^ data2 = gcnew array<Byte>(1);
	array<Byte>^ raw;
	String^ GetString()
	{
		return ("Taille = " + lenght + " | Type = " + type + " | Data1 = + encoder->GetString(data1) +  | Data2 = ");// + encoder->GetString(data2)
	}

	int getData1Int()
	{
		return Convert::ToInt32(encoder->GetString(data1));
	}
	String^ getData1String()
	{
		return encoder->GetString(data1);
	}
	Boolean getData1Boolean()
	{
		if (encoder->GetString(data1) == "1")
		{
			return true;
		}
		else
		{
			return false;
		}
		
	}
};