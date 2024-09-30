#include "Level.h"

Level::Level() {
	AssetController::Instance().Initialize(100000000);//allocate 100 MB

	FileChunk::Pool = new ObjectPool<FileChunk>();


	//m_fileChunk = nullptr;
	m_fileChunks.clear();

}

Level::~Level() {
	//m_units.clear();

	m_fileChunks.clear();
	cout << "after filechnk clear" << endl;
	
	delete FileChunk::Pool;
	cout << "after delete filechunkpool" << endl;

	AssetController::Instance().Clear();//free alllocated memory

}
void Level::AssignNonDefaultValues() {

	for (int count = 0; count < 7; count++) {
		FileChunk* fc = FileChunk::Pool->GetResource();
		fc->AssignNonDefaultValues();
		m_fileChunks.push_back(fc);
		
	}

	/*FileChunk* fc = FileChunk::Pool->GetResource();
	fc->AssignNonDefaultValues();*/
	
	//m_fileChunk = FileChunk::Pool->GetResource();
	
	//m_fileChunk->AssignNonDefaultValues();

	

	Resource::AssignNonDefaultValues();

}

void Level::Serialize(std::ostream& _stream) {

	int numberOfChunks = m_fileChunks.size();
	cout << std::to_string(m_fileChunks.size()) << endl;

	_stream.write(reinterpret_cast<char*>(&numberOfChunks), sizeof(numberOfChunks));
	for (int count = 0; count < numberOfChunks; count++) {
		SerializePointer(_stream, m_fileChunks[count]);
	}
	Resource::Serialize(_stream);
}

void Level::Deserialize(std::istream& _stream) {
	cout << std::to_string(m_fileChunks.size()) << endl;
	int numberOfChunks = m_fileChunks.size();
	_stream.read(reinterpret_cast<char*>(&numberOfChunks), sizeof(numberOfChunks));
	for (int count = 0; count < numberOfChunks; count++) {
		FileChunk* fileChunk;
		DeserializePointer(_stream, fileChunk);
		m_fileChunks.push_back(fileChunk);
		//fileChunk->AssignNonDefaultValues();
	}
	Resource::Deserialize(_stream);
}
void Level::ToString() {
	cout << "LEVEL" << endl;

	/*for (int count = 0; count < m_fileChunks.size(); count++) {
		m_fileChunks[count]->ToString();
	}*/
	Resource::ToString();

}

int Level::GetMemSize() {
	int totalSize = 0;
	for (int i = 0; i < m_fileChunks.size(); i++) {
		
		totalSize += (m_fileChunks[i]->GetDataSize());

		//totalSize += m_fileChunks.push_back
	}
	cout << m_fileChunks.size() << endl;
	return totalSize;
	
}