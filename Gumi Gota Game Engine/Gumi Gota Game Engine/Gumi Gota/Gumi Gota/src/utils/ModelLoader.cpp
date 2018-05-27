
/* INCLUDES */
// Self Include
#include "ModelLoader.h"

// Normal Includes
#include <iostream>
#include <fstream>
#include <sstream>

// Header Includes
#include "../maths/vectors/vector2.h"
#include "../maths/vectors/vector3.h"



namespace gg
{

	/* ADDITIONAL FUNCTIONS */
	static std::vector<std::string> s_split(const std::string& string, const std::string& separator)
	{
		// Init
		char* charString = const_cast<char*>(string.c_str());
		char* current = strtok(charString, separator.c_str());

		std::vector<std::string> result;

		// Getting Words from Splitting
		while (current != NULL)
		{
			result.push_back(current);
			current = strtok(NULL, separator.c_str());
		}


		return result;
	}

	static void s_processVertex(const std::string& vertexDataWord,
		const std::vector<vector3>& readVertices, std::vector<float>& vertices,
		const std::vector<vector2>& readTextureCoordinates, std::vector<float>& textureCoordinates,
		const std::vector<vector3>& readNormals, std::vector<float>& normals)
	{
		std::vector<std::string> vertexData = s_split(vertexDataWord, "/");

		int vertexIndex = std::stoi(vertexData[0]) - 1;
		vertices.push_back(readVertices[vertexIndex].x);
		vertices.push_back(readVertices[vertexIndex].y);
		vertices.push_back(readVertices[vertexIndex].z);

		int textureCoordinatesIndex = std::stoi(vertexData[1]) - 1;
		textureCoordinates.push_back(readTextureCoordinates[textureCoordinatesIndex].x);
		textureCoordinates.push_back(1.0f - readTextureCoordinates[textureCoordinatesIndex].y);

		int normalIndex = std::stoi(vertexData[2]) - 1;
		normals.push_back(readNormals[normalIndex].x);
		normals.push_back(readNormals[normalIndex].y);
		normals.push_back(readNormals[normalIndex].z);
	}
	


	/* FUNCTIONS */
	Model loadModelFromFile(const std::string& objFilepath, const std::string& textureFilepath)
	{
		// Opening OBJ File
		std::ifstream fileReader(objFilepath);

		if (!fileReader.is_open())
			std::cout << "[GumiGota][Error] Coulnd't open OBJ file: " << objFilepath << std::endl;

		// Init
		unsigned int vertexCount = 0;

		std::vector<vector3> readVertices;
		std::vector<vector2> readTextureCoordinates;
		std::vector<vector3> readNormals;

		std::vector<float> vertices;
		std::vector<float> textureCoordinates;
		std::vector<float> normals;
		std::vector<unsigned int> indices;

		std::string readLine;
		std::string firstWord;
		std::string readValue[3];

		// Reading Data
		while (std::getline(fileReader, readLine))
		{
			std::istringstream iss(readLine);

			if (!(iss >> firstWord))
				break; //quitting loop if line is empty


			if (firstWord == "v") //vertices
			{
				// Reading Values from Line
				for (unsigned int i = 0; i < 3; i++)
				{
					if (!(iss >> readValue[i]))
					{
						break; //quitting loop if fails to read 3 vertices
						std::cout << "[GumiGota][Warning] File '" << objFilepath << "' might be corrupted. Failed to correctly read vertices." << std::endl;
					}
				}

				readVertices.push_back(vector3(std::stof(readValue[0], nullptr), std::stof(readValue[1], nullptr), std::stof(readValue[2], nullptr))); //putting values in vertices vector
			}
			else if (firstWord == "vt") //texture coordinates
			{
				// Reading Values from Line
				for (unsigned int i = 0; i < 2; i++)
				{
					if (!(iss >> readValue[i]))
					{
						break; //quitting loop if fails to read 3 vertices
						std::cout << "[GumiGota][Warning] File '" << objFilepath << "' might be corrupted. Failed to correctly read texture coordinates." << std::endl;
					}
				}

				readTextureCoordinates.push_back(vector2(std::stof(readValue[0], nullptr), std::stof(readValue[1], nullptr))); //putting values in texture coordinates vector
			}
			else if (firstWord == "vn") //normals
			{
				// Reading Values from Line
				for (unsigned int i = 0; i < 3; i++)
				{
					if (!(iss >> readValue[i]))
					{
						break; //quitting loop if fails to read 3 vertices
						std::cout << "[GumiGota][Warning] File '" << objFilepath << "' might be corrupted. Failed to correctly read normals." << std::endl;
					}
				}

				readNormals.push_back(vector3(std::stof(readValue[0], nullptr), std::stof(readValue[1], nullptr), std::stof(readValue[2], nullptr))); //putting values in normals vector
			}
			else if (firstWord == "f") //indices
			{
				// Reading Values from Line
				for (unsigned int i = 0; i < 3; i++)
				{
					if (!(iss >> readValue[i]))
					{
						break; //quitting loop if fails to read 3 vertices
						std::cout << "[GumiGota][Warning] File '" << objFilepath << "' might be corrupted. Failed to correctly read indices." << std::endl;
					}

					s_processVertex(readValue[i], readVertices, vertices, readTextureCoordinates, textureCoordinates, readNormals, normals);

					indices.push_back(vertexCount);
					vertexCount++;
				}
			}
			
		}


		// Finishing
		fileReader.close(); //closing file


		return Model(&vertices[0], vertices.size(), &textureCoordinates[0], textureCoordinates.size(), textureFilepath, &normals[0], normals.size(), &indices[0], indices.size());
	}

}