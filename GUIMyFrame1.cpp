#include "GUIMyFrame1.h"

GUIMyFrame1::GUIMyFrame1( wxWindow* parent )
:
MyFrame1( parent )
{

}

void GUIMyFrame1::window_update( wxUpdateUIEvent& event )
{
repaint();
int panel_width = m_panel1->GetSize().GetWidth();
int panel_height = m_panel1->GetSize().GetHeight();
}

void GUIMyFrame1::scrollbar_scroll( wxScrollEvent& event )
{
// TODO: Implement scrollbar_scroll
}

void GUIMyFrame1::LoadImgOnClick( wxCommandEvent& event )
{
// TODO: Implement LoadImgOnClick
}


void GUIMyFrame1::repaint()
{
   wxClientDC dc(m_panel1);
   dc.SetBackground(wxColor(255, 255, 255));
}
