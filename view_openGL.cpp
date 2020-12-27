#include "StdAfx.h"
#include "view_openGL.h"

// -------- PUBLIC --------
// ++++++++++++++++ VIEW_OPENGL
view_openGL::view_openGL(System::Windows::Forms::Form ^ parentForm)
{
	view_openGL_params = gcnew CreateParams;

	// Set the position on the form
	view_openGL_params->X = VIEW_OPENGL_X;
	view_openGL_params->Y = VIEW_OPENGL_Y;
	view_openGL_params->Width = VIEW_OPENGL_WIDTH;
	view_openGL_params->Height = VIEW_OPENGL_HEIGHT;

	// Specify the form as the parent.
	view_openGL_params->Parent = parentForm->Handle;

	// Create as a child of the specified parent and make OpenGL compliant (no clipping)
	view_openGL_params->Style = WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_CLIPCHILDREN;

	// Create the actual window
	this->CreateHandle(view_openGL_params);

	this->m_hDC = GetDC((HWND)this->Handle.ToPointer());

	if(this->m_hDC)
	{
		this->init_format_pixel();
	}
}

// ++++++++++++++++ ~VIEW_OPENGL
view_openGL::~view_openGL(System::Void)
{
	this->DestroyHandle();
}

// ++++++++++++++++ BUFFERS_SWAP
System::Void view_openGL::buffers_swap(System::Void)
{
	SwapBuffers(this->m_hDC);
}
// -------- PRIVATE --------
// ++++++++++++++++ INIT_FORMAT_PIXEL
int view_openGL::init_format_pixel(void)
{
	static	PIXELFORMATDESCRIPTOR pfd=				// pfd Tells Windows How We Want Things To Be
	{
		sizeof(PIXELFORMATDESCRIPTOR),				// Size Of This Pixel Format Descriptor
		1,											// Version Number
		PFD_DRAW_TO_WINDOW |						// Format Must Support Window
		PFD_SUPPORT_OPENGL |						// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,							// Must Support Double Buffering
		PFD_TYPE_RGBA,								// Request An RGBA Format
		16,											// Select Our Color Depth
		0, 0, 0, 0, 0, 0,							// Color Bits Ignored
		0,											// No Alpha Buffer
		0,											// Shift Bit Ignored
		0,											// No Accumulation Buffer
		0, 0, 0, 0,									// Accumulation Bits Ignored
		16,											// 16Bit Z-Buffer (Depth Buffer)  
		0,											// No Stencil Buffer
		0,											// No Auxiliary Buffer
		PFD_MAIN_PLANE,								// Main Drawing Layer
		0,											// Reserved
		0, 0, 0										// Layer Masks Ignored
	};

	int iPixelFormat; 

	// get the device context's best, available pixel format match 
	if((iPixelFormat = ChoosePixelFormat(this->m_hDC, &pfd)) == 0)
	{
		MessageBox::Show("ChoosePixelFormat Failed");
		return 0;
	}

	// make that match the device context's current pixel format 
	if(SetPixelFormat(this->m_hDC, iPixelFormat, &pfd) == FALSE)
	{
		MessageBox::Show("SetPixelFormat Failed");
		return 0;
	}

	if((this->m_hglrc = wglCreateContext(this->m_hDC)) == NULL)
	{
		MessageBox::Show("wglCreateContext Failed");
		return 0;
	}

	if((wglMakeCurrent(this->m_hDC, this->m_hglrc)) == NULL)
	{
		MessageBox::Show("wglMakeCurrent Failed");
		return 0;
	}

	return 1;
}
