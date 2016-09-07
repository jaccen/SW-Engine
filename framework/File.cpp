#include "file.h"

namespace Utility {
	bool FileExists(const std::string& filename) {
		std::ifstream ifile(filename.c_str());
		return (bool)ifile;
	}

	void WriteString(std::ofstream *out, std::string value) {
		unsigned int size = value.size();
		out->write(reinterpret_cast<const char *>(&size), sizeof(unsigned int));
		out->write(value.c_str(), sizeof(char) * size);
	}

	void WriteBool(std::ofstream *out, bool value) {
		out->write(reinterpret_cast<const char *>(&value), sizeof(bool));
	}

	void WriteUInt(std::ofstream *out, unsigned int value) {
		out->write(reinterpret_cast<const char *>(&value), sizeof(unsigned int));
	}

	void WriteFloat(std::ofstream *out, float value) {
		out->write(reinterpret_cast<const char *>(&value), sizeof(float));
	}

	void WriteFloatV(std::ofstream *out, float *value, unsigned int count) {
		out->write(reinterpret_cast<const char *>(value), sizeof(float) * count);
	}

	void WriteVec3(std::ofstream *out, glm::vec3 value) {
		out->write(reinterpret_cast<const char *>(glm::value_ptr(value)), sizeof(float) * 3);
	}

// 	void WriteVec4(std::ofstream *out, glm::vec4 value) {
// 		out->write(reinterpret_cast<const char *>(glm::value_ptr(value)), sizeof(float) * 4);
// 	}

	void WriteQuat(std::ofstream *out, glm::quat value) {
		WriteFloat(out, value.x);
		WriteFloat(out, value.y);
		WriteFloat(out, value.z);
		WriteFloat(out, value.w);
	}

// 	void WriteMat4(std::ofstream *out, glm::mat4 value) {
// 		out->write(reinterpret_cast<const char *>(glm::value_ptr(value)), sizeof(float) * 16);
// 	}

	void CopyFile(std::string in, std::string out){
		std::ifstream in_file(in.c_str(), std::fstream::binary);
		std::ofstream out_file(out.c_str(), std::fstream::trunc | std::fstream::binary);
		out_file << in_file.rdbuf();
		in_file.close();
		out_file.close();
	}

	std::string ReadString(std::ifstream *in) {
		unsigned int size = ReadUInt(in);
		char *characters = new char[size];
		in->read(characters, sizeof(char) * size);
		std::string out(characters, size);
		delete[]characters;
		return out;
	}
	std::string ReadString(unsigned int &offset, char *in) {
		unsigned int size = ReadUInt(offset, in);
		char *characters = new char[size];
		memcpy(characters, &(in[offset]), sizeof(char) * size);
		std::string out(characters, size);
		delete[]characters;
		offset += size * sizeof(char);
		return out;
	}

	bool ReadBool(std::ifstream *in) {
		bool out;
		in->read((char *)&out, sizeof(bool));
		return out;
	}
	bool ReadBool(unsigned int &offset, char *in) {
		bool out;
		memcpy(&out, &(in[offset]), sizeof(bool));
		offset += sizeof(bool);
		return out;
	}

	unsigned int ReadUInt(std::ifstream *in) {
		unsigned int out;
		in->read((char *)&out, sizeof(unsigned int));
		return out;
	}
	unsigned int ReadUInt(unsigned int &offset, char *in) {
		unsigned int out;
		memcpy(&out, &(in[offset]), sizeof(unsigned int));
		offset += sizeof(unsigned int);
		return out;
	}

	float ReadFloat(std::ifstream *in) {
		float out;
		in->read((char *)&out, sizeof(float));
		return out;
	}
	float ReadFloat(unsigned int &offset, char *in) {
		float out;
		memcpy(&out, &(in[offset]), sizeof(float));
		offset += sizeof(float);
		return out;
	}

	float *ReadFloatV(std::ifstream *in, unsigned int size) {
		float *out = new float[size];
		in->read((char *)out, sizeof(float) * size);
		return out;
	}
	float *ReadFloatV(unsigned int &offset, char *in, unsigned int size) {
		float *out = new float[size];
		memcpy(out, &(in[offset]), sizeof(float) * size);
		offset += sizeof(float) * size;
		return out;
	}

	glm::vec3 ReadVec3(std::ifstream *in) {
		float tmp[3];
		in->read((char *)tmp, sizeof(float) * 3);
		return glm::vec3(tmp[0], tmp[1], tmp[2]);
	}
	glm::vec3 ReadVec3(unsigned int &offset, char *in) {
		float tmp[3];
		memcpy(tmp, &(in[offset]), sizeof(float) * 3);
		offset += sizeof(float) * 3;
		return glm::vec3(tmp[0], tmp[1], tmp[2]);
	}

	glm::vec4 ReadVec4(std::ifstream *in) {
		float tmp[4];
		in->read((char *)tmp, sizeof(float) * 4);
		return glm::vec4(tmp[0], tmp[1], tmp[2], tmp[3]);
	}
	glm::vec4 ReadVec4(unsigned int &offset, char *in) {
		float tmp[4];
		memcpy(tmp, &(in[offset]), sizeof(float) * 4);
		offset += sizeof(float) * 4;
		return glm::vec4(tmp[0], tmp[1], tmp[2], tmp[3]);
	}

	glm::quat ReadQuat(std::ifstream *in) {
		float tmp[4];
		tmp[0] = ReadFloat(in);
		tmp[1] = ReadFloat(in);
		tmp[2] = ReadFloat(in);
		tmp[3] = ReadFloat(in);
		return glm::quat(tmp[3], tmp[0], tmp[1], tmp[2]);
	}
	glm::quat ReadQuat(unsigned int &offset, char *in) {
		float tmp[4];
		memcpy(tmp, &(in[offset]), sizeof(float) * 4);
		offset += sizeof(float) * 4;
		return glm::quat(tmp[0], tmp[1], tmp[2], tmp[3]);
	}

	glm::mat4 ReadMat4(std::ifstream *in) {
		float tmp[16];
		in->read((char *)tmp, sizeof(float) * 16);
		glm::mat4 out(tmp[0], tmp[1], tmp[2], tmp[3],
			tmp[4], tmp[5], tmp[6], tmp[7],
			tmp[8], tmp[9], tmp[10], tmp[11],
			tmp[12], tmp[13], tmp[14], tmp[15]);
		return out;
	}
	glm::mat4 ReadMat4(unsigned int &offset, char *in) {
		float tmp[16];
		memcpy(tmp, &(in[offset]), sizeof(float) * 16);
		offset += sizeof(float) * 16;
		glm::mat4 out(tmp[0], tmp[1], tmp[2], tmp[3],
			tmp[4], tmp[5], tmp[6], tmp[7],
			tmp[8], tmp[9], tmp[10], tmp[11],
			tmp[12], tmp[13], tmp[14], tmp[15]);
		return out;
	}
}