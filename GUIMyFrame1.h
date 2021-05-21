#ifndef __GUIMyFrame1__
#define __GUIMyFrame1__

/**
@file
Subclass of MyFrame1, which is generated by wxFormBuilder.
*/


#include "GUI.h"

#include <vector>
#include <string>
#include <wx/msgdlg.h>
#include <wx/dcmemory.h>
#include <wx/dcclient.h>
#include <wx/dcbuffer.h>
#include <wx/msgdlg.h>
#include "wx/dirdlg.h"
#include <wx/dir.h>
#include <wx/stattext.h>
#include <wx/bmpbuttn.h>
#include <wx/bitmap.h>
#include "FreeImage.h"
//// end generated include
#include "wx/custombgwin.h"
#include "wx/wx.h"
#include <iostream>
class Point
{
public:
	Point(int xUpLeft, int yUpLeft, int xDownRight, int yDownRigth)
		: _xUpLeft(xUpLeft), _yUpLeft(yUpLeft), _xDownRight(xDownRight), _yDownRigth(yDownRigth) {}
	~Point() = default;
	int _xUpLeft;
	int _yUpLeft;
	int _xDownRight;
	int _yDownRigth;
};

/*
class Thumbnail{
public:
	Thumbnail(wxWindow* parent, wxString fileName)
	{
		m_filename = fileName;
		wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);

		wxImage image=wxImage(m_filename);
		m_bitmap = wxBitmap(image,-1);
		wxBitmap smallBmp = m_bitmap;
		//m_bitmapButton = new wxBitmapButton(this, wxID_ANY, smallBmp);
		//sizer.Add(m_bitmapButton, 1, wxCenter,3);
		//wxEVT_BUTTON(-1, new wxEventListener(OnBitmapButtonClicked));
	}
protected:
	//void OnBitmapButtonClicked(wxObject& event, wxEvent& event){
		// Notify our listeners
		/*if (ThumbnailClicked != null) {
			ThumbnailClicked(m_fileName, m_bitmap);
		}
	//}
private:
	wxBitmap m_bitmap;
	wxString m_filename;
	wxBitmapButton *m_bitmapButton;
};*/


/** Implementing MyFrame1 */
class GUIMyFrame1 : public MyFrame1
{
	friend class MyButton;
	friend class Panel2;
public:
	/** Constructor */
	GUIMyFrame1(wxWindow* parent);
	wxArrayString path_array;
	size_t file_count;
	wxImage* m_imageRGB;
	wxBitmap m_imageBitmap;
	int window_width;
	int window_height;
	bool imageLoaded;
	int m_imageWidth;
	int m_imageHeight;
	int m_imageCounter;
	int m_fullImagesWidth;
	int m_fullImagesHeight;
	unsigned char* m_myImage;

	wxFlexGridSizer* fgSizer1;
	std::map<int, Point> imagesPosition;
	//// end generated class members
	int panel_width;
	int panel_height;
	//two vectors - not necessary in final version
	std::vector<wxBitmap> bitmap;
	std::vector<wxBitmapButton> bu;
	wxBitmapButton m_bmt;
	wxBitmap* bmpt;
	wxImage* image;
	wxImage sourceImage;
	int changedirectoryclickevent = 0;
	int changedwindowsize = 0;
	void printBitmapButtons();
	//static methods for displaying data
	static void DisplayPic(wxPanel* parent, wxString path, wxPanel* display, wxFlexGridSizer* fgSizer);
	static void DisplayMetaData(wxGrid* EXIF, wxPanel* parent, wxPanel* display, wxString path);
	static void DisplayFolder(wxPanel* parent, wxPanel* display);
	//FreeImage
	void OnPanelClick(wxMouseEvent& event)
	{
		event.Skip();
	}
protected:

	void window_update(wxUpdateUIEvent& event);
	void LoadImgOnClick(wxCommandEvent& event);
	void WindowSizeChanged(wxSizeEvent& event);
	void scrollbar_scroll(wxScrollEvent& event);
};


