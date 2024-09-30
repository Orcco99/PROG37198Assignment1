#ifndef FILE_CHUNK_H
#define FILE_CHUNK_H
#include "Resource.h"
#include "Asset.h"
class FileChunk : public Resource
{
public:
	//contructors/destructors
	FileChunk();
	virtual ~FileChunk();
	
	Asset* GetAsset() { return m_chunk; }
	void SetChunk(Asset* _part) { m_chunk = _part; }
	void SetDataSize(int _size) { m_size = _size; }
	int GetDataSize() { return m_size; }

	//void SetDataSize(int _size) { m_dataSize = _size; }
//	byte* GetData() { return m_data; }

	//methods
	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	int GetFileCount() { return m_fileCount; }
	void FileCountPlus() { m_fileCount++; }

	void MoveTo(Asset* _chunk);
	void Update();

	//members
	static ObjectPool<FileChunk>* Pool;
	static int m_fileCount;

	
protected:

private:
	
	bool m_dirty;

	Asset* m_chunk;
	int m_size;

};

#endif