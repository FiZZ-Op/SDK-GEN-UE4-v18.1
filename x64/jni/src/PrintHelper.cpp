#include "PrintHelper.hpp"

#include "tinyformat.h"

#include "IGenerator.hpp"
#include "Package.hpp"


void PrintFileHeader(std::ostream& os, const std::vector<std::string>& includes, bool isHeaderFile)
{
	extern IGenerator* generator;

	if (isHeaderFile)
	{
		os << "#pragma once\n\n";
	}

	os << tfm::format("// %s (%s) SDKGen by @Unknown_Xd\n", generator->GetGameName(), generator->GetGameVersion());

	if (!includes.empty())
	{
		for (auto&& i : includes) { os << "#include " << i << "\n"; }
		os << "\n";
	}

	if (!generator->GetNamespaceName().empty())
	{
		os << "namespace " << generator->GetNamespaceName() << "\n{\n";
	}
}

void PrintFileHeader(std::ostream& os, bool isHeaderFile)
{
	extern IGenerator* generator;

	PrintFileHeader(os, std::vector<std::string>(), isHeaderFile);
}

void PrintFileFooter(std::ostream& os)
{
	extern IGenerator* generator;

	if (!generator->GetNamespaceName().empty())
	{
		os << "}\n\n";
	}

}

void PrintSectionHeader(std::ostream& os, const char* name)
{
	os << "//---------------------------------------------------------------------------\n"
		<< "//" << name << "\n"
		<< "//---------------------------------------------------------------------------\n\n";
}

std::string GenerateFileName(FileContentType type, const Package& package)
{
	extern IGenerator* generator;

	const char* name;
	switch (type)
	{
	case FileContentType::Structs:
		name = "%s_%s_structs.hpp";
		break;
	case FileContentType::Classes:
		name = "%s_%s_classes.hpp";
		break;
	case FileContentType::Functions:
		name = "%s_%s_functions.cpp";
		break;
	case FileContentType::FunctionParameters:
		name = "%s_%s_parameters.hpp";
		break;
	default:
		assert(false);
	}

	return tfm::format(name, generator->GetGameNameShort(), package.GetName());
}
