/*Copyright reserved by KenLee@2018 ken4000kl@gmail.com*/
#include "Model.h"

using namespace std;

Model::Model(const GLchar* filepath) : Drawable() {
	// ��ʼ��
	directory = "";
	meshes.clear();
	cachedTextures.clear();
	loadModel(filepath);
}

Model::~Model() {

}

void Model::draw(const Shader* pShader, const Camera* pCamera) {
    //
    if(pShader != nullptr) {
        pShader->use();
        glUniformMatrix4fv(glGetUniformLocation(pShader->programID, "model"), 1, GL_FALSE, glm::value_ptr(getModelMat()));
        if(pCamera != nullptr) {
            glUniformMatrix4fv(glGetUniformLocation(pShader->programID, "view"), 1, GL_FALSE, pCamera->getViewMatrixVal());
            glUniformMatrix4fv(glGetUniformLocation(pShader->programID, "projection"), 1, GL_FALSE, pCamera->getProjectionMatrixVal());
        }
    }
    //
    for(UInt i = 0; i < meshes.size(); ++i) {
        meshes[i]->draw(pShader);
    }
}

void Model::drawInstanced(const Shader* pShader, const Camera* pCamera) {

}

void Model::loadModel(string filepath) {
	//
	checkFileExist(filepath.c_str());
	//������
	Assimp::Importer importer;
	//����ָ�룬ִ�����ǻ���������ת��������
	const aiScene* scene = importer.ReadFile(filepath, aiProcess_Triangulate | aiProcess_FlipUVs);
	//������
	if (scene == nullptr || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || scene->mRootNode == nullptr) {
		printf("[Error] Model Loading Error: %s\n\n", importer.GetErrorString());
		return;
	}
	// ��¼�ļ�Ŀ¼�Լ������·���ļ�(������)
	size_t pos = filepath.rfind('/');
	directory = filepath.substr(0, pos + 1);
	//
	dLog("[Info] ===== Loading model with total %d meshes: ===== \n", scene->mNumMeshes);
	// �Ӹ��ڵ㿪ʼ��������ģ��
	processNode(scene->mRootNode, scene);
	//
	dLog("[Info] ===== Model loading finished. ===== \n\n");
}


void Model::processNode(const aiNode* node, const aiScene* scene) {
	//
	ddLog("    |-- Load %d Meshes from a node.\n", node->mNumMeshes);
	// ���ɵ�ǰ�ڵ������Mesh
	for (UInt i = 0; i < node->mNumMeshes; ++i) {
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		processMesh(mesh, scene);
	}
	// �ݹ鴦���ӽڵ�
	for (UInt i = 0; i < node->mNumChildren; ++i) {
		this->processNode(node->mChildren[i], scene);
	}
}

void Model::processMesh(const aiMesh* mesh, const aiScene* scene) {
	// ����Mesh��Ҫ������
	vector<MeshVertex> vertices;
	vector<UInt> indices;
	//
	ddLog("        |-- Load %d Vertices from a mesh.\n", mesh->mNumVertices);
	// ����������
	for (UInt i = 0; i < mesh->mNumVertices; ++i) {
		MeshVertex vertex;
		Vec3 tmpVec3;
		Vec2 tmpVec2 = Vec2(0.0f, 0.0f);
		// λ��
		tmpVec3.x = mesh->mVertices[i].x;
		tmpVec3.y = mesh->mVertices[i].y;
		tmpVec3.z = mesh->mVertices[i].z;
		vertex.position = tmpVec3;
		// ����
		if (mesh->mNormals) {
			tmpVec3.x = mesh->mNormals[i].x;
			tmpVec3.y = mesh->mNormals[i].y;
			tmpVec3.z = mesh->mNormals[i].z;
			vertex.normal = tmpVec3;
		}
		// ����
		if (mesh->mTextureCoords[0]) {
			tmpVec2.x = mesh->mTextureCoords[0][i].x;
			tmpVec2.y = mesh->mTextureCoords[0][i].y;
			vertex.texCoord = tmpVec2;
		}
		// �Ѷ���Ž�ȥ
		vertices.push_back(vertex);
	}
	// ������������(���ڿ��������ǻ�������mNumIndices��ʵ����ԶΪ3)
	for (UInt i = 0; i < mesh->mNumFaces; i++) {
		aiFace face = mesh->mFaces[i];
		for (UInt j = 0; j < face.mNumIndices; j++) {
			indices.push_back(face.mIndices[j]);
		}
	}
	// ��������ӳ��: ASSIMP�������� -> Nene��������
    vector<shared_ptr<Texture>> textures;
	vector<TextureType> texTypes;
	if (mesh->mMaterialIndex >= 0) {
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
		loadMaterialTextures(material, aiTextureType_DIFFUSE, TEXTURE_DIFFUSE, textures, texTypes);
		loadMaterialTextures(material, aiTextureType_SPECULAR, TEXTURE_SPECULAR, textures, texTypes);
		loadMaterialTextures(material, aiTextureType_AMBIENT, TEXTURE_REFLECT, textures, texTypes);
		//loadMaterialTextures(material, aiTextureType_HEIGHT, TEXTURE_NORMAL, textures, texTypes);// ��֪��Ϊɶ assimp ��map_bump ������heightmap
		//loadMaterialTextures(material, aiTextureType_LIGHTMAP, TEXTURE_AMBIENT_OCCLUSION, textures, texTypes);
	}
	// Debug ���
	ddLog("        |-- Process Mesh with:\n");
	ddLog("            Normal? : %s.\n", mesh->mNormals ? "Yes" : "No");
	ddLog("            Vertices: %d\n", vertices.size());
	ddLog("            Indices : %d\n", indices.size());
	ddLog("            Textures: %d\n", textures.size());
	// �����ɵ��������ѹ���Ա����
	meshes.push_back(unique_ptr<Mesh> (new Mesh(vertices, indices, textures, texTypes)));
}

void Model::loadMaterialTextures(aiMaterial* material, aiTextureType typeAssimp,
	TextureType typeNene, vector<shared_ptr<Texture>> &textures, vector<TextureType> &texTypes) {
	// һ���Զ�ȡͬ���͵�����
	for (UInt i = 0; i < material->GetTextureCount(typeAssimp); ++i) {
		// ��ȡ������ļ���
		aiString texFileName;
		material->GetTexture(typeAssimp, i, &texFileName);
		// ���������ļ�·��
		string texFilePath = directory + texFileName.C_Str();
		// ���֮ǰ�Ƿ��ȡ��
		auto it = cachedTextures.find(texFilePath);
		if (it == cachedTextures.end()) {
			// ֮ǰû��ȡ��, �����µ��������
			shared_ptr<Texture> pNewTexture(new Texture(texFilePath.c_str(), GL_BGRA, GL_RGBA));
			cachedTextures.insert(make_pair(texFilePath, pNewTexture));
			textures.push_back(pNewTexture);
			ddLog("            loaded new texture file[type: %d]: %s\n", typeNene, texFilePath.c_str());
		} else {
			// ֮ǰ�Ѿ���ȡ���������ظ���ȡ
			textures.push_back(it->second);
			ddLog("            loaded cached texture file[type: %d]: %s\n", typeNene, texFilePath.c_str());
		}
		// д������������
		texTypes.push_back(typeNene);
	}
}
