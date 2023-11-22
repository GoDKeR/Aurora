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

#include "SciterInput.hpp"
#include <Content/Service.hpp>
#include <Input/Service.hpp>
#include <Graphic/Renderer.hpp>
#include <Platform/Service.hpp>
#include <Platform/Window.hpp>

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace UI
{
    // -=(Undocumented)=-
    class SciterHost final : public Subsystem
    {
    public:

        // -=(Undocumented)=-
        using OnScriptCall = FPtr<sciter::value(CPtr<const sciter::value>)>;

        // -=(Undocumented)=-
        using OnScriptDraw = FPtr<void(CStr ID, Ptr<DRAW_PARAMS> Parameters)>;

    public:

        // -=(Undocumented)=-
        SciterHost(Ref<Context> Context);

        // -=(Undocumented)=-
        ~SciterHost();

        // \see Subsystem::OnTick
        void OnTick() override;

        // -=(Undocumented)=-
        Bool Initialise(ConstSPtr<Platform::Window> Window, ConstSPtr<Graphic::Renderer> Renderer);

        // -=(Undocumented)=-
        void Draw();

        // -=(Undocumented)=-
        Bool Load(CStr16 Uri);

        // -=(Undocumented)=-
        Bool Call(CStr16 Function, CPtr<const sciter::value> Parameters, Ptr<sciter::value> Return);

        // -=(Undocumented)=-
        Bool Eval(CStr16 Script, Ptr<sciter::value> Return);

        // -=(Undocumented)=-
        void CreateFunction(CStr Name, OnScriptCall Method);

        // -=(Undocumented)=-
        void DeleteFunction(CStr Name);

        // -=(Undocumented)=-
        void SetVariable(CStr Name, Ref<const sciter::value> Value);

        // -=(Undocumented)=-
        sciter::value GetVariable(CStr Name);

    private:

        // -=(Undocumented)=-
        void OnSciterLoad(LPSCN_LOAD_DATA Data);

        // -=(Undocumented)=-
        void OnSciterRender(LPCBYTE Bytes, INT X, INT Y, UINT Width, UINT Height);

        // -=(Undocumented)=-
        Bool OnSciterRenderElement(HELEMENT Element, Ptr<DRAW_PARAMS> Parameters);

        // -=(Undocumented)=-
        UInt OnSciterAttachBehaviour(LPSCN_ATTACH_BEHAVIOR Behavior);

        // -=(Undocumented)=-
        Bool OnSciterCall(Ptr<SCRIPTING_METHOD_PARAMS> Parameters);

    private:

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        SPtr<Platform::Window>      mDisplay;
        Bool                        mDisplayIsDirty;

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        StringTable<OnScriptCall>   mFunctions;

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        Graphic::Object             mDevice;       // TODO: Class?
        SPtr<Graphic::Renderer>     mRenderer;
        SPtr<Graphic::Material>     mMaterial;
        SPtr<Graphic::Pipeline>     mPipeline;
    };
}