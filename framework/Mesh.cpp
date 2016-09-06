#include "Mesh.h"


Mesh::Mesh()
{
	m_Type = MESH_NO_TYPE;
}


Mesh::~Mesh()
{
}

int Mesh::get_vertex_count()
{
	return m_VertexCount;
}

void Mesh::set_vertex_count(int nCount)
{
	m_VertexCount = nCount;
}

int Mesh::get_type()
{
	return m_Type;
}
