﻿
#include "stdafx.h"

#include "ReaderFactory.h"

#include <cctype>
#include <string>
#include <algorithm>
#include "../LogWriter.h"

#ifdef SHIJTFORMAT
#include "JtReader.h"
#endif
#ifdef IFCFORMAT
#include "IfcReader.h"
#endif
#ifdef CLASSICFORMAT
#include "ClassicFormatReader.h"
#endif
#ifdef CITYGMLFORMAT
#include "CitygmlReader.h"
#endif
#ifdef POINTCLOUDFORMAT
#include "PointCloudReader.h"
#endif
#ifdef AVEVAREVIEWFORMAT
#include "AvevaRevReader.h"
#endif
#ifdef INDOORGMLFORMAT
#include "IndoorGMLReader.h"
#endif

ReaderFactory::ReaderFactory()
{
}

ReaderFactory::~ReaderFactory()
{
}

aReader* ReaderFactory::makeReader(std::string& filePath)
{
	std::string::size_type dotPosition = filePath.rfind(".");
	if(dotPosition == std::string::npos)
		return NULL;

	std::string::size_type fileExtLength = filePath.length() - dotPosition - 1;

	std::string fileExt = filePath.substr(dotPosition + 1, fileExtLength);

	std::transform(fileExt.begin(), fileExt.end(), fileExt.begin(), towlower);

#ifdef SHIJTFORMAT
	if(fileExt.compare(std::string("jt")) == 0)
	{
		return new JtReader;
	}
#endif

#ifdef IFCFORMAT
	if (fileExt.compare(std::string("ifc")) == 0)
	{
		return new IfcReader;
	}
#endif

#ifdef CLASSICFORMAT
	if (fileExt.compare(std::string("obj")) == 0 ||
		fileExt.compare(std::string("dae")) == 0 ||
		fileExt.compare(std::string("3ds")) == 0 ||
		fileExt.compare(std::string("fbx")) == 0)
	{
		return new ClassicFormatReader;
	}
#endif

#ifdef CITYGMLFORMAT
	if (fileExt.compare(std::string("gml")) == 0 ||
		fileExt.compare(std::string("xml")) == 0 ||
		fileExt.compare(std::string("citygml")) == 0)
	{
		return new CitygmlReader;
	}
#endif

#ifdef POINTCLOUDFORMAT
	if (fileExt.compare(std::string("las")) == 0 ||
		fileExt.compare(std::string("tpc")) == 0)
	{
		return new PointCloudReader;
	}
#endif

#ifdef AVEVAREVIEWFORMAT
	if (fileExt.compare(std::string("rev")) == 0)
	{
		return new AvevaRevReader;
	}
#endif

#ifdef INDOORGMLFORMAT
	if (fileExt.compare(std::string("indoorgml")) == 0)
	{
		return new IndoorGMLReader;
	}
#endif

	return NULL;
}