class Panel2 : public wxPanel{
	friend class MyButton;
	friend class GUIMyFrame1;
	friend class MyCanvas;
	public:
		Panel2(wxPanel* parent, wxString path, wxPanel* display, wxFlexGridSizer* fgSizer, const wxSize& pos = wxDefaultSize):wxPanel(display, -1, wxPoint(0, 0),pos),_parent(parent),_path(path),_DisplayPanel(display),_fgSizer(fgSizer)
		{	
			Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(Panel2::OnPanelDoubleDown));
			wxClientDC dc(display);
			wxImage im = wxImage(path, wxBITMAP_TYPE_ANY, -1);
			im.Rescale(1200, 700, wxIMAGE_QUALITY_NEAREST);
			wxBitmap b1(im, -1);
			dc.DrawBitmap(b1, 0, 0);
		}
	private:
		wxPanel* _parent;
		wxString _path;
		wxPanel* _DisplayPanel;
		wxFlexGridSizer* _fgSizer;
		void OnPanelDoubleDown(wxMouseEvent& event)
		{
			GUIMyFrame1::DisplayFolder(_parent,_DisplayPanel);
			
		}
	
};

class MyButton : public wxBitmapButton
{
	friend class GUIMyFrame1;
	friend class Panel2;
public:

	MyButton(wxFlexGridSizer* fgSizer1, wxPanel* parent, wxPanel* displaypanel, wxGrid* EXIF, wxWindowID id, const wxBitmap& bitmap, const wxPoint& pos = wxDefaultPosition, wxString path_array = 'a') : wxBitmapButton(parent, -1, bitmap, pos)
	{
		Connect(wxEVT_LEFT_DOWN, wxMouseEventHandler(MyButton::OnMouseLeftDown));
		Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(MyButton::OnMouseDoubleDown));
		//Connect(wxEVT_LEFT_DCLICK, wxMouseEventHandler(MyButton::OnMouseLeftUp)); //need double-click action
		path = path_array;
		parent1 = parent;
		EXIF1 = EXIF;
		fgSizer = fgSizer1;
		DisplayPanel = displaypanel;
	}
private:
	wxString path;
	wxPanel* parent1;
	wxGrid* EXIF1;
	wxFlexGridSizer* fgSizer;
	wxPanel* DisplayPanel;
	void OnMouseLeftDown(wxMouseEvent& event)
	{
		GUIMyFrame1::DisplayMetaData(EXIF1, parent1, DisplayPanel, path);

	}

	void OnMouseDoubleDown(wxMouseEvent& event)
	{
		GUIMyFrame1::DisplayPic(parent1, path, DisplayPanel, fgSizer);
	}
};

class Scrolling : public wxScrolledWindow
{
	wxBitmap* bitmap;
	int w, h;
	Scrolling* m_peer;

public:
	Scrolling(wxWindow* parent, wxWindowID id, int width,int height) : wxScrolledWindow(parent, id)
	{
		m_peer = NULL;

		w = width;			//DO NOT DELETE!
		h = height;

		/* init scrolled area size, scrolling speed, etc. */
		SetScrollbars(1, 1, w, h, 0, 0);

		//bitmap = new wxBitmap(image);

		Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBTRACK, wxScrollWinEventHandler(Scrolling::onScroll), NULL, this);
		Connect(wxID_ANY, wxEVT_SCROLLWIN_THUMBRELEASE, wxScrollWinEventHandler(Scrolling::onScroll), NULL, this);
		Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEUP, wxScrollWinEventHandler(Scrolling::onScroll), NULL, this);
		Connect(wxID_ANY, wxEVT_SCROLLWIN_LINEDOWN, wxScrollWinEventHandler(Scrolling::onScroll), NULL, this);
	}
	~Scrolling()
	{
		//delete bitmap;
	}

	void SetPeer(Scrolling* other)
	{
		m_peer = other;
	}

	void onScroll(wxScrollWinEvent& evt)
	{
		if (m_peer != NULL)
		{
			m_peer->Scroll(GetScrollPos(wxHORIZONTAL), GetScrollPos(wxVERTICAL));
		}
		evt.Skip(); // let the event go
	}

	void OnDraw(wxDC& dc)
	{
		/* render the image - in a real app, if your scrolled area
		 is somewhat big, you will want to draw only visible parts,
		 not everything like below */
		//dc.DrawBitmap(*bitmap, 0, 0, false);

		// also check wxScrolledWindow::PrepareDC
	}
};



#endif // __GUIMyFrame1__
