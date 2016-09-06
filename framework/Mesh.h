#pragma once
/*
Mesh 
*/
enum MeshType
{
	MESH_NO_TYPE = -1,
	MESH_STATIC = 0,
	MESH_ANIMATION,
	MESH_SKELETAL
};
class Mesh
{
public:
	Mesh();
	virtual ~Mesh();

	int get_type();

	virtual void set_render_state(void* pScene,
		unsigned int hProg,
		int nAnimationIndex,
		float fCurentFrame) = 0;

	void set_vertex_count(int nCount);
	int  get_vertex_count();

protected:
	int m_Type;
	int m_VertexCount;
};
