# -*- coding: utf-8 -*- 

###########################################################################
## Python code generated with wxFormBuilder (version Jun 17 2015)
## http://www.wxformbuilder.org/
##
## PLEASE DO "NOT" EDIT THIS FILE!
###########################################################################

import wx
import wx.xrc

wx.ID_TIMER1 = 1000
wx.ID_TIMER2 = 1001
wx.ID_TIMER3 = 1002
wx.ID_TIMER4 = 1003
wx.ID_TIMER5 = 1004

###########################################################################
## Class MainFrame
###########################################################################

class MainFrame ( wx.Frame ):
	
	def __init__( self, parent ):
		wx.Frame.__init__ ( self, parent, id = wx.ID_ANY, title = u"Lab. Sólidos Amorfos - Control Horno GH", pos = wx.DefaultPosition, size = wx.Size( 838,478 ), style = wx.DEFAULT_FRAME_STYLE )
		
		self.SetSizeHintsSz( wx.DefaultSize, wx.DefaultSize )
		
		bSizer14 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_notebook2 = wx.Notebook( self, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_notebook2.SetFont( wx.Font( 10, 74, 90, 90, False, "Arial" ) )
		self.m_notebook2.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BTNHIGHLIGHT ) )
		
		self.m_panel6 = wx.Panel( self.m_notebook2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer7 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer12 = wx.GridSizer( 0, 2, 0, 0 )
		
		self.m_panel81 = wx.Panel( self.m_panel6, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel81.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INFOBK ) )
		
		bSizer11 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer5 = wx.GridSizer( 0, 3, 0, 0 )
		
		self.m_staticText49 = wx.StaticText( self.m_panel81, wx.ID_ANY, u"Hora último \ndato leído:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText49.Wrap( -1 )
		self.m_staticText49.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BTNTEXT ) )
		
		gSizer5.Add( self.m_staticText49, 0, wx.ALL, 5 )
		
		self.m_staticText63 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText63.Wrap( -1 )
		gSizer5.Add( self.m_staticText63, 0, wx.ALL, 5 )
		
		self.m_staticText651 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText651.Wrap( -1 )
		gSizer5.Add( self.m_staticText651, 0, wx.ALL, 5 )
		
		self.m_staticText27 = wx.StaticText( self.m_panel81, wx.ID_ANY, u"Temperatura \nTermocupla:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText27.Wrap( -1 )
		self.m_staticText27.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BACKGROUND ) )
		
		gSizer5.Add( self.m_staticText27, 0, wx.ALL, 5 )
		
		self.m_staticText64 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText64.Wrap( -1 )
		gSizer5.Add( self.m_staticText64, 0, wx.ALL, 5 )
		
		self.m_staticText681 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText681.Wrap( -1 )
		gSizer5.Add( self.m_staticText681, 0, wx.ALL, 5 )
		
		self.m_staticText29 = wx.StaticText( self.m_panel81, wx.ID_ANY, u"Temperatura \nJuntura Fría:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText29.Wrap( -1 )
		self.m_staticText29.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BACKGROUND ) )
		
		gSizer5.Add( self.m_staticText29, 0, wx.ALL, 5 )
		
		self.m_staticText65 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText65.Wrap( -1 )
		gSizer5.Add( self.m_staticText65, 0, wx.ALL, 5 )
		
		self.m_staticText691 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText691.Wrap( -1 )
		gSizer5.Add( self.m_staticText691, 0, wx.ALL, 5 )
		
		self.m_staticText47 = wx.StaticText( self.m_panel81, wx.ID_ANY, u"Potencia:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText47.Wrap( -1 )
		self.m_staticText47.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BTNTEXT ) )
		
		gSizer5.Add( self.m_staticText47, 0, wx.ALL, 5 )
		
		self.m_staticText66 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText66.Wrap( -1 )
		gSizer5.Add( self.m_staticText66, 0, wx.ALL, 5 )
		
		self.m_staticText701 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText701.Wrap( -1 )
		gSizer5.Add( self.m_staticText701, 0, wx.ALL, 5 )
		
		self.m_staticText67 = wx.StaticText( self.m_panel81, wx.ID_ANY, u"Auto\nSintonía:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText67.Wrap( -1 )
		gSizer5.Add( self.m_staticText67, 0, wx.ALL, 5 )
		
		self.m_staticText68 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText68.Wrap( -1 )
		gSizer5.Add( self.m_staticText68, 0, wx.ALL, 5 )
		
		self.m_staticText711 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText711.Wrap( -1 )
		gSizer5.Add( self.m_staticText711, 0, wx.ALL, 5 )
		
		self.m_staticText69 = wx.StaticText( self.m_panel81, wx.ID_ANY, u"Control\nAutomático:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText69.Wrap( -1 )
		gSizer5.Add( self.m_staticText69, 0, wx.ALL, 5 )
		
		self.m_staticText70 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText70.Wrap( -1 )
		gSizer5.Add( self.m_staticText70, 0, wx.ALL, 5 )
		
		self.m_staticText721 = wx.StaticText( self.m_panel81, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText721.Wrap( -1 )
		gSizer5.Add( self.m_staticText721, 0, wx.ALL, 5 )
		
		
		bSizer11.Add( gSizer5, 1, wx.ALL|wx.EXPAND, 5 )
		
		
		self.m_panel81.SetSizer( bSizer11 )
		self.m_panel81.Layout()
		bSizer11.Fit( self.m_panel81 )
		gSizer12.Add( self.m_panel81, 1, wx.EXPAND |wx.ALL, 5 )
		
		self.m_panel7 = wx.Panel( self.m_panel6, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel7.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INFOBK ) )
		
		bSizer10 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer15 = wx.GridSizer( 0, 3, 0, 0 )
		
		self.m_staticText791 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Tipo de Termocupla: ", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText791.Wrap( -1 )
		gSizer15.Add( self.m_staticText791, 0, wx.ALL, 5 )
		
		m_choice5Choices = [ u"Tipo B", u"Tipo E", u"Tipo J", u"Tipo K", u"Tipo N", u"Tipo R", u"Tipo S", u"Tipo T" ]
		self.m_choice5 = wx.Choice( self.m_panel7, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, m_choice5Choices, 0 )
		self.m_choice5.SetSelection( 0 )
		gSizer15.Add( self.m_choice5, 0, wx.ALL, 5 )
		
		self.m_staticText811 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText811.Wrap( -1 )
		gSizer15.Add( self.m_staticText811, 0, wx.ALL, 5 )
		
		self.m_staticText951 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Comando del Horno:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText951.Wrap( -1 )
		gSizer15.Add( self.m_staticText951, 0, wx.ALL, 5 )
		
		m_choice8Choices = [ u"CONTROL MANUAL", u"CONTROL AUTOMATICO" ]
		self.m_choice8 = wx.Choice( self.m_panel7, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, m_choice8Choices, 0 )
		self.m_choice8.SetSelection( 0 )
		gSizer15.Add( self.m_choice8, 0, wx.ALL, 5 )
		
		self.m_staticText96 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText96.Wrap( -1 )
		gSizer15.Add( self.m_staticText96, 0, wx.ALL, 5 )
		
		self.m_staticText71 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Temperatura Límite:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText71.Wrap( -1 )
		gSizer15.Add( self.m_staticText71, 0, wx.ALL, 5 )
		
		self.m_staticText72 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText72.Wrap( -1 )
		gSizer15.Add( self.m_staticText72, 0, wx.ALL, 5 )
		
		self.m_staticText731 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText731.Wrap( -1 )
		gSizer15.Add( self.m_staticText731, 0, wx.ALL, 5 )
		
		self.m_staticText75 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Estado:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText75.Wrap( -1 )
		gSizer15.Add( self.m_staticText75, 0, wx.ALL, 5 )
		
		self.m_staticText74 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText74.Wrap( -1 )
		gSizer15.Add( self.m_staticText74, 0, wx.ALL, 5 )
		
		self.m_staticText741 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText741.Wrap( -1 )
		gSizer15.Add( self.m_staticText741, 0, wx.ALL, 5 )
		
		self.m_staticText73 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Operando en Modo:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText73.Wrap( -1 )
		gSizer15.Add( self.m_staticText73, 0, wx.ALL, 5 )
		
		self.m_staticText76 = wx.StaticText( self.m_panel7, wx.ID_ANY, u"Manual", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText76.Wrap( -1 )
		gSizer15.Add( self.m_staticText76, 0, wx.ALL, 5 )
		
		self.m_staticText751 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText751.Wrap( -1 )
		gSizer15.Add( self.m_staticText751, 0, wx.ALL, 5 )
		
		self.m_bpButton1 = wx.BitmapButton( self.m_panel7, wx.ID_ANY, wx.Bitmap( u"stop.png", wx.BITMAP_TYPE_ANY ), wx.Point( 100,100 ), wx.Size( 100,100 ), wx.BU_AUTODRAW )
		gSizer15.Add( self.m_bpButton1, 0, wx.ALL, 5 )
		
		self.m_staticText692 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText692.Wrap( -1 )
		gSizer15.Add( self.m_staticText692, 0, wx.ALL, 5 )
		
		self.m_staticText82 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText82.Wrap( -1 )
		gSizer15.Add( self.m_staticText82, 0, wx.ALL, 5 )
		
		self.m_staticText83 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText83.Wrap( -1 )
		gSizer15.Add( self.m_staticText83, 0, wx.ALL, 5 )
		
		self.m_staticText841 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText841.Wrap( -1 )
		gSizer15.Add( self.m_staticText841, 0, wx.ALL, 5 )
		
		self.m_staticText85 = wx.StaticText( self.m_panel7, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText85.Wrap( -1 )
		gSizer15.Add( self.m_staticText85, 0, wx.ALL, 5 )
		
		
		bSizer10.Add( gSizer15, 1, wx.EXPAND, 5 )
		
		
		self.m_panel7.SetSizer( bSizer10 )
		self.m_panel7.Layout()
		bSizer10.Fit( self.m_panel7 )
		gSizer12.Add( self.m_panel7, 1, wx.EXPAND |wx.ALL, 5 )
		
		
		bSizer7.Add( gSizer12, 1, wx.EXPAND, 5 )
		
		
		self.m_panel6.SetSizer( bSizer7 )
		self.m_panel6.Layout()
		bSizer7.Fit( self.m_panel6 )
		self.m_notebook2.AddPage( self.m_panel6, u"General", True )
		self.m_panel8 = wx.Panel( self.m_notebook2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel8.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOW ) )
		self.m_panel8.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_WINDOW ) )
		
		bSizer15 = wx.BoxSizer( wx.VERTICAL )
		
		self.m_staticText24 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"Com. USB:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText24.Wrap( -1 )
		self.m_staticText24.SetFont( wx.Font( 10, 74, 90, 90, False, "Arial" ) )
		self.m_staticText24.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_CAPTIONTEXT ) )
		
		bSizer15.Add( self.m_staticText24, 0, wx.ALL, 5 )
		
		self.m_staticText25 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"Com. Termocupla:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText25.Wrap( -1 )
		self.m_staticText25.SetFont( wx.Font( 10, 74, 90, 90, False, "Arial" ) )
		self.m_staticText25.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BACKGROUND ) )
		
		bSizer15.Add( self.m_staticText25, 0, wx.ALL, 5 )
		
		self.m_staticText26 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"Com. Potenciómetro:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText26.Wrap( -1 )
		self.m_staticText26.SetFont( wx.Font( 10, 74, 90, 90, False, "Arial" ) )
		self.m_staticText26.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BACKGROUND ) )
		
		bSizer15.Add( self.m_staticText26, 0, wx.ALL, 5 )
		
		self.m_staticText17 = wx.StaticText( self.m_panel8, wx.ID_ANY, u"Detección de Fallas:", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText17.Wrap( -1 )
		self.m_staticText17.SetFont( wx.Font( 15, 70, 90, 90, True, wx.EmptyString ) )
		self.m_staticText17.SetForegroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_HIGHLIGHT ) )
		self.m_staticText17.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_BTNHIGHLIGHT ) )
		
		bSizer15.Add( self.m_staticText17, 0, wx.ALL, 5 )
		
		self.m_listCtrl1 = wx.ListCtrl( self.m_panel8, wx.ID_ANY, wx.DefaultPosition, wx.Size( -1,300 ), wx.LC_REPORT )
		self.m_listCtrl1.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial" ) )
		self.m_listCtrl1.SetBackgroundColour( wx.SystemSettings.GetColour( wx.SYS_COLOUR_INFOBK ) )
		
		bSizer15.Add( self.m_listCtrl1, 0, wx.ALL|wx.EXPAND, 5 )
		
		
		self.m_panel8.SetSizer( bSizer15 )
		self.m_panel8.Layout()
		bSizer15.Fit( self.m_panel8 )
		self.m_notebook2.AddPage( self.m_panel8, u"Estado del equipo", False )
		self.m_panel5 = wx.Panel( self.m_notebook2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		self.m_panel5.SetFont( wx.Font( 10, 74, 90, 90, False, "Arial" ) )
		
		bSizer5 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer8 = wx.GridSizer( 0, 2, 0, 0 )
		
		gSizer61 = wx.GridSizer( 0, 2, 0, 0 )
		
		self.m_staticText114 = wx.StaticText( self.m_panel5, wx.ID_ANY, u"Control Automático", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText114.Wrap( -1 )
		self.m_staticText114.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial Rounded MT Bold" ) )
		
		gSizer61.Add( self.m_staticText114, 0, wx.ALL, 5 )
		
		self.m_staticText115 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText115.Wrap( -1 )
		gSizer61.Add( self.m_staticText115, 0, wx.ALL, 5 )
		
		self.m_staticText38 = wx.StaticText( self.m_panel5, wx.ID_ANY, u"Temp. Objetivo", wx.DefaultPosition, wx.DefaultSize, wx.ALIGN_CENTRE )
		self.m_staticText38.Wrap( -1 )
		self.m_staticText38.SetFont( wx.Font( 10, 74, 90, 90, False, "Arial" ) )
		
		gSizer61.Add( self.m_staticText38, 0, wx.ALL, 5 )
		
		self.m_textCtrl12 = wx.TextCtrl( self.m_panel5, wx.ID_ANY, u"950ºC", wx.DefaultPosition, wx.DefaultSize, wx.TE_RIGHT )
		gSizer61.Add( self.m_textCtrl12, 0, wx.ALL, 5 )
		
		self.m_radioBtn1 = wx.RadioButton( self.m_panel5, wx.ID_ANY, u"Calentamiento Lento \n\n(100% hasta objetivo)", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer61.Add( self.m_radioBtn1, 0, wx.ALL, 5 )
		
		self.m_staticText125 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText125.Wrap( -1 )
		gSizer61.Add( self.m_staticText125, 0, wx.ALL, 5 )
		
		self.m_radioBtn2 = wx.RadioButton( self.m_panel5, wx.ID_ANY, u"Calentamiento Rápido (Calibración previa + Control)", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer61.Add( self.m_radioBtn2, 0, wx.ALL, 5 )
		
		self.m_staticText126 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText126.Wrap( -1 )
		gSizer61.Add( self.m_staticText126, 0, wx.ALL, 5 )
		
		self.m_button7 = wx.Button( self.m_panel5, wx.ID_ANY, u"Activar", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer61.Add( self.m_button7, 0, wx.ALL, 5 )
		
		self.m_button8 = wx.Button( self.m_panel5, wx.ID_ANY, u"Desactivar", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer61.Add( self.m_button8, 0, wx.ALL, 5 )
		
		self.m_staticText37 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText37.Wrap( -1 )
		self.m_staticText37.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial Rounded MT Bold" ) )
		
		gSizer61.Add( self.m_staticText37, 0, wx.ALL, 5 )
		
		
		gSizer8.Add( gSizer61, 1, wx.ALL|wx.EXPAND, 5 )
		
		gSizer151 = wx.GridSizer( 7, 2, 0, 0 )
		
		self.m_staticText702 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText702.Wrap( -1 )
		gSizer151.Add( self.m_staticText702, 0, wx.ALL, 5 )
		
		self.m_staticText712 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText712.Wrap( -1 )
		gSizer151.Add( self.m_staticText712, 0, wx.ALL, 5 )
		
		self.m_staticText122 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText122.Wrap( -1 )
		gSizer151.Add( self.m_staticText122, 0, wx.ALL, 5 )
		
		self.m_staticText123 = wx.StaticText( self.m_panel5, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText123.Wrap( -1 )
		gSizer151.Add( self.m_staticText123, 0, wx.ALL, 5 )
		
		
		gSizer8.Add( gSizer151, 1, wx.EXPAND, 5 )
		
		
		bSizer5.Add( gSizer8, 1, wx.EXPAND, 5 )
		
		
		self.m_panel5.SetSizer( bSizer5 )
		self.m_panel5.Layout()
		bSizer5.Fit( self.m_panel5 )
		self.m_notebook2.AddPage( self.m_panel5, u"Control Automático", False )
		self.m_panel4 = wx.Panel( self.m_notebook2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer51 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer81 = wx.GridSizer( 0, 0, 0, 0 )
		
		gSizer16 = wx.GridSizer( 6, 3, 0, 0 )
		
		self.m_staticText102 = wx.StaticText( self.m_panel4, wx.ID_ANY, u"Cambio de Potencia Manual", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText102.Wrap( -1 )
		self.m_staticText102.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial Rounded MT Bold" ) )
		
		gSizer16.Add( self.m_staticText102, 0, wx.ALL, 5 )
		
		self.m_staticText103 = wx.StaticText( self.m_panel4, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText103.Wrap( -1 )
		gSizer16.Add( self.m_staticText103, 0, wx.ALL, 5 )
		
		self.m_staticText113 = wx.StaticText( self.m_panel4, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText113.Wrap( -1 )
		gSizer16.Add( self.m_staticText113, 0, wx.ALL, 5 )
		
		self.m_staticText106 = wx.StaticText( self.m_panel4, wx.ID_ANY, u"Cambia la potencia del horno \nsin ningún tipo de control\n", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText106.Wrap( -1 )
		gSizer16.Add( self.m_staticText106, 0, wx.ALL, 5 )
		
		self.m_staticText105 = wx.StaticText( self.m_panel4, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText105.Wrap( -1 )
		gSizer16.Add( self.m_staticText105, 0, wx.ALL, 5 )
		
		self.m_staticText104 = wx.StaticText( self.m_panel4, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText104.Wrap( -1 )
		gSizer16.Add( self.m_staticText104, 0, wx.ALL, 5 )
		
		self.m_staticText32 = wx.StaticText( self.m_panel4, wx.ID_ANY, u"Potencia", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText32.Wrap( -1 )
		gSizer16.Add( self.m_staticText32, 0, wx.ALL, 5 )
		
		self.m_textCtrl14 = wx.TextCtrl( self.m_panel4, wx.ID_ANY, u"10%", wx.DefaultPosition, wx.DefaultSize, wx.TE_RIGHT )
		gSizer16.Add( self.m_textCtrl14, 0, wx.ALL, 5 )
		
		self.m_button51 = wx.Button( self.m_panel4, wx.ID_ANY, u"Modificar", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer16.Add( self.m_button51, 0, wx.ALL, 5 )
		
		
		gSizer81.Add( gSizer16, 1, wx.EXPAND, 5 )
		
		gSizer171 = wx.GridSizer( 0, 2, 0, 0 )
		
		
		gSizer81.Add( gSizer171, 1, wx.EXPAND, 5 )
		
		
		bSizer51.Add( gSizer81, 1, wx.EXPAND, 5 )
		
		
		self.m_panel4.SetSizer( bSizer51 )
		self.m_panel4.Layout()
		bSizer51.Fit( self.m_panel4 )
		self.m_notebook2.AddPage( self.m_panel4, u"Potencia Manual", False )
		self.m_panel51 = wx.Panel( self.m_notebook2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer6 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer11 = wx.GridSizer( 0, 2, 0, 0 )
		
		gSizer9 = wx.GridSizer( 0, 2, 0, 0 )
		
		self.m_staticText97 = wx.StaticText( self.m_panel51, wx.ID_ANY, u"Parámetros de Auto-Sintonía", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText97.Wrap( -1 )
		self.m_staticText97.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial Rounded MT Bold" ) )
		
		gSizer9.Add( self.m_staticText97, 0, wx.ALL, 5 )
		
		self.m_staticText98 = wx.StaticText( self.m_panel51, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText98.Wrap( -1 )
		gSizer9.Add( self.m_staticText98, 0, wx.ALL, 5 )
		
		self.m_staticText521 = wx.StaticText( self.m_panel51, wx.ID_ANY, u"Temperatura \nde Corte", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText521.Wrap( -1 )
		gSizer9.Add( self.m_staticText521, 0, wx.ALL, 5 )
		
		self.m_textCtrl171 = wx.TextCtrl( self.m_panel51, wx.ID_ANY, u"1300ºC", wx.DefaultPosition, wx.DefaultSize, wx.TE_RIGHT )
		gSizer9.Add( self.m_textCtrl171, 0, wx.ALL, 5 )
		
		self.m_staticText53 = wx.StaticText( self.m_panel51, wx.ID_ANY, u"Potencia\nEstacionaria", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText53.Wrap( -1 )
		gSizer9.Add( self.m_staticText53, 0, wx.ALL, 5 )
		
		self.m_textCtrl18 = wx.TextCtrl( self.m_panel51, wx.ID_ANY, u"60%", wx.DefaultPosition, wx.DefaultSize, wx.TE_RIGHT )
		gSizer9.Add( self.m_textCtrl18, 0, wx.ALL, 5 )
		
		self.m_button81 = wx.Button( self.m_panel51, wx.ID_ANY, u"Activar", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer9.Add( self.m_button81, 0, wx.ALL, 5 )
		
		self.m_button91 = wx.Button( self.m_panel51, wx.ID_ANY, u"Desactivar", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer9.Add( self.m_button91, 0, wx.ALL, 5 )
		
		self.m_staticText371 = wx.StaticText( self.m_panel51, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText371.Wrap( -1 )
		self.m_staticText371.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial Rounded MT Bold" ) )
		
		gSizer9.Add( self.m_staticText371, 0, wx.ALL, 5 )
		
		
		gSizer11.Add( gSizer9, 1, wx.EXPAND, 5 )
		
		gSizer10 = wx.GridSizer( 10, 1, 0, 0 )
		
		self.m_bitmap2 = wx.StaticBitmap( self.m_panel51, wx.ID_ANY, wx.Bitmap( u"app_1.png", wx.BITMAP_TYPE_ANY ), wx.DefaultPosition, wx.Size( 400,200 ), 0 )
		gSizer10.Add( self.m_bitmap2, 0, wx.ALIGN_CENTER_HORIZONTAL|wx.ALL, 5 )
		
		
		gSizer11.Add( gSizer10, 1, wx.EXPAND, 5 )
		
		
		bSizer6.Add( gSizer11, 1, wx.EXPAND, 5 )
		
		
		self.m_panel51.SetSizer( bSizer6 )
		self.m_panel51.Layout()
		bSizer6.Fit( self.m_panel51 )
		self.m_notebook2.AddPage( self.m_panel51, u"Auto-Sintonía", False )
		self.m_panel91 = wx.Panel( self.m_notebook2, wx.ID_ANY, wx.DefaultPosition, wx.DefaultSize, wx.TAB_TRAVERSAL )
		bSizer12 = wx.BoxSizer( wx.VERTICAL )
		
		gSizer17 = wx.GridSizer( 0, 2, 0, 0 )
		
		gSizer18 = wx.GridSizer( 6, 2, 0, 0 )
		
		self.m_staticText99 = wx.StaticText( self.m_panel91, wx.ID_ANY, u"Iniciar Gráfico y Adquisición", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText99.Wrap( -1 )
		self.m_staticText99.SetFont( wx.Font( 11, 74, 90, 90, False, "Arial Rounded MT Bold" ) )
		
		gSizer18.Add( self.m_staticText99, 0, wx.ALL, 5 )
		
		self.m_staticText100 = wx.StaticText( self.m_panel91, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText100.Wrap( -1 )
		gSizer18.Add( self.m_staticText100, 0, wx.ALL, 5 )
		
		self.m_staticText107 = wx.StaticText( self.m_panel91, wx.ID_ANY, u"Presione la tecla iniciar para que se inicie el gráfico\ninteractivo y los datos de adquisición se guarden en el \narchivo CSV.", wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText107.Wrap( -1 )
		gSizer18.Add( self.m_staticText107, 0, wx.ALL, 5 )
		
		self.m_staticText111 = wx.StaticText( self.m_panel91, wx.ID_ANY, wx.EmptyString, wx.DefaultPosition, wx.DefaultSize, 0 )
		self.m_staticText111.Wrap( -1 )
		gSizer18.Add( self.m_staticText111, 0, wx.ALL, 5 )
		
		self.m_button101 = wx.Button( self.m_panel91, wx.ID_ANY, u"Iniciar", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer18.Add( self.m_button101, 0, wx.ALL, 5 )
		
		self.m_button11 = wx.Button( self.m_panel91, wx.ID_ANY, u"Detener", wx.DefaultPosition, wx.DefaultSize, 0 )
		gSizer18.Add( self.m_button11, 0, wx.ALL, 5 )
		
		
		gSizer17.Add( gSizer18, 1, wx.ALL|wx.EXPAND, 5 )
		
		
		bSizer12.Add( gSizer17, 1, wx.EXPAND, 5 )
		
		
		self.m_panel91.SetSizer( bSizer12 )
		self.m_panel91.Layout()
		bSizer12.Fit( self.m_panel91 )
		self.m_notebook2.AddPage( self.m_panel91, u"Gráfico y Adquisición", False )
		
		bSizer14.Add( self.m_notebook2, 1, wx.EXPAND, 5 )
		
		
		self.SetSizer( bSizer14 )
		self.Layout()
		self.m_timer1 = wx.Timer()
		self.m_timer1.SetOwner( self, wx.ID_TIMER1 )
		self.m_timer1.Start( 2000 )
		
		self.m_timer2 = wx.Timer()
		self.m_timer2.SetOwner( self, wx.ID_TIMER2 )
		self.m_timer3 = wx.Timer()
		self.m_timer3.SetOwner( self, wx.ID_TIMER3 )
		self.m_timer4 = wx.Timer()
		self.m_timer4.SetOwner( self, wx.ID_TIMER4 )
		self.m_timer5 = wx.Timer()
		self.m_timer5.SetOwner( self, wx.ID_TIMER5 )
		
		self.Centre( wx.BOTH )
		
		# Connect Events
		self.Bind( wx.EVT_CLOSE, self.OnClose )
		self.m_choice5.Bind( wx.EVT_CHOICE, self.selectTermRange )
		self.m_choice8.Bind( wx.EVT_CHOICE, self.changeCommandPower )
		self.m_bpButton1.Bind( wx.EVT_BUTTON, self.emergencyStop )
		self.m_button7.Bind( wx.EVT_BUTTON, self.sendControlParams )
		self.m_button8.Bind( wx.EVT_BUTTON, self.cancelControl )
		self.m_button51.Bind( wx.EVT_BUTTON, self.sendPotValue )
		self.m_button81.Bind( wx.EVT_BUTTON, self.sendCalibrationParams )
		self.m_button91.Bind( wx.EVT_BUTTON, self.cancelCalibration )
		self.m_button101.Bind( wx.EVT_BUTTON, self.startCapture )
		self.m_button11.Bind( wx.EVT_BUTTON, self.stopCapture )
		self.Bind( wx.EVT_TIMER, self.checkSerialStatus, id=wx.ID_TIMER1 )
		self.Bind( wx.EVT_TIMER, self.readCharUSB, id=wx.ID_TIMER2 )
		self.Bind( wx.EVT_TIMER, self.setInitialConfig, id=wx.ID_TIMER3 )
		self.Bind( wx.EVT_TIMER, self.clearListFault, id=wx.ID_TIMER4 )
		self.Bind( wx.EVT_TIMER, self.autoConversionOn, id=wx.ID_TIMER5 )
	
	def __del__( self ):
		pass
	
	
	# Virtual event handlers, overide them in your derived class
	def OnClose( self, event ):
		event.Skip()
	
	def selectTermRange( self, event ):
		event.Skip()
	
	def changeCommandPower( self, event ):
		event.Skip()
	
	def emergencyStop( self, event ):
		event.Skip()
	
	def sendControlParams( self, event ):
		event.Skip()
	
	def cancelControl( self, event ):
		event.Skip()
	
	def sendPotValue( self, event ):
		event.Skip()
	
	def sendCalibrationParams( self, event ):
		event.Skip()
	
	def cancelCalibration( self, event ):
		event.Skip()
	
	def startCapture( self, event ):
		event.Skip()
	
	def stopCapture( self, event ):
		event.Skip()
	
	def checkSerialStatus( self, event ):
		event.Skip()
	
	def readCharUSB( self, event ):
		event.Skip()
	
	def setInitialConfig( self, event ):
		event.Skip()
	
	def clearListFault( self, event ):
		event.Skip()
	
	def autoConversionOn( self, event ):
		event.Skip()
	

