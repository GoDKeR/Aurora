// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Copyright (C) 2021-2024 by Agustin Alvarez. All rights reserved.
//
// This work is licensed under the terms of the MIT license.
//
// For a copy, see <https://opensource.org/licenses/MIT>.
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#pragma once

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [  HEADER  ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

#include "Aurora.Input/Common.hpp"
#include "Aurora.Graphic/Common.hpp"

// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// [   CODE   ]
// -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

namespace Engine
{
    // -=(Undocumented)=-
    class Device
    {
    public:

        // -=(Undocumented)=-
        Device(UInt Handle, CStr Title, UInt16 Width, UInt16 Height, Graphic::Backend Backend, Bool Fullscreen, Bool Borderless);

        // -=(Undocumented)=-
        ~Device();

        // -=(Undocumented)=-
        Ptr<SDL_Window> GetHandle()
        {
            return mHandle;
        }

        // -=(Undocumented)=-
        void SetTitle(CStr Title)
        {
            SDL_SetWindowTitle(mHandle, Title.data());
        }

        // -=(Undocumented)=-
        CStr GetTitle() const
        {
            return SDL_GetWindowTitle(mHandle);
        }

        // -=(Undocumented)=-
        void SetVisible(Bool Visible)
        {
            if (Visible)
            {
                SDL_ShowWindow(mHandle);
            }
            else
            {
                SDL_HideWindow(mHandle);
            }
        }

        // -=(Undocumented)=-
        Bool IsVisible() const
        {
            return (SDL_GetWindowFlags(mHandle) & SDL_WINDOW_HIDDEN) == 0;
        }

        // -=(Undocumented)=-
        void SetFocus()
        {
            SDL_RaiseWindow(mHandle);
        }

        // -=(Undocumented)=-
        Bool IsFocused() const
        {
            return (SDL_GetWindowFlags(mHandle) & SDL_WINDOW_INPUT_FOCUS) != 0;
        }

        // -=(Undocumented)=-
        void SetMode(Bool Fullscreen, Bool Borderless);

        // -=(Undocumented)=-
        Bool IsBorderless() const
        {
            return (SDL_GetWindowFlags(mHandle) & SDL_WINDOW_BORDERLESS) != 0;
        }

        // -=(Undocumented)=-
        Bool IsWindowed() const
        {
            return (SDL_GetWindowFlags(mHandle) & SDL_WINDOW_FULLSCREEN) == 0;
        }

        // -=(Undocumented)=-
        Bool IsFullscreen() const
        {
            return (SDL_GetWindowFlags(mHandle) & SDL_WINDOW_FULLSCREEN) != 0;
        }

        // -=(Undocumented)=-
        void SetSize(UInt16 Width, UInt16 Height)
        {
            mWidth  = Width;
            mHeight = Height;
            SDL_SetWindowSize(mHandle, Width, Height);
        }

        // -=(Undocumented)=-
        UInt16 GetWidth() const
        {
            return mWidth;
        }

        // -=(Undocumented)=-
        UInt16 GetHeight() const
        {
            return mHeight;
        }

        // -=(Undocumented)=-
        Real32 GetScale() const
        {
            return SDL_GetWindowDisplayScale(mHandle);
        }

        // -=(Undocumented)=-
        void SetClipboard(CStr Text)
        {
            SDL_SetClipboardText(Text.data());
        }

        // -=(Undocumented)=-
        SStr GetClipboard() const
        {
            return SDL_GetClipboardText();
        }

    private:

        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
        // -=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

        Ptr<SDL_Window> mHandle;
        UInt16          mWidth;
        UInt16          mHeight;
    };
}