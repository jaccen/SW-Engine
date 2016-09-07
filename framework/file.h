#ifndef ENGINE_FILE_H
#define ENGINE_FILE_H
#include <fstream>
#include "Util.h"
namespace Utility{
	bool FileExists(const std::string& filename);
	void CopyFile(std::string in, std::string out);
	void WriteString(std::ofstream *out, std::string value);
	void WriteBool(std::ofstream *out, bool value);
	void WriteUInt(std::ofstream *out, unsigned int value);
	void WriteFloat(std::ofstream *out, float value);
	void WriteFloatV(std::ofstream *out, float *value, unsigned int count);
	void WriteVec3(std::ofstream *out, glm::vec3 value);
//	void WriteVec4(std::ofstream *out, glm::vec4 value);
	void WriteQuat(std::ofstream *out, glm::quat value);
	void WriteMat4(std::ofstream *out, glm::mat4 value);

	std::string ReadString(std::ifstream *in);
	bool ReadBool(std::ifstream *in);
	unsigned int ReadUInt(std::ifstream *in);
	float ReadFloat(std::ifstream *in);
	float *ReadFloatV(std::ifstream *in, unsigned int size);
	glm::vec3 ReadVec3(std::ifstream *in);
	glm::vec4 ReadVec4(std::ifstream *in);
	glm::quat ReadQuat(std::ifstream *in);
	glm::mat4 ReadMat4(std::ifstream *in);

	std::string ReadString(unsigned int &offset, char *in);
	bool ReadBool(unsigned int &offset, char *in);
	unsigned int ReadUInt(unsigned int &offset, char *in);
	float ReadFloat(unsigned int &offset, char *in);
	float *ReadFloatV(unsigned int &offset, char *in, unsigned int size);
	glm::vec3 ReadVec3(unsigned int &offset, char *in);
	glm::vec4 ReadVec4(unsigned int &offset, char *in);
	glm::quat ReadQuat(unsigned int &offset, char *in);
	glm::mat4 ReadMat4(unsigned int &offset, char *in);

}
#endif // !ENGINE_FILE_H
