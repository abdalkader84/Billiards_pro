//---------------------------------------------------------------------------

#ifndef mainH
#define mainH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.Objects.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Layouts.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Effects.hpp>
#include <FMX.Media.hpp>
//---------------------------------------------------------------------------
class TBall : public TCircle
{
	public:
		void Ball();

		float spx;
		float spy;
		float vic_amp;

		float vic_ang;
        float rot;
};
void TBall::Ball()
{
	return;
}

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TTimer *Timer3;
	TLayout *Lay_ide;
	TRectangle *Rectangle1;
	TBall *b0;
	TRectangle *rpt;
	TCircle *Circle3;
	TRectangle *stick;
	TCircle *Circle4;
	TRectangle *h1;
	TRectangle *h2;
	TRectangle *h3;
	TRectangle *h4;
	TRectangle *h5;
	TRectangle *h6;
	TCircle *c1;
	TCircle *c2;
	TCircle *c3;
	TCircle *c4;
	TCircle *c6;
	TCircle *c7;
	TCircle *c8;
	TCircle *c5;
	TCircle *Circle1;
	TShadowEffect *ShadowEffect1;
	TCircle *Circle2;
	TShadowEffect *ShadowEffect2;
	TCircle *c9;
	TCircle *c10;
	TCircle *c11;
	TCircle *c12;
	TCircle *Circle5;
	TShadowEffect *ShadowEffect3;
	TCircle *Circle6;
	TShadowEffect *ShadowEffect4;
	TLayout *Lay_main;
	TLayout *Lay_back;
	TRectangle *Rectangle2;
	TRectangle *t1;
	TRectangle *t6;
	TRectangle *t5;
	TRectangle *t4;
	TRectangle *t3;
	TRectangle *t2;
	TShadowEffect *ShadowEffect5;
	void __fastcall FormMouseMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void __fastcall r0MouseMove(TObject *Sender, TShiftState Shift, float X,
          float Y);
	void __fastcall r0MouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall r0MouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall Timer3Timer(TObject *Sender);
	void __fastcall b0Paint(TObject *Sender, TCanvas *Canvas, const TRectF &ARect);
	void __fastcall Lay_ideMouseMove(TObject *Sender, TShiftState Shift, float X, float Y);
	void __fastcall Lay_ideMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          float X, float Y);
	void __fastcall FormCreate(TObject *Sender);




private:	// User declarations
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void __fastcall create_wave(int val);
	void __fastcall initial();
	void __fastcall create_target();
	void __fastcall move_target();
	void __fastcall belyardo_collosion(TBall *r,TBall *pr);
	void __fastcall Reflect(TBall * b1,TBall * b2);
	void __fastcall create_Ball(unsigned int clr,TPointF p,int style);
    void __fastcall PlaySoundFile( );
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
