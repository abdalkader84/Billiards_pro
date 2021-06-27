//---------------------------------------------------------------------------
#include <fmx.h>
#pragma hdrstop
#include "main.h"
#include "math.h"
#include <mmsystem.h>
#include <system.Diagnostics.hpp>
#include <system.Threading.hpp>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
TForm1 *Form1;
int phs=0;
float f=7;
const float pi=3.141592;
float ms_x;
float l_x;
float spd_x;
bool l_clk=false;
bool r_clk=false;
unsigned long tim;
unsigned long target_tim;
float G= 0.17;
float ms_x1,ms_y1;
TPointF ps,pe,p1;
bool md;
int max_distance=25;
int com_id=0;
float F=0.99;
float Col_F=0.7;
float Rot_F=0.99;
bool  is_pull=false;
float shot=0;
//---------------------------------------------------------------------------
class TCppTask : public TCppInterfacedObject<TProc> {
public:
    void __fastcall Invoke() {
		//Sleep(3000);
		//ShowMessage("Hello");
		mciSendString(TEXT("play ball.wav"), NULL, SND_ASYNC | SND_FILENAME, NULL);
	}
};

void __fastcall TForm1::PlaySoundFile( )
{
   //if FileExists(FileName) then
	//sndPlaySound ( (FileName), 0, SND_ASYNC | SND_FILENAME);
	//mciSendString(TEXT("play C:\\WINDOWS\\Media\\onestop.mid"), NULL, 0, NULL);
	//mciSendString(TEXT("play D:\\Gun+Silencer.wav"), NULL, 0, NULL);
   _di_ITask task = TTask::Create(_di_TProc(new TCppTask()));
	task->Start();

	//	To stop the music:
	//mciSendString(TEXT("stop C:\\WINDOWS\\Media\\onestop.mid"), NULL, 0, NULL);

/* Flags are:
	SND_SYNC  =0 = Startlaying, and wait for the sound to finish
    SND_ASYNC =1 = Start playing, and don't wait to return
	SND_LOOP  =8 = Keep looping the sound until another sound is played  */
 }
