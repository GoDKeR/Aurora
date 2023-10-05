// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2023 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Core/Core.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Graphic
{
    // -=(Undocumented)=-
    enum
    {
        // -=(Undocumented)=-
        k_Default        = 0,

        // -=(Undocumented)=-
        k_MaxAdapters    = 0x0008,

        // -=(Undocumented)=-
        k_MaxAttachments = 0x0004,

        // -=(Undocumented)=-
        k_MaxAttributes  = 0x0008,

        // -=(Undocumented)=-
        k_MaxBuffers     = 0x0080,

        // -=(Undocumented)=-
        k_MaxDisplays    = 0x0080,

        // -=(Undocumented)=-
        k_MaxMaterials   = 0x1000,

        // -=(Undocumented)=-
        k_MaxMipmap      = 0x0010,

        // -=(Undocumented)=-
        k_MaxPasses      = 0x0040,

        // -=(Undocumented)=-
        k_MaxPipelines   = 0x00C0,

        // -=(Undocumented)=-
        k_MaxSamplers    = 0x00FF,

        // -=(Undocumented)=-
        k_MaxSources     = 0x0004,

        // -=(Undocumented)=-
        k_MaxStages      = 0x0003,

        // -=(Undocumented)=-
        k_MaxTextures    = 0x0800,

        // -=(Undocumented)=-
        k_MaxUniforms    = 0x0004,
    };

    // -=(Undocumented)=-
    enum class Backend
    {
        None,
        Direct3D11,
    };

    // -=(Undocumented)=-
    enum class BlendColor
    {
        RGBA = 0b00001111,
        RGB  = 0b00000111,
        RGA  = 0b00001011,
        RBA  = 0b00001101,
        RG   = 0b00000011,
        RB   = 0b00000101,
        RA   = 0b00001001,
        R    = 0b00000001,
        GBA  = 0b00001110,
        GB   = 0b00000110,
        GA   = 0b00001010,
        G    = 0b00000010,
        BA   = 0b00001100,
        B    = 0b00000100,
        A    = 0b00001000,
        None = 0b00000000,
    };

    // -=(Undocumented)=-
    enum class BlendFactor
    {
        Zero,
        One,
        SrcColor,
        OneMinusSrcColor,
        SrcAlpha,
        OneMinusSrcAlpha,
        DstColor,
        OneMinusDstColor,
        DstAlpha,
        OneMinusDstAlpha,
    };

    // -=(Undocumented)=-
    enum class BlendFunction
    {
        Add,
        Subtract,
        ReverseSubtract,
        Min,
        Max,
    };

    // -=(Undocumented)=-
    enum class Clear
    {
        Color,
        Auxiliary,
        All,
    };

    // -=(Undocumented)=-
    enum class Cull
    {
        None,
        Back,
        Front,
    };

    // -=(Undocumented)=-
    enum class Language
    {
        Version_1,
        Version_2,
        Version_3,
        Version_4,
        Version_5,
        Version_6,
    };

    // -=(Undocumented)=-
    enum class Stage
    {
        Vertex,
        Fragment,
        Geometry,
    };

    // -=(Undocumented)=-
    enum class TestAction
    {
        Keep,
        Replace,
        Zero,
        Decrement,
        DecrementWrap,
        Invert,
        Increment,
        IncrementWrap,
    };

    // -=(Undocumented)=-
    enum class TestCondition
    {
        Always,
        Never,
        Greater,
        GreaterEqual,
        Equal,
        NotEqual,
        Less,
        LessEqual,
    };

    // -=(Undocumented)=-
    enum class TextureEdge
    {
        Clamp,
        Repeat,
        Mirror,
    };

    // -=(Undocumented)=-
    enum class TextureFilter
    {
        Nearest,
        Bilinear,
        Trilinear,
    };

    // -=(Undocumented)=-
    enum class TextureFormat
    {
        BC1UIntNorm,
        BC1UIntNorm_sRGB,
        BC2UIntNorm,
        BC2UIntNorm_sRGB,
        BC3UIntNorm,
        BC3UIntNorm_sRGB,
        BC4UIntNorm,
        BC5UIntNorm,
        BC7UIntNorm,
        BC7UIntNorm_sRGB,
        R8SInt,
        R8SIntNorm,
        R8UInt,
        R8UIntNorm,
        R16SInt,
        R16SIntNorm,
        R16UInt,
        R16UIntNorm,
        R16Float,
        R32SInt,
        R32UInt,
        R32Float,
        RG8SInt,
        RG8SIntNorm,
        RG8UInt,
        RG8UIntNorm,
        RG16SInt,
        RG16SIntNorm,
        RG16UInt,
        RG16UIntNorm,
        RG16Float,
        RG32SInt,
        RG32UInt,
        RG32Float,
        RGB32SInt,
        RGB32UInt,
        RGB32Float,
        RGBA8SInt,
        RGBA8SIntNorm,
        RGBA8UInt,
        RGBA8UIntNorm,
        RGBA8UIntNorm_sRGB,
        RGBA16SInt,
        RGBA16SIntNorm,
        RGBA16UInt,
        RGBA16UIntNorm,
        RGBA16Float,
        RGBA32SInt,
        RGBA32UInt,
        RGBA32Float,
        D16Float,
        D24Float,
        D32Float,
        D16X0UIntNorm,
        D24X0UIntNorm,
        D24S8UIntNorm,
        D32X0UIntNorm,
    };

    // -=(Undocumented)=-
    enum class TextureLayout
    {
        Source,
        Destination,
        Dual,
    };

    // -=(Undocumented)=-
    enum class Usage
    {
        Vertices,
        Indices,
        Uniform,
    };

    // -=(Undocumented)=-
    enum class VertexFormat
    {
        Float16x2,
        Float16x4,
        Float32x1,
        Float32x2,
        Float32x3,
        Float32x4,
        SInt8x4,
        SIntNorm8x4,
        UInt8x4,
        UIntNorm8x4,
        SInt16x2,
        SIntNorm16x2,
        UInt16x2,
        UIntNorm16x2,
        SInt16x4,
        SIntNorm16x4,
        UInt16x4,
        UIntNorm16x4,
    };

    // -=(Undocumented)=-
    enum class VertexTopology
    {
        Point,
        Line,
        Triangle,
    };

    // -=(Undocumented)=-
    using  Object = UInt;

    // -=(Undocumented)=-
    struct Resolution
    {
        // -=(Undocumented)=-
        UInt Width;

        // -=(Undocumented)=-
        UInt Height;

        // -=(Undocumented)=-
        UInt Frequency;
    };

    // -=(Undocumented)=-
    struct Adapter
    {
        // -=(Undocumented)=-
        SStr Description;

        // -=(Undocumented)=-
        UInt DedicatedMemoryInMBs;

        // -=(Undocumented)=-
        UInt SystemMemoryInMBs;

        // -=(Undocumented)=-
        UInt SharedMemoryInMBs;

        // -=(Undocumented)=-
        Stack<Resolution, k_MaxDisplays> Displays;
    };

    // -=(Undocumented)=-
    struct Attribute
    {
        // -=(Undocumented)=-
        SInt32       Slot   = -1;

        // -=(Undocumented)=-
        SInt32       Offset = -1;

        // -=(Undocumented)=-
        VertexFormat Format = VertexFormat::Float32x4;
    };

    // -=(Undocumented)=-
    struct Binding
    {
        // -=(Undocumented)=-
        Object Buffer = 0;

        // -=(Undocumented)=-
        UInt   Length = 0;

        // -=(Undocumented)=-
        UInt   Offset = 0;

        // -=(Undocumented)=-
        UInt   Stride = 0;
    };

    // -=(Undocumented)=-
    struct Capabilities
    {
        // -=(Undocumented)=-
        Backend  Backend  = Backend::None;

        // -=(Undocumented)=-
        Language Language = Language::Version_1;

        // -=(Undocumented)=-
        Stack<Adapter, k_MaxAdapters> Adapters;
    };

    // -=(Undocumented)=-
    struct Descriptor
    {
        // -=(Undocumented)=-
        Cull           Cull                = Cull::Back;

        // -=(Undocumented)=-
        Bool           Fill                = true;

        // -=(Undocumented)=-
        BlendColor     BlendMask           = BlendColor::RGBA;

        // -=(Undocumented)=-
        BlendFactor    BlendColorSrcFactor = BlendFactor::One;

        // -=(Undocumented)=-
        BlendFactor    BlendColorDstFactor = BlendFactor::Zero;

        // -=(Undocumented)=-
        BlendFunction  BlendColorEquation  = BlendFunction::Add;

        // -=(Undocumented)=-
        BlendFactor    BlendAlphaSrcFactor = BlendFactor::One;

        // -=(Undocumented)=-
        BlendFactor    BlendAlphaDstFactor = BlendFactor::Zero;

        // -=(Undocumented)=-
        BlendFunction  BlendAlphaEquation  = BlendFunction::Add;

        // -=(Undocumented)=-
        Bool           DepthMask           = true;

        // -=(Undocumented)=-
        TestCondition  DepthCondition      = TestCondition::LessEqual;

        // -=(Undocumented)=-
        UInt08         StencilMask         = 0b11111111;

        // -=(Undocumented)=-
        TestCondition  StencilCondition    = TestCondition::Always;

        // -=(Undocumented)=-
        TestAction     StencilOnFail       = TestAction::Keep;

        // -=(Undocumented)=-
        TestAction     StencilOnDepthFail  = TestAction::Keep;

        // -=(Undocumented)=-
        TestAction     StencilOnDepthPass  = TestAction::Keep;

        // -=(Undocumented)=-
        Attribute      InputLayout[k_MaxAttributes];

        // -=(Undocumented)=-
        VertexTopology InputTopology       = VertexTopology::Triangle;
    };

    // -=(Undocumented)=-
    struct Sampler
    {
        // -=(Undocumented)=-
        TextureEdge   EdgeU  = TextureEdge::Clamp;

        // -=(Undocumented)=-
        TextureEdge   EdgeV  = TextureEdge::Clamp;

        // -=(Undocumented)=-
        TextureFilter Filter = TextureFilter::Nearest;
    };

    // -=(Undocumented)=-
    struct Signature
    {
        // -=(Undocumented)=-
        Binding Uniforms[k_MaxUniforms];

        // -=(Undocumented)=-
        Sampler Samplers[k_MaxSources];

        // -=(Undocumented)=-
        Object  Textures[k_MaxSources] = { 0 };
    };

    // -=(Undocumented)=-
    struct Submission
    {
        // -=(Undocumented)=-
        Binding   Vertices;

        // -=(Undocumented)=-
        Binding   Indices;

        // -=(Undocumented)=-
        Recti     Scissor                = { 0, 0, UINT16_MAX, UINT16_MAX };

        // -=(Undocumented)=-
        UInt      Stencil                = 0;

        // -=(Undocumented)=-
        Object    Pipeline               = 0;

        // -=(Undocumented)=-
        Signature Root[k_MaxStages];
    };
}