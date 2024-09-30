// SDLFileChunks.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <stdio.h>
//#include "FileController.h"
//#include "StackAllocator.h"
//#include "ObjectPool.h"
//#include "Resource.h"
//#include "AssetController.h"
////#include "Asset.h"
//#include "Resource.h"
#include "Level.h"
int main()
{

	int cont = 1;
	char choice;
	int chunkIndex = 0;

	Level* level = new Level();
	level->AssignNonDefaultValues();
	//delete level;
	//level->ToString();
	//Level* slevel = new Level();
	//slevel = level;
	//ofstream writeStream("level.bin", ios::out | ios::binary);
	//level->Serialize(writeStream);
	//writeStream.close();
	//cout << "Level to save: ";
	//level->ToString();

	while (cont == 1) {
		std::cout << "[Q]uit	[S]ave level	[L]oad level	[Z] Undo	[Y] Redo\n[C]reate image buffer [D]elete image buffer [A]dd chunk	[R]emove chunk\nIndex ("+to_string(chunkIndex) + ") Undo count(0) Redo count(0)" << endl;
		cin >> choice;
		choice = toupper(choice);
		switch (choice) {

		case 'S': {
			//Level* slevel = new Level;
			//slevel = level;
			//slevel->AssignNonDefaultValues();
			//Level* slevel = level;
			ofstream writeStream("level.bin", ios::out | ios::binary);
			level->Serialize(writeStream);
			writeStream.close();
			cout << "Level to save: ";
			level->ToString();
			break;
		}
		case 'L': {
			delete level;
			cout << "asfter delete" << endl;
			Level* loadedLevel = new Level();
			//level = loadedLevel;


			//loadedLevel->AssignNonDefaultValues();

			ifstream readStream("level.bin", ios::in | ios::binary);

			loadedLevel->Deserialize(readStream);
			//level->Deserialize(readStream);
			readStream.close();
			cout << "Loaded Level:";
			//level->ToString();
			loadedLevel->ToString();
			level = loadedLevel;
			//delete loadedLevel;

			cout << "bytes used by image.bmp: " << AssetController::Stack->GetByteUsed() << endl;
			break;

		}
		case 'C':
		{ /*Creates a byte* image buffer, which is a member of the level. It needs to allocate the correct amount of
			memory to store a total image that will be assembled from the 7 supplied file chunks that are now loaded as
				resources(each chunk contains the asset data and byte size).You will need to calculate the total number of bytes to
				allocate for the big image dynamically by inspecting the chunk resources.After allocation, set the entire image
				buffer’s data to 0 (see memset).The application should work for any supplied image chunks, therefore you cannot
				hard - code byte sizes.This command must be an un - doable but not re - doable command.After executing the
				command, save the image buffer to NewImage.tga.*/
				//level->GetFileChunkCollectionSize();
				//Asset* asset = 
			int total = 0;
			for (int i = 0; i < level->GetFileChunkCollectionSize(); i++) {
				//level->GetFileChunkCollectionSize()
				Asset* asset = AssetController::Instance().GetAsset("chunk" + to_string(i) + ".bin");
				total += asset->GetDataSize();
				//cout << "bytes used by image.bmp: " << AssetController::Stack->GetByteUsed() << endl;
			}
			cout << total << endl;

			//Asset* asset = AssetController::Instance().GetAsset();
			int totalSize = AssetController::Stack->GetByteUsed();
			byte* imageBuffer = new byte[AssetController::Stack->GetByteUsed()];
			//cout << level->GetMemSize()<<  endl;
			memset(imageBuffer, 0, AssetController::Stack->GetByteUsed());
			level->imageBuffer = imageBuffer;

			ofstream file("NewImage.tga", ios::out | ios::binary);
			if (file.is_open()) {
				file.write(reinterpret_cast<char*>(imageBuffer), totalSize);
				file.close();
				cout << "Saving NewImage.tga" << endl;
			}

			break;
		}
		case 'D':
		{
			if (level->imageBuffer) {
				delete[] level->imageBuffer;  // Free the allocated memory
				level->imageBuffer = nullptr; // Set the pointer to null after deletion
				cout << "Image buffer deleted." << endl;
				chunkIndex = 0;//reset chunkc ounter
			}
			else {
				cout << "No image buffer to delete." << endl;
			}
			break;
		}
		case 'A':
		{
			cout << " current " << chunkIndex << endl;
			cout << level->GetFileChunkCollectionSize() << endl;
			if (level->imageBuffer && chunkIndex < level->GetFileChunkCollectionSize()) {

				Asset* asset = AssetController::Instance().GetAsset("chunk" + to_string(chunkIndex) + ".bin");
				int chunkSize = asset->GetDataSize();
				byte* chunkData = asset->GetData();
				//level->imageBuffer = asset->GetData();
				//chunkIndex++;

				// Get the current chunk to copy
				//FileChunk* currentChunk = level->GetFileChunk(level->currentChunkIndex);
				//Asset* asset = currentChunk->GetAsset();
				//int chunkSize = asset->GetSizeInBytes();  // Assuming this gives the chunk size in bytes
				//byte* chunkData = asset->GetData();       // Assuming this gives the chunk data pointer

				// Calculate the correct offset in the image buffer
				int offset = 0;
				for (int i = 0; i < chunkIndex; i++) {

					Asset* asset = AssetController::Instance().GetAsset("chunk" + to_string(i) + ".bin");
					offset += asset->GetDataSize();
					//offset += level->GetFileChunk(i)->GetAsset()->GetSizeInBytes();
				}
				cout << offset << endl;
				// Copy the current chunk into the image buffer at the calculated offset
				memcpy(level->imageBuffer + offset, chunkData, chunkSize);
				cout << "Chunk " << chunkIndex << " added to the image buffer." << endl;
				// Increment the chunk index
				if (chunkIndex < 6) {
					chunkIndex++;
				}
				if (chunkIndex == 6) {
					cout << "Can't add any more chunks after this index" << endl;
					//chunkIndex++;
				}
				//else { chunkIndex = 7; }*/
				//chunkIndex++;



				// Save the updated image buffer to a file (NewImage.tga)
				ofstream file("NewImage.tga", ios::out | ios::binary);
				if (file.is_open()) {
					file.write(reinterpret_cast<char*>(level->imageBuffer), offset + chunkSize);
					file.close();
					cout << "Image buffer saved to NewImage.tga" << endl;
				}
			}
			else {
				cout << "No image buffer or no more chunks to add." << endl;
			}
			break;
		}


		
		case 'R':
		{
			int offset = 0;
			int prevChunkIndex = chunkIndex - 1;
			cout << " current " << chunkIndex << endl;
			cout << level->GetFileChunkCollectionSize() << endl;
			// Ensure there's an image buffer and at least one chunk to remove
			if (level->imageBuffer && chunkIndex > 0) {
				// Get the chunk to remove
				Asset* asset = AssetController::Instance().GetAsset("chunk" + to_string(chunkIndex - 1) + ".bin");
				int chunkSize = asset->GetDataSize();
				byte* chunkData = asset->GetData();

				// Calculate the correct offset for the current chunk in the image buffer

				for (int i = 0; i < chunkIndex-1; i++) {
					//offset += level->GetFileChunk(i)->GetAsset()->GetSizeInBytes();

					Asset* asset = AssetController::Instance().GetAsset("chunk" + to_string(i) + ".bin");
					offset += asset->GetDataSize();
					cout << "chunk" + to_string(i) + ".bin sixe being read" << endl;
				}
				cout << offset << endl;
				// Set the memory starting from the offset to zero for the size of the chunk
				memset(level->imageBuffer + (offset), 0, chunkSize);

				// Output message to indicate the chunk has been removed
				cout << "Chunk " << chunkIndex - 1 << " removed from the image buffer." << endl;

				// Decrement the chunk index after removing the chunk
				chunkIndex--;

				// Save the updated image buffer to a file (NewImage.tga)
				ofstream file("NewImage.tga", ios::out | ios::binary);
				if (file.is_open()) {
					file.write(reinterpret_cast<char*>(level->imageBuffer), offset);
					file.close();
					cout << "Image buffer saved to NewImage.tga." << endl;
				}
			}
			else {
				// If no image buffer or no chunks to remove, output an error message
				cout << "No image buffer or no more chunks to remove." << endl;
				cout << offset << endl;
			}
			break;
		}
		
		}
	}
		

		cont = 1;
	}
	//delete level;
	//cout << endl;

	//Level* loadedLevel = new Level();
	//ifstream readStream("level.bin", ios::in | ios::binary);
	//loadedLevel->Deserialize(readStream);
	//readStream.close();
	//cout << "Loaded Level:";
	//loadedLevel->ToString();
	//delete loadedLevel;


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
