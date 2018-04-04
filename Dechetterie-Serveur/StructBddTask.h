#pragma once
using namespace System;

ref struct BddTask
{
	int type; //1 insert 2 delete
	String^ table;
	int id;
};
