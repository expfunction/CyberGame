#include "CE_global.hpp"
#include "CE_asset.hpp"

using namespace CyberEngine;
	
CUID Asset::GenerateUUID()
{
	UUIDv4::UUIDGenerator<std::mt19937_64> generator;
	return generator.getUUID();
}
