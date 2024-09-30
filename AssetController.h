#ifndef ASSET_CONTROLLER_H
#define ASSET_CONTROLLER_H
#include "StackAllocator.h"
#include "StandardIncludes.h"
#include "Asset.h"

class AssetController : public Singleton<AssetController>
{
public:
	//constructor/destructor
	AssetController();
	virtual ~AssetController();

	//Methods
	void Initialize(int _stackSize);
	void Clear();
	Asset* GetAsset(string _guid);

	//members
	static StackAllocator* Stack;
private:
	//member
	map<string, Asset*> m_assets;
};
#endif

