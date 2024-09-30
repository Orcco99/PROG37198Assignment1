#ifndef LEVEL_H
#define LEVEL_H
//#include "UnitWSound.h"
#include "Unit.h"
#include "FileChunk.h"
class Level : public Resource
{
public:
	Level();
	virtual ~Level();

	void Serialize(std::ostream& _stream) override;
	void Deserialize(std::istream& _stream) override;
	void ToString() override;
	void AssignNonDefaultValues() override;
	int GetFileChunkCollectionSize() { return m_fileChunks.size(); }
	int GetMemSize();

	byte* imageBuffer;
private:
	//int fileChunkCollectionSize;
	vector<FileChunk*> m_fileChunks;

	//FileChunk* m_fileChunk;

};

#endif