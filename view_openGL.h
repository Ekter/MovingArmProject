#pragma once

#include "include_define.h"
#include "model_openGL.h"

using namespace System::Windows::Forms;

public ref class view_openGL: public System::Windows::Forms::NativeWindow
{
    public:
        view_openGL(System::Windows::Forms::Form^);
        ~view_openGL(System::Void);

		System::Void buffers_swap(System::Void);

	private:
		CreateParams^ view_openGL_params;
      
		HDC m_hDC;
		HGLRC m_hglrc;

		int init_format_pixel(void);
};
