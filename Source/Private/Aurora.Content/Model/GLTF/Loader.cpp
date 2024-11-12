// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2024 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Loader.hpp"
#define TINYGLTF_IMPLEMENTATION
#define TINYGLTF_NO_STB_IMAGE_WRITE
#include <tiny_gltf.h>
#include <Aurora.Content/Service.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Content
{
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Graphic::VertexSemantic As(CStr Name)
    {
        static  Table<SStr, Graphic::VertexSemantic> kMapping
        {
            { "NORMAL",     Graphic::VertexSemantic::Normal },
            { "POSITION",   Graphic::VertexSemantic::Position },
            { "COLOR",      Graphic::VertexSemantic::Color },
            { "TANGENT",    Graphic::VertexSemantic::Tangent },
            { "TEXCOORD_0", Graphic::VertexSemantic::TexCoord0 },
            { "TEXCOORD_1", Graphic::VertexSemantic::TexCoord1 },
            { "TEXCOORD_2", Graphic::VertexSemantic::TexCoord2 },
            { "TEXCOORD_3", Graphic::VertexSemantic::TexCoord3 },
        };

        const auto Iterator = kMapping.find(Name.data());
        return (Iterator == kMapping.end() ? Graphic::VertexSemantic::None : Iterator->second);
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Graphic::Sampler LoadSampler(Ref<const tinygltf::Sampler> GLTFSampler)
    {
        Graphic::Sampler Sampler;

        switch (GLTFSampler.wrapS)
        {
		case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            Sampler.EdgeU = Graphic::TextureEdge::Clamp;
            break;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            Sampler.EdgeU = Graphic::TextureEdge::Mirror;
            break;
        default:
            Sampler.EdgeU = Graphic::TextureEdge::Repeat;
            break;
        }
        switch (GLTFSampler.wrapT)
        {
        case TINYGLTF_TEXTURE_WRAP_CLAMP_TO_EDGE:
            Sampler.EdgeV = Graphic::TextureEdge::Clamp;
            break;
        case TINYGLTF_TEXTURE_WRAP_MIRRORED_REPEAT:
            Sampler.EdgeV = Graphic::TextureEdge::Mirror;
            break;
        default:
            Sampler.EdgeU = Graphic::TextureEdge::Repeat;
            break;
        }

        switch (GLTFSampler.minFilter)
        {
        case TINYGLTF_TEXTURE_FILTER_NEAREST:
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_NEAREST:    // @NOT_SUPPORTED
        case TINYGLTF_TEXTURE_FILTER_NEAREST_MIPMAP_LINEAR:     // @NOT_SUPPORTED
            Sampler.Filter = Graphic::TextureFilter::Nearest;
            break;
        case TINYGLTF_TEXTURE_FILTER_LINEAR:
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_NEAREST:     // @NOT_SUPPORTED
            Sampler.Filter = Graphic::TextureFilter::Bilinear;
            break;
        case TINYGLTF_TEXTURE_FILTER_LINEAR_MIPMAP_LINEAR:
            Sampler.Filter = Graphic::TextureFilter::Trilinear;
            break;
        default:
            Sampler.Filter = Graphic::TextureFilter::Nearest;
            break;
        }
        return Sampler;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    SPtr<Graphic::Texture> LoadTexture(Ref<tinygltf::Model> GLTFModel, Ref<const tinygltf::Texture> GLTFTexture)
    {
        Ref<const tinygltf::Image>   GLTFImage   = GLTFModel.images[GLTFTexture.source];

        Data Chunk(GLTFImage.image.size());
        memcpy(Chunk.GetData<UInt8>(), GLTFImage.image.data(), GLTFImage.image.size());

        constexpr UInt8 k_DefaultMipmaps = 1;
        constexpr UInt8 k_DefaultSamples = 1;

        const SPtr<Graphic::Texture> Texture = NewPtr<Graphic::Texture>(Uri { GLTFTexture.name });
        Texture->Load(
                Graphic::TextureFormat::RGBA8UIntNorm,
                Graphic::TextureLayout::Source, GLTFImage.width, GLTFImage.height, k_DefaultMipmaps, k_DefaultSamples, Move(Chunk));
        return Texture;
    }

    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    Bool GLTFLoader::OnLoad(Ref<Service> Service, Any<Data> File, Ref<Graphic::Model> Asset)
    {
        tinygltf::TinyGLTF GLTFLoader;
        tinygltf::Model    GLTFModel;

        // Parse the model asset using TinyGLTF
        SStr Error;

        const Bool Result = GLTFLoader.LoadBinaryFromMemory(
            AddressOf(GLTFModel), AddressOf(Error), nullptr, File.GetData<UInt8>(), File.GetSize());
        if (!Result)
        {
            Log::Warn("GLTFLoader: {}", Error);
            return false;
        }

        // Safe-guard against big model(s).
        if (GLTFModel.meshes.size() > Graphic::Mesh::k_MaxPrimitives)
        {
            Log::Warn("GLTFLoader: Exceeding maximum sub-mesh support of {} with {}",
                Graphic::Mesh::k_MaxPrimitives, GLTFModel.meshes.size());
            return false;
        }

        // Find how many bytes we need for buffer(s) and create them
        UInt32 BytesForVertices = 0;
        UInt32 BytesForIndices  = 0;
        for (Ref<const tinygltf::BufferView> View : GLTFModel.bufferViews)
        {
            if (View.target == TINYGLTF_TARGET_ARRAY_BUFFER)
            {
                BytesForVertices += View.byteLength;
            }
            else
            {
                BytesForIndices += View.byteLength;
            }
        }

        UInt32 OffsetForVertices = 0;
        UInt32 OffsetForIndices  = 0;
        Data   BlockForVertices(BytesForVertices);
        Data   BlockForIndices(BytesForIndices);
        for (Ref<tinygltf::BufferView> View : GLTFModel.bufferViews)
        {
            if (View.target == TINYGLTF_TARGET_ARRAY_BUFFER)
            {
                memcpy(
                    BlockForVertices.GetData<UInt8>() + OffsetForVertices,
                    AddressOf(GLTFModel.buffers[View.buffer].data[View.byteOffset]), View.byteLength);
                View.byteOffset = OffsetForVertices;
                OffsetForVertices += View.byteLength;
            }
            else
            {
                memcpy(
                     BlockForIndices.GetData<UInt8>() + OffsetForIndices,
                     AddressOf(GLTFModel.buffers[View.buffer].data[View.byteOffset]), View.byteLength);
                View.byteOffset = OffsetForIndices;
                OffsetForIndices += View.byteLength;
            }
        }

        // Parse each material from the model
        Array<SPtr<Graphic::Material>, Graphic::Mesh::k_MaxPrimitives> Materials { };
        for (UInt32 ID = 0; Ref<const tinygltf::Material> GLTFMaterial : GLTFModel.materials)
        {
            const SPtr<Graphic::Material> Material = NewPtr<Graphic::Material>(Uri { GLTFMaterial.name });
            Material->SetResidence(true);

            if (SInt32 Index = GLTFMaterial.pbrMetallicRoughness.baseColorTexture.index; Index >= 0)
            {
                Ref<const tinygltf::Texture> GLTFTexture = GLTFModel.textures[Index];

                Material->SetTexture(Graphic::Source::Diffuse, LoadTexture(GLTFModel, GLTFTexture));
                Material->SetSampler(Graphic::Source::Diffuse, LoadSampler(GLTFModel.samplers[GLTFTexture.sampler]));
            }
            if (SInt32 Index = GLTFMaterial.pbrMetallicRoughness.metallicRoughnessTexture.index; Index >= 0)
            {
                Ref<const tinygltf::Texture> GLTFTexture = GLTFModel.textures[Index];

                Material->SetTexture(Graphic::Source::Roughness, LoadTexture(GLTFModel, GLTFTexture));
                Material->SetSampler(Graphic::Source::Roughness, LoadSampler(GLTFModel.samplers[GLTFTexture.sampler]));
            }
            if (SInt32 Index = GLTFMaterial.normalTexture.index; Index >= 0)
            {
                Ref<const tinygltf::Texture> GLTFTexture = GLTFModel.textures[Index];

                Material->SetTexture(Graphic::Source::Normal, LoadTexture(GLTFModel, GLTFTexture));
                Material->SetSampler(Graphic::Source::Normal, LoadSampler(GLTFModel.samplers[GLTFTexture.sampler]));
            }
            if (SInt32 Index = GLTFMaterial.emissiveTexture.index; Index >= 0)
            {
                Ref<const tinygltf::Texture> GLTFTexture = GLTFModel.textures[Index];

                Material->SetTexture(Graphic::Source::Emissive, LoadTexture(GLTFModel, GLTFTexture));
                Material->SetSampler(Graphic::Source::Emissive, LoadSampler(GLTFModel.samplers[GLTFTexture.sampler]));
            }
            if (SInt32 Index = GLTFMaterial.occlusionTexture.index; Index >= 0)
            {
                Ref<const tinygltf::Texture> GLTFTexture = GLTFModel.textures[Index];

                Material->SetTexture(Graphic::Source::Occlusion, LoadTexture(GLTFModel, GLTFTexture));
                Material->SetSampler(Graphic::Source::Occlusion, LoadSampler(GLTFModel.samplers[GLTFTexture.sampler]));
            }

            // @TODO: Create uniform buffer for the PBR / Custom properties

            Materials[ID++] = Material;
        }

        // Parse each mesh from the model
        const SPtr<Graphic::Mesh> Mesh = NewPtr<Graphic::Mesh>(Uri { Asset.GetKey() });
        Mesh->Load(Move(BlockForVertices), Move(BlockForIndices));

        for (Ref<const tinygltf::Mesh> GLTFMesh : GLTFModel.meshes)
        {
            if (GLTFMesh.primitives.size() > 1)
            {
                Log::Warn("GLTFLoader: Multiple primitives unsupported, skipping {}", GLTFMesh.name);
                continue;
            }

            Ref<const tinygltf::Primitive> GLTFPrimitive = GLTFMesh.primitives[0];

            // Parse material
            Graphic::Mesh::Primitive Primitive;
            Primitive.Material = static_cast<SInt8>(GLTFPrimitive.material);

            // Parse vertices
            for (const auto & [Name, Accessor] : GLTFPrimitive.attributes)
            {
                Ref<const tinygltf::Accessor>   GLTFAccessor = GLTFModel.accessors[Accessor];
                Ref<const tinygltf::BufferView> GLTFView     = GLTFModel.bufferViews[GLTFAccessor.bufferView];

                const UInt32 Length = tinygltf::GetComponentSizeInBytes(GLTFAccessor.componentType)
                              * tinygltf::GetNumComponentsInType(GLTFAccessor.type)
                              * GLTFAccessor.count;
                const UInt32 Offset = GLTFView.byteOffset + GLTFAccessor.byteOffset;
                const UInt32 Stride = GLTFAccessor.ByteStride(GLTFView);

                if (const Graphic::VertexSemantic Semantic = As(Name); Semantic != Graphic::VertexSemantic::None)
                {
                    Primitive.Attributes[CastEnum(Semantic)] = { Length, Offset, Stride };
                }
            }

            // Parse indices
            if (GLTFPrimitive.indices >= 0)
            {
                Ref<const tinygltf::Accessor>   GLTFAccessor = GLTFModel.accessors[GLTFPrimitive.indices];
                Ref<const tinygltf::BufferView> GLTFView     = GLTFModel.bufferViews[GLTFAccessor.bufferView];

                const UInt32 Length = tinygltf::GetComponentSizeInBytes(GLTFAccessor.componentType)
                              * tinygltf::GetNumComponentsInType(GLTFAccessor.type)
                              * GLTFAccessor.count;
                const UInt32 Offset = GLTFView.byteOffset + GLTFAccessor.byteOffset;
                const UInt32 Stride = GLTFAccessor.ByteStride(GLTFView);

                Primitive.Indices = { Length, Offset, Stride };
            }

            // Continue with the next submesh
            Mesh->AddPrimitive(Move(Primitive));
        }

        Asset.Load(Mesh, Move(Materials));
        return true;
    }
}