#include "FileChunk.h"

ObjectPool<FileChunk>* FileChunk::Pool = nullptr;
int FileChunk::m_fileCount = 0;

FileChunk::FileChunk() {
	m_chunk = nullptr;
	//lastChunk = nullptr;
	//m_fileCount = 0;
}

FileChunk::~FileChunk() {
	cout<<"Deleting pool object: class FileChunk" << endl;
}

void FileChunk::AssignNonDefaultValues() {
	m_chunk = AssetController::Instance().GetAsset("chunk"+std::to_string(GetFileCount())+".bin");
	
	SetDataSize(m_chunk->GetDataSize());
	//cout << m_size<< endl;
	//cout << "Allocating asset chunk" + std::to_string(GetFileCount()) + ".bin" << endl;
	if (m_fileCount < 6) {
		FileCountPlus();
	}
	
	//FileCounter()
	//cout << "Allocating sset" << endl;
	
	Resource::AssignNonDefaultValues();

}

void FileChunk::Serialize(std::ostream& _stream) {
	SerializeAsset(_stream, m_chunk);
	Resource::Serialize(_stream);

}
void FileChunk::Deserialize(std::istream& _stream) {
	
	m_fileCount--;
	DeserializeAsset(_stream, m_chunk);
	//cout << "Deleting Asset chunk" + std::to_string(GetFileCount()) + ".bin" << endl;
	Resource::Deserialize(_stream);
}

void FileChunk::ToString() {
	cout << "chunk:" << endl;
	m_chunk->ToString();
	Resource::ToString();

}

void FileChunk::MoveTo(Asset* _chunk) {
	m_dirty = ((m_chunk != _chunk));
	//lastChunk = m_chunk;
	m_chunk = _chunk;
}

void FileChunk::Update() {
	if (m_dirty) {
		m_dirty = false;
		std::cout << "Perform Time Consuming Operation Once Per Movement.\n";

	}
}