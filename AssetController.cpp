#include "AssetController.h"
#include "FileController.h"
#include <string>
StackAllocator* AssetController::Stack = nullptr;

AssetController::AssetController() {

}

void AssetController::Initialize(int _stackSize) {
	Stack = new StackAllocator();
	AssetController::Stack->AllocateStack(_stackSize);//allocates n numebr of bytes to stack
	Asset::Pool = new ObjectPool<Asset>();
}

AssetController::~AssetController() {
	Clear();
}
void AssetController::Clear() {
	//REMOVE ALL OBJECTS FROM OBJECT POOL
	
	for (auto const& x : m_assets) {
		Asset::Pool->ReleaseResource(x.second);
		cout << "Deleting asset ";
		cout << (x.first) << endl;
	}
	if (Asset::Pool != nullptr) {
		delete Asset::Pool;
		Asset::Pool = nullptr;
	}
	Stack->ClearMemory();
	m_assets.clear();
}

Asset* AssetController::GetAsset(string _guid) {

	//if asset has alreeady been loaded return loaded asset
	if (m_assets.count(_guid) != 0) {
		return m_assets[_guid];
	}

	//otherwise load the asset and return it
	Asset* asset = Asset::Pool->GetResource();
	asset->SetGUID(_guid);
	asset->SetDataSize(FileController::Instance().GetFileSize(_guid));
	asset->SetData(Stack->GetMemory(asset->GetDataSize()));
	
	FileController::Instance().ReadFile(_guid, asset->GetData(), asset->GetDataSize());
	cout << "Allocating asset " + (_guid) << endl;
	
	//adde new asset tot he map 
	m_assets[_guid] = asset;

	return asset;
}