__fastcall TForm1::TForm1(TComponent* Owner): TForm(Owner)
{
	srand(time(NULL));
}
void __fastcall TForm1::FormMouseMove(TObject *Sender, TShiftState Shift, float X, float Y)
{
	if (X>0) {
	  ms_x=X;
	}
	else
	{
	  ms_x=l_x;
	}
}
void __fastcall TForm1::r0MouseMove(TObject *Sender, TShiftState Shift, float X, float Y)
{
	if (md==true)
	{
		TPointF p2=((TBall *)Sender)->AbsoluteRect.CenterPoint();
		((TBall *)Sender)->Position->Point =((TRectangle *)Sender)->Position->Point-p1+PointF(X,Y);
		TPointF p3=((TBall *)Sender)->AbsoluteRect.CenterPoint();

		//-----------------------------------------------------
		if (((TBall *)Sender)->Position->X<((TBall *)Sender)->Width*0.5)
		{
			((TBall *)Sender)->Position->X=((TBall *)Sender)->Width*0.5;
		}
		if (((TBall *)Sender)->Position->Y<((TBall *)Sender)->Width*0.5)
		{
			((TBall *)Sender)->Position->Y=((TBall *)Sender)->Width*0.5;
		}
		if (((TBall *)Sender)->Position->Y >Lay_ide->Height- ((TBall *)Sender)->Height)
		{
			((TBall *)Sender)->Position->Y=Lay_ide->Height- ((TBall *)Sender)->Height- ((TBall *)Sender)->Height*0.5;
		}
		if (((TBall *)Sender)->Position->X >Lay_ide->Width- ((TBall *)Sender)->Width)
		{
			((TBall *)Sender)->Position->X=Lay_ide->Width- ((TBall *)Sender)->Width- ((TBall *)Sender)->Width*0.5;
		}
	}
}
void __fastcall TForm1::r0MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y)
{
	md=true;
	((TBall *)Sender)->AutoCapture=true;
    ((TBall *)Sender)->vic_amp=0;
	p1=PointF(X,Y);
	ps=PointF(X,Y)+b0->Position->Point;
}
void __fastcall TForm1::r0MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift, float X, float Y)
{
	md=false;
	((TBall *)Sender)->AutoCapture=false;
	pe=PointF(X,Y)+b0->Position->Point;
	//Circle1->vic_amp=pe.Distance(ps);
	//Circle1->vic_ang =pe.Angle (ps);
	if (Button==TMouseButton::mbRight)
	{
		//((TBall *)Sender)->vic_amp=5;
		//((TBall *)Sender)->vic_ang=ArcDial1->Value*pi/180;;
	}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::Reflect(TBall * b1,TBall * b2)
{
	for (int i=0; i<Lay_ide->Children->Count; i++) {
		TBall * r=(TBall *)Lay_ide->Children->Items[i];
		if (r==b1){continue;}
		if (r->Tag==54)
		{
			float xx=6;
			TPointF p1=b1->AbsoluteRect.CenterPoint();
			TPointF p2=r->AbsoluteRect.CenterPoint();
			float a1=p1.Angle (p2);
			float a2=p2.Angle (p1);

			if (r->vic_amp<0.1){r->vic_amp=0;}
			if (b1->vic_amp<0.1){b1->vic_amp=0;}
			if (p1.Distance(p2)< 25 && (b1->vic_amp>0 || r->vic_amp>0))
			{
				TPointF p3=PointF(cos(a2),sin(a2))*b1->vic_amp*Col_F;
				TPointF p4=PointF(cos(r->vic_ang),sin(r->vic_ang))*r->vic_amp*Col_F;
				TPointF p5=p3+p4;
				float amp=p5.Length();
				p5=p5.Normalize();

				r->vic_amp=amp;
				r->vic_ang=ArcTan2(p5.Y,p5.X);
				if (a2>0){r->rot=xx*r->vic_amp*b1->vic_amp;}
				if (a2<0){r->rot=-xx*r->vic_amp*b1->vic_amp;}
				if (a2==0){r->rot=0;}

				p3=PointF(cos(a1),sin(a1))*r->vic_amp*Col_F;
				p4=PointF(cos(b1->vic_ang),sin(b1->vic_ang))*b1->vic_amp*Col_F;
				p5=p3+p4;
				amp=p5.Length();
				p5=p5.Normalize();

				b1->vic_amp=amp;
				b1->vic_ang=ArcTan2(p5.Y,p5.X);
				if (a1>0){b1->rot=xx*b1->vic_amp*r->vic_amp;}
				if (a1<0){b1->rot=-xx*b1->vic_amp*r->vic_amp;}
				if (a1==0){b1->rot=0;}
				//MediaPlayer1->Play();
				//PlaySoundFile( );
			}
		}
        if (r->Tag==53)
		{
			TPointF p1=b1->AbsoluteRect.CenterPoint();
			TPointF p2=r->AbsoluteRect.CenterPoint();
			float a1=p1.Angle (p2);
			float a2=p2.Angle (p1);
            if (p1.Distance(p2)< 25 &&  b1->vic_amp>0 )
			{
				TPointF p3,p4,p5;
				p3=PointF(cos(a1),sin(a1))*b1->vic_amp*Col_F*2;
				p4=PointF(cos(b1->vic_ang),sin(b1->vic_ang))*b1->vic_amp*Col_F;
				p5=p3+p4;
				float amp=p5.Length();
				p5=p5.Normalize();

				b1->vic_amp=amp*Col_F;
				b1->vic_ang=ArcTan2(p5.Y,p5.X);
			}
		}
	}
}
void __fastcall TForm1::Timer3Timer(TObject *Sender)
{
	// new work
	Lay_ide->Canvas->BeginScene();
	is_pull=true;
	for (int i=0; i<Lay_ide->Children->Count; i++) {
		TBall * r=(TBall *)Lay_ide->Children->Items[i];
		if (r->Tag==54)
		{
			r->Position->Point=r->Position->Point+PointF(cos(r->vic_ang),sin(r->vic_ang))*r->vic_amp;
			r->vic_amp*=F;


			((TBall * )r->Children->Items[0])->RotationAngle+=r->rot;
			r->rot*=Rot_F;

			if (r->rot<0.1){r->rot=0;}


			if (r->AbsoluteRect.Intersects(h1->AbsoluteRect)==true ||
				r->AbsoluteRect.Intersects(h2->AbsoluteRect)==true ||
				r->AbsoluteRect.Intersects(h3->AbsoluteRect)==true ||
				r->AbsoluteRect.Intersects(h4->AbsoluteRect)==true  )
			{
				TPointF p=PointF(cos(r->vic_ang),sin(r->vic_ang));
				p.Y=-p.Y;
				r->vic_ang=ArcTan2(p.Y,p.X);
				if ( r->Position->Y<=h1->Position->Y+h1->Height )
				{
					r->Position->Y=h1->Position->Y+h1->Height+0.01;
				}
				if ( r->Position->Y>=h3->Position->Y-r->Height)
				{
					r->Position->Y=h3->Position->Y-r->Height-0.01;
				}
			}
			if (r->AbsoluteRect.Intersects(h5->AbsoluteRect)==true ||
				r->AbsoluteRect.Intersects(h6->AbsoluteRect)==true )
			{
				TPointF p=PointF(cos(r->vic_ang),sin(r->vic_ang));
				p.X=-p.X;
				r->vic_ang=ArcTan2(p.Y,p.X);
				if ( r->Position->X<=h5->Position->X+h5->Width )
				{
					r->Position->X=h5->Position->X+h5->Width+0.01;
				}
				if ( r->Position->X>=h6->Position->X-r->Width)
				{
					r->Position->X=h6->Position->X-r->Width-0.01;
				}
			}

			Reflect(r,NULL);
			if (r->vic_amp>0){is_pull=false;}
			if (t1->AbsoluteRect.Contains(r->AbsoluteRect.CenterPoint())==true ||
				t2->AbsoluteRect.Contains(r->AbsoluteRect.CenterPoint())==true ||
				t3->AbsoluteRect.Contains(r->AbsoluteRect.CenterPoint())==true ||
				t4->AbsoluteRect.Contains(r->AbsoluteRect.CenterPoint())==true ||
				t5->AbsoluteRect.Contains(r->AbsoluteRect.CenterPoint())==true ||
				t6->AbsoluteRect.Contains(r->AbsoluteRect.CenterPoint())==true  )
				{
					if (r==b0) {
                        r->vic_amp=0;
						r->Position->Point=PointF(144,144);
						continue;
					}
					Lay_ide->RemoveObject(r);
                    r->DisposeOf();
				}

		}

	}
	if (is_pull==true)
	{
		((TCircle * )b0->Children->Items[1])->Visible=true;
		((TRectangle *)  ((TCircle * )b0->Children->Items[1])->Children->Items[0])->Position->X-=0.5;
		if (((TRectangle *)  ((TCircle * )b0->Children->Items[1])->Children->Items[0])->Position->X<-400)
		{
			((TRectangle *)  ((TCircle * )b0->Children->Items[1])->Children->Items[0])->Position->X=-240;
			Form1->Caption=((TRectangle *)  ((TCircle * )b0->Children->Items[1])->Children->Items[0])->Position->X;
		}
	}
	else
	{
		((TCircle * )b0->Children->Items[1])->Visible=false;
	}
	Lay_ide->Repaint();
	Rectangle1->Repaint();
    Lay_main->Repaint();
    Lay_ide->Canvas->EndScene();
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
void __fastcall TForm1::b0Paint(TObject *Sender, TCanvas *Canvas, const TRectF &ARect)
{
 	((TBall *) Sender)->Canvas->BeginScene();
	TStrokeBrush * st=new TStrokeBrush(TBrushKind::Solid,TAlphaColors().Green);
	st->Thickness=2;
	float a = ((TBall *) Sender) ->vic_ang ;
	((TBall *) Sender)->Canvas->DrawLine(((TBall *) Sender)->LocalRect.CenterPoint(),PointF(cos(a),sin(a))*(((TBall *) Sender)->vic_amp*3)+((TBall *) Sender)->LocalRect.CenterPoint(),1,st);
	((TBall *) Sender)->Canvas->EndScene();
	st->Free();
}
void __fastcall TForm1::Lay_ideMouseMove(TObject *Sender, TShiftState Shift, float X, float Y)
{
	if (is_pull==true && Shift!=TShiftState()>>ssShift)
	{
		b0->BringToFront();
		TPointF p1=b0->Position->Point+Point(b0->Width*0.5,b0->Height*0.5) ;
		TPointF p2=PointF(X,Y);
		((TCircle * ) b0->Children->Items[1])->RotationAngle=p2.Angle(p1)*180/pi ;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Lay_ideMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y)
{
	if (is_pull==true  && Button==TMouseButton::mbRight)
	{
		((TBall *)	b0)->vic_ang=((TCircle * ) b0->Children->Items[1])->RotationAngle*pi/180;
		shot=abs(((TRectangle *)  ((TCircle * )b0->Children->Items[1])->Children->Items[0])->Position->X)-240;
		((TBall *)	b0)->vic_amp=1+shot*20/(400-240);
		//((TBall *)	b0)->vic_amp=5;
	}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::create_Ball(unsigned int clr,TPointF p,int style)
{
	TBall * r=NULL;
	r=(TBall *) b0->Clone(Lay_ide);
	r->Position->Point=p;
	r->Tag=style;
	r->Visible=true;
	r->Parent=Lay_ide;
    r->HitTest=false;
	/*
	r->OnMouseDown=r0MouseDown;
	r->OnMouseMove=r0MouseMove;
	r->OnMouseUp=r0MouseUp;
    */
	r->OnPaint=b0Paint;
	r->vic_ang=0;
	r->vic_amp=0;
	r->rot=0;
    r->HitTest=false;
	r->Name="r"+IntToStr(com_id++);
	r->Fill->Color= clr;
	if (clr==TAlphaColors().Black)
    {r->Stroke->Color=TAlphaColors().Gray;}
	((TBall * )r->Children->Items[1])->Visible=false;
	Lay_ide->AddObject(r);
}
void __fastcall TForm1::initial()
{
	((TBall *)	b0)->vic_amp=0;
	((TBall *)	b0)->rot=0;
	create_Ball(TAlphaColors().Yellow,PointF(370,144),54);

	create_Ball(TAlphaColors().Blue,PointF(392,131),54);
	create_Ball(TAlphaColors().Red,PointF(392,157),54);

	create_Ball(TAlphaColors().Magenta,PointF(414,119),54);
	create_Ball(TAlphaColors().Orange,PointF(414,145),54);
	create_Ball(TAlphaColors().Limegreen,PointF(414,170),54);

	create_Ball(TAlphaColors().Brown,PointF(437,106),54);
	create_Ball(TAlphaColors().Black,PointF(437,132),54);
	create_Ball(TAlphaColors().Yellow,PointF(437,159),54);
	create_Ball(TAlphaColors().Blue,PointF(437,184),54);

	create_Ball(TAlphaColors().Red,PointF(460,94),54);
	create_Ball(TAlphaColors().Magenta,PointF(460,120),54);
	create_Ball(TAlphaColors().Orange,PointF(460,145),54);
	create_Ball(TAlphaColors().Limegreen,PointF(460,170),54);
	create_Ball(TAlphaColors().Brown,PointF(460,196),54);

}
void __fastcall TForm1::FormCreate(TObject *Sender)
{
	initial();

}
//---------------------------------------------------------------------